#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "snowflake.hpp"
#include "user.hpp"

namespace discord_bot::domain {

/// Source:
/// https://docs.discord.com/developers/resources/channel#channel-object-channel-types
enum class ChannelType : uint8_t {
  GuildText = 0,
  Dm = 1,
  GuildVoice = 2,
  GroupDm = 3,
  GuildCategory = 4,
  GuildAnnouncement = 5,
  AnnouncementThread = 10,
  PublicThread = 11,
  PrivateThread = 12,
  GuildStageVoice = 13,
  GuildDirectory = 14,
  GuildForum = 15,
  GuildMedia = 16,
};

/// Source:
/// https://docs.discord.com/developers/resources/channel#channel-mention-object
struct ChannelMention {
  Snowflake id;
  Snowflake guild_id;
  ChannelType type{ChannelType::GuildText};
  std::string name;
};

/// Source: https://docs.discord.com/developers/resources/channel#channel-object
struct Channel {
  Snowflake id;
  ChannelType type{ChannelType::GuildText};
  std::optional<Snowflake> guild_id;
  std::optional<int32_t> position;
  // TODO: add permission_overwrites.
  std::optional<std::string> name;
  std::optional<std::string> topic;
  bool nsfw{false};
  std::optional<Snowflake> last_message_id;
  std::optional<uint32_t> bitrate;
  std::optional<uint32_t> user_limit;
  std::optional<uint32_t> rate_limit_per_user;
  std::vector<User> recipients;
  std::optional<std::string> icon;
  std::optional<Snowflake> owner_id;
  std::optional<Snowflake> application_id;
  std::optional<bool> managed;
  std::optional<Snowflake> parent_id;
  // TDOD: complete the rest of the fields as needed.
};

} // namespace discord_bot::domain
