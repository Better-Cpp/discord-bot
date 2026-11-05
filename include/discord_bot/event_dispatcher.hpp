#pragma once

#include <concepts>
#include <functional>
#include <tuple>
#include <utility>
#include <vector>

namespace discord_bot {

template <typename... Events> class EventDispatcher {
public:
  EventDispatcher() = default;
  EventDispatcher(EventDispatcher const&) = delete;
  EventDispatcher& operator=(EventDispatcher const&) = delete;

  template <typename Event, typename Handler>
    requires std::invocable<Handler const&, Event const&>
  void on(Handler&& handler) {
    std::get<handler_list<Event>>(subscriber_lists)
        .emplace_back(std::forward<Handler>(handler));
  }

  template <typename Event> void emit(Event const& event) const {
    for (auto const& handler :
         std::get<handler_list<Event>>(subscriber_lists)) {
      handler(event);
    }
  }

private:
  template <typename Event>
  using handler_list =
      std::vector<std::move_only_function<void(Event const&) const>>;

  std::tuple<handler_list<Events>...> subscriber_lists;
};

} // namespace discord_bot
