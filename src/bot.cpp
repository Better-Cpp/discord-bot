#include <print>

#include "convert.hpp"
#include <discord_bot/bot.hpp>
#include <discord_bot/domain/events.hpp>

#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

namespace discord_bot {

Bot::Bot(std::string const& token)
    : cluster(token, dpp::i_default_intents | dpp::i_message_content) {
  cluster.on_log([this](dpp::log_t const& e) { on_log(e); });
  cluster.on_ready([this](dpp::ready_t const& e) { on_ready(e); });
  cluster.on_slashcommand(
      [this](dpp::slashcommand_t const& e) { on_slashcommand(e); });
  cluster.on_message_create([this](dpp::message_create_t const& e) {
    event_dispatcher.emit<domain::MessageCreate>(convert::to_domain(e));
  });
  cluster.on_message_update([this](dpp::message_update_t const& e) {
    event_dispatcher.emit<domain::MessageUpdate>(convert::to_domain(e));
  });
  cluster.on_message_delete([this](dpp::message_delete_t const& e) {
    event_dispatcher.emit<domain::MessageDelete>(convert::to_domain(e));
  });
  cluster.on_message_delete_bulk([this](dpp::message_delete_bulk_t const& e) {
    event_dispatcher.emit<domain::MessageDeleteBulk>(convert::to_domain(e));
  });
}

void Bot::run() { cluster.start(dpp::st_wait); }

void Bot::on_log(dpp::log_t const& event) {
  std::println(stderr, "[{}] {}: {}", dpp::utility::current_date_time(),
               dpp::utility::loglevel(event.severity), event.message);
}

void Bot::on_ready(dpp::ready_t const& event) {
  if (dpp::run_once<struct register_bot_commands>()) {
    cluster.global_command_create(
        dpp::slashcommand("ping", "Ping pong!", cluster.me.id));
  }
  event_dispatcher.emit<domain::Ready>(convert::to_domain(event, cluster));
}

void Bot::on_slashcommand(dpp::slashcommand_t const& event) {
  if (event.command.get_command_name() == "ping") {
    event.reply("Pong!");
  }
}

} // namespace discord_bot
