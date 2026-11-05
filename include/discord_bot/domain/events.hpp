#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "channel.hpp"
#include "message.hpp"
#include "snowflake.hpp"
#include "user.hpp"

namespace discord_bot::domain {

/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-create
struct MessageCreate {
  Message message;
  std::optional<Snowflake> guild_id;
  std::optional<ChannelType> channel_type;
};

/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-update
struct MessageUpdate {
  Message message;
  std::optional<Snowflake> guild_id;
  std::optional<ChannelType> channel_type;
};

/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-delete
struct MessageDelete {
  Snowflake id;
  Snowflake channel_id;
  std::optional<Snowflake> guild_id;
};

/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-delete-bulk
struct MessageDeleteBulk {
  std::vector<Snowflake> ids;
  Snowflake channel_id;
  std::optional<Snowflake> guild_id;
};

/// Source: https://docs.discord.com/developers/events/gateway-events#ready
struct Ready {
  User user;
  std::vector<Snowflake> guild_ids;
  std::string session_id;
  std::optional<std::uint32_t> shard_id;
};

using EventTypes = std::variant<MessageCreate, MessageUpdate, MessageDelete,
                                MessageDeleteBulk, Ready>;

} // namespace discord_bot::domain
