#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include "snowflake.hpp"

namespace domain {

/// Attachment Flags
/// source:
/// https://docs.discord.com/developers/resources/message#attachment-object-attachment-flags
enum class AttachmentFlag : uint32_t {
  IS_CLIP = 1 << 0,
  IS_THUMBNAIL = 1 << 1,
  IS_REMIX = 1 << 2,
  IS_SPOILER = 1 << 3,
  CONTAINS_EXPLICIT_CONTENT = 1 << 4,
  IS_ANIMATED = 1 << 5,
  CONTAINS_GORE_CONTENT = 1 << 6,
  CONTAINS_SELF_HARM_CONTENT = 1 << 7,
};

/// Attachment object
/// Source:
/// https://docs.discord.com/developers/resources/message#attachment-object
struct Attachment {
  Snowflake id;
  std::string filename;
  std::optional<std::string> title;
  std::optional<std::string> description;
  std::optional<std::string> content_type;
  uint64_t size{0};
  std::string url;
  std::string proxy_url;
  std::optional<std::string> placeholder;
  uint8_t placeholder_version;
  std::optional<uint32_t> height;
  std::optional<uint32_t> width;
  std::optional<bool> ephemeral;
  std::optional<double> duration_secs;
  std::optional<std::string> waveform;
  uint32_t flags{0};
};

} // namespace domain
