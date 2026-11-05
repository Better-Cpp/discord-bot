#include <cstdlib>
#include <print>

#include <discord_bot/bot.hpp>
#include <discord_bot/domain/events.hpp>

int main() {
  char const* token = std::getenv("BOT_TOKEN");
  if (!token) {
    std::println(stderr, "BOT_TOKEN environment variable is not set");
    return EXIT_FAILURE;
  }

  discord_bot::Bot bot{token};
  bot.on<discord_bot::domain::Ready>([](auto const& event) {
    std::println("Logged in as {}#{}", event.user.username,
                 event.user.discriminator);
  });
  bot.on<discord_bot::domain::MessageCreate>([](auto const& event) {
    std::println("Received message: {}", event.message.content);
  });
  bot.run();
}
