#include <dpp/snowflake.h>
#include <optional>
#include <ranges>

#include "convert.hpp"
#include "discord_bot/domain/snowflake.hpp"
#include <dpp/cluster.h>
#include <dpp/message.h>
#include <vector>

namespace discord_bot::convert {

// Basic types:
std::optional<std::string> to_optional(std::string const& s) {
  if (s.empty())
    return std::nullopt;
  return s;
}

std::chrono::sys_time<std::chrono::milliseconds> to_time(std::time_t t) {
  return std::chrono::sys_time<std::chrono::milliseconds>{
      std::chrono::seconds{t}};
}

std::optional<std::chrono::sys_time<std::chrono::milliseconds>>
to_optional_time(std::time_t t) {
  if (t == 0)
    return std::nullopt;
  return to_time(t);
}

// D++ types

domain::Snowflake to_domain(dpp::snowflake id) {
  return domain::Snowflake{static_cast<std::uint64_t>(id)};
}

std::optional<domain::Snowflake> to_optional_domain(dpp::snowflake id) {
  if (id == 0)
    return std::nullopt;
  return to_domain(id);
}

domain::User to_domain(dpp::user user) {
  return domain::User{.id = to_domain(user.id),
                      .username = user.username,
                      .discriminator = user.discriminator,
                      .global_name = to_optional(user.global_name),
                      .avatar = to_optional(user.avatar.to_string()),
                      .bot = user.is_bot(),
                      .system = user.is_system(),
                      .mfa_enabled = user.is_mfa_enabled(),
                      .banner = std::nullopt,
                      .verified = user.is_verified(),
                      .flags = user.flags};
}

domain::Attachment to_domain(dpp::attachment const& a) {
  return domain::Attachment{
      .id = to_domain(a.id),
      .filename = a.filename,
      .description = to_optional(a.description),
      .content_type = to_optional(a.content_type),
      .size = a.size,
      .url = a.url,
      .proxy_url = a.proxy_url,
      .height = a.height ? std::optional{a.height} : std::nullopt,
      .width = a.width ? std::optional{a.width} : std::nullopt,
      .ephemeral = a.ephemeral,
  };
}

domain::MessageReference to_domain(struct dpp::message::message_ref const& r) {
  return domain::MessageReference{
      .type = static_cast<domain::MessageRefType>(
          static_cast<std::uint8_t>(r.type)),
      .message_id = to_optional_domain(r.message_id),
      .channel_id = to_optional_domain(r.channel_id),
      .guild_id = to_optional_domain(r.guild_id),
      .fail_if_not_exists = r.fail_if_not_exists,
  };
}

domain::Message to_domain(dpp::message const& m) {
  domain::Message out;
  out.id = to_domain(m.id);
  out.channel_id = to_domain(m.channel_id);
  out.guild_id = to_optional_domain(m.guild_id);
  out.author = to_domain(m.author);
  out.content = m.content;
  out.timestamp = to_time(m.sent);
  out.edited_timestamp = to_optional_time(m.edited);
  out.tts = m.tts;
  out.mention_everyone = m.mention_everyone;
  for (auto const& mention : m.mentions) {
    out.mentions.push_back(
        to_domain(mention.first)); // pair<user, guild_member>
  }
  for (auto const role : m.mention_roles) {
    out.mention_roles.push_back(to_domain(role));
  }
  for (auto const& a : m.attachments) {
    out.attachments.push_back(to_domain(a));
  }
  out.pinned = m.pinned;
  out.webhook_id = to_optional_domain(m.webhook_id);
  out.type =
      static_cast<domain::MessageType>(static_cast<std::uint8_t>(m.type));
  out.flags = m.flags;
  if (m.message_reference.message_id != 0 ||
      m.message_reference.channel_id != 0) {
    out.message_reference = to_domain(m.message_reference);
  }
  // TODO: embeds, reactions, referenced_message
  return out;
}

// Events
domain::MessageCreate to_domain(dpp::message_create_t const& e) {
  return {.message = to_domain(e.msg),
          .guild_id = to_optional_domain(e.msg.guild_id),
          .channel_type = std::nullopt};
}

domain::MessageUpdate to_domain(dpp::message_update_t const& e) {
  return {.message = to_domain(e.msg),
          .guild_id = to_optional_domain(e.msg.guild_id),
          .channel_type = std::nullopt};
}

domain::MessageDelete to_domain(dpp::message_delete_t const& e) {
  return {.id = to_domain(e.id),
          .channel_id = to_domain(e.channel_id),
          .guild_id = to_optional_domain(e.guild_id)};
}

domain::MessageDeleteBulk to_domain(dpp::message_delete_bulk_t const& e) {
  domain::MessageDeleteBulk out;
  for (auto const id : e.deleted)
    out.ids.push_back(to_domain(id));
  out.channel_id =
      e.deleting_channel
          ? to_domain(e.deleting_channel->id)
          : domain::Snowflake(
                0); // For some reason, D++ stores them behind a pointer,
                    // even though the Discord API guarantees they exist.
  out.guild_id = e.deleting_guild->id ? to_optional_domain(e.deleting_guild->id)
                                      : std::nullopt;
  return out;
}

domain::Ready to_domain(dpp::ready_t const& e, dpp::cluster const& cluster) {
  return {
      .user = convert::to_domain(cluster.me),
      .guild_ids = e.guilds |
                   std::views::transform(
                       [](dpp::snowflake const& id) { return to_domain(id); }) |
                   std::ranges::to<std::vector>(),
      .session_id = e.session_id,
      .shard_id = e.shard_id,
  };
}

} // namespace discord_bot::convert
