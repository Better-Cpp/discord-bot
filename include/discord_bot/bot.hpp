#pragma once

#include <string>

#include <dpp/dpp.h>
#include <utility>

#include <discord_bot/domain/events.hpp>
#include <discord_bot/event_dispatcher.hpp>

namespace discord_bot {

class Bot {
public:
  explicit Bot(std::string const& token);
  void run();

  template <typename Event, typename Handler>
    requires std::invocable<Handler const&, Event const&>
  void on(Handler&& handler) {
    event_dispatcher.on<Event>(std::forward<Handler>(handler));
  }

private:
  void on_log(dpp::log_t const& event);
  void on_ready(dpp::ready_t const& event);
  void on_slashcommand(dpp::slashcommand_t const& event);

  dpp::cluster cluster;
  EventDispatcher<domain::MessageCreate, domain::MessageUpdate,
                  domain::MessageDelete, domain::MessageDeleteBulk,
                  domain::Ready>
      event_dispatcher;
};

} // namespace discord_bot
