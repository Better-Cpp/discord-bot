#include <cstdlib>
#include <print>
#include <utility>

#include <discord_bot/bot.hpp>
#include <discord_bot/handlers.hpp>

int main() {
  char const* token = std::getenv("BOT_TOKEN");
  if (!token) {
    std::println(stderr, "BOT_TOKEN environment variable is not set");
    return EXIT_FAILURE;
  }

  discord_bot::Bot bot{token};
  discord_bot::register_handlers(bot);
  bot.run();
}
