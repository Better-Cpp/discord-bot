#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "attachment.hpp"
#include "channel.hpp"
#include "embed.hpp"
#include "reaction.hpp"
#include "snowflake.hpp"
#include "user.hpp"

namespace discord_bot::domain {

/// Source:
/// https://docs.discord.com/developers/resources/message#message-object-message-types
enum class MessageType : uint8_t {
  Default = 0,
  RecipientAdd = 1,
  RecipientRemove = 2,
  Call = 3,
  ChannelNameChange = 4,
  ChannelIconChange = 5,
  ChannelPinnedMessage = 6,
  UserJoin = 7,
  GuildBoost = 8,
  GuildBoostTier1 = 9,
  GuildBoostTier2 = 10,
  GuildBoostTier3 = 11,
  ChannelFollowAdd = 12,
  GuildDiscoveryDisqualified = 14,
  GuildDiscoveryRequalified = 15,
  GuildDiscoveryGracePeriodInitialWarning = 16,
  GuildDiscoveryGracePeriodFinalWarning = 17,
  ThreadCreated = 18,
  Reply = 19,
  ChatInputCommand = 20,
  ThreadStarterMessage = 21,
  GuildInviteReminder = 22,
  ContextMenuCommand = 23,
  AutoModerationAction = 24,
  RoleSubscriptionPurchase = 25,
  InteractionPremiumUpsell = 26,
  StageStart = 27,
  StageEnd = 28,
  StageSpeaker = 29,
  StageTopic = 31,
  GuildApplicationPremiumSubscription = 32,
  GuildIncidentAlertModeEnabled = 36,
  GuildIncidentAlertModeDisabled = 37,
  GuildIncidentReportRaid = 38,
  GuildIncidentReportFalseAlarm = 39,
  PurchaseNotification = 44,
  PollResult = 46,
};

/// Source:
/// https://docs.discord.com/developers/resources/message#message-reference-types
enum class MessageRefType : uint8_t {
  Default = 0,
  Forward = 1,
};

/// Source:
/// https://docs.discord.com/developers/resources/message#message-reference-structure
struct MessageReference {
  MessageRefType type{MessageRefType::Default};
  std::optional<Snowflake> message_id;
  std::optional<Snowflake> channel_id;
  std::optional<Snowflake> guild_id;
  std::optional<bool> fail_if_not_exists;
};

/// Source:
/// https://docs.discord.com/developers/resources/message#message-object-message-flags
enum class MessageFlags : uint32_t {
  Crossposted = 1 << 0,
  IsCrosspost = 1 << 1,
  SuppressEmbeds = 1 << 2,
  SourceMessageDeleted = 1 << 3,
  Urgent = 1 << 4,
  HasThread = 1 << 5,
  Ephemeral = 1 << 6,
  Loading = 1 << 7,
  FailedToMentionSomeRolesInThread = 1 << 8,
  SuppressNotifications = 1 << 12,
  IsVoiceMessage = 1 << 13,
  HasSnapshot = 1 << 14,
  IsComponentsV2 = 1 << 15,
};

/// Source: https://docs.discord.com/developers/resources/message#message-object
struct Message {
  Snowflake id;
  Snowflake channel_id;
  std::optional<Snowflake> guild_id;
  User author;
  std::string content;
  std::chrono::sys_time<std::chrono::milliseconds> timestamp{};
  std::optional<std::chrono::sys_time<std::chrono::milliseconds>>
      edited_timestamp;
  bool tts{false};
  bool mention_everyone{false};
  std::vector<User> mentions;
  std::vector<Snowflake> mention_roles;
  std::vector<ChannelMention> mention_channels;
  std::vector<Attachment> attachments;
  std::vector<Embed> embeds;
  std::vector<Reaction> reactions;
  std::optional<std::string> nonce;
  bool pinned{false};
  std::optional<Snowflake> webhook_id;
  MessageType type{MessageType::Default};
  // TODO: activity, application and application_id as needed
  uint32_t flags{0};
  std::optional<MessageReference> message_reference;
  std::vector<Message> message_snapshots;
  std::unique_ptr<Message> referenced_message;
  // TODO: interaction_metadata, interaction, thread, components, sticker_items
  // and stickers
  std::optional<uint64_t> position;

  Message() = default;
  Message(Message const& other);
  Message& operator=(Message const& other);
  Message(Message&&) noexcept = default;
  Message& operator=(Message&&) noexcept = default;
  ~Message() = default;
};

inline Message::Message(Message const& other)
    : id(other.id), channel_id(other.channel_id), guild_id(other.guild_id),
      author(other.author), content(other.content), timestamp(other.timestamp),
      edited_timestamp(other.edited_timestamp), tts(other.tts),
      mention_everyone(other.mention_everyone), mentions(other.mentions),
      mention_roles(other.mention_roles),
      mention_channels(other.mention_channels), attachments(other.attachments),
      embeds(other.embeds), reactions(other.reactions), nonce(other.nonce),
      pinned(other.pinned), webhook_id(other.webhook_id), type(other.type),
      flags(other.flags), message_reference(other.message_reference),
      message_snapshots(other.message_snapshots),
      referenced_message(
          other.referenced_message
              ? std::make_unique<Message>(*other.referenced_message)
              : nullptr),
      position(other.position) {}

inline Message& Message::operator=(Message const& other) {
  if (this != &other) {
    id = other.id;
    channel_id = other.channel_id;
    guild_id = other.guild_id;
    author = other.author;
    content = other.content;
    timestamp = other.timestamp;
    edited_timestamp = other.edited_timestamp;
    tts = other.tts;
    mention_everyone = other.mention_everyone;
    mentions = other.mentions;
    mention_roles = other.mention_roles;
    mention_channels = other.mention_channels;
    attachments = other.attachments;
    embeds = other.embeds;
    reactions = other.reactions;
    nonce = other.nonce;
    pinned = other.pinned;
    webhook_id = other.webhook_id;
    type = other.type;
    flags = other.flags;
    message_reference = other.message_reference;
    message_snapshots = other.message_snapshots;
    referenced_message =
        other.referenced_message
            ? std::make_unique<Message>(*other.referenced_message)
            : nullptr;
    position = other.position;
  }
  return *this;
}

} // namespace discord_bot::domain
