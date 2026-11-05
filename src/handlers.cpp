#include <print>
#include <utility>

#include <discord_bot/domain/events.hpp>
#include <discord_bot/handlers.hpp>

namespace discord_bot {

void register_handlers(Bot& bot) {
  bot.on<domain::Ready>([](domain::Ready const& e) {
    std::println("[test] ready: {} in {} guilds", e.user.username,
                 e.guild_ids.size());
  });
  bot.on<domain::MessageCreate>([](domain::MessageCreate const& e) {
    std::println("[test] create id={} channel={} author={} len={} type={}",
                 e.message.id, e.message.channel_id, e.message.author.id,
                 e.message.content.size(), std::to_underlying(e.message.type));
  });
  bot.on<domain::MessageUpdate>([](domain::MessageUpdate const& e) {
    std::println("[test] update id={} edited={}", e.message.id,
                 e.message.edited_timestamp.has_value());
  });
  bot.on<domain::MessageDelete>([](domain::MessageDelete const& e) {
    std::println("[test] delete id={} channel={}", e.id, e.channel_id);
  });
  bot.on<domain::MessageDeleteBulk>([](domain::MessageDeleteBulk const& e) {
    std::println("[test] bulk delete {} messages", e.ids.size());
  });
}

} // namespace discord_bot
