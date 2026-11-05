/// Source: https://docs.discord.com/developers/events/gateway-events

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

namespace domain {

/// Dispatched when a message is created.
/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-create
struct MessageCreate {
  Message message;
  std::optional<Snowflake> guild_id;
  std::optional<ChannelType> channel_type;
};

/// Dispatched when a message is updated.
/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-update
struct MessageUpdate {
  Message message;
  std::optional<Snowflake> guild_id;
  std::optional<ChannelType> channel_type;
};

/// Dispatched when a message is deleted.
/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-delete
struct MessageDelete {
  Snowflake id;
  Snowflake channel_id;
  std::optional<Snowflake> guild_id;
};

/// Dispatched when multiple messages are deleted at once.
/// Source:
/// https://docs.discord.com/developers/events/gateway-events#message-delete-bulk
struct MessageDeleteBulk {
  std::vector<Snowflake> ids;
  Snowflake channel_id;
  std::optional<Snowflake> guild_id;
};

/// Dispatched when client completes handshake with gateway.
/// Source: https://docs.discord.com/developers/events/gateway-events#ready
struct Ready {
  uint8_t version{0};
  User user;
  std::vector<Snowflake> guild_ids;
  std::string session_id;
  std::optional<std::string> resume_gateway_url;
};

using EventTypes = std::variant<MessageCreate, MessageUpdate, MessageDelete,
                                MessageDeleteBulk, Ready>;

} // namespace domain
