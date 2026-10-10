#include <cstdlib>
#include <print>

#include <discord_bot/bot.hpp>

int main() {
  char const* token = std::getenv("BOT_TOKEN");
  if (!token) {
    std::println(stderr, "BOT_TOKEN environment variable is not set");
    return EXIT_FAILURE;
  }

  Bot bot{token};
  bot.run();
}
