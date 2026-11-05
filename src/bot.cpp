#include "convert.hpp"
#include <discord_bot/bot.hpp>
#include <discord_bot/domain/events.hpp>

#include <print>

#include <dpp/dpp.h>

namespace discord_bot {

Bot::Bot(std::string const& token) : cluster(token) {
  cluster.on_log([this](dpp::log_t const& e) { on_log(e); });
  cluster.on_ready([this](dpp::ready_t const& e) { on_ready(e); });
  cluster.on_slashcommand(
      [this](dpp::slashcommand_t const& e) { on_slashcommand(e); });
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
  event_dispatcher.emit<domain::Ready>(domain::Ready{
      .user = convert::to_domain(cluster.me),
      .session_id = event.session_id,
      .shard_id = event.shard_id,
  });
}

void Bot::on_slashcommand(dpp::slashcommand_t const& event) {
  if (event.command.get_command_name() == "ping") {
    event.reply("Pong!");
  }
}

} // namespace discord_bot
