#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace domain {

/// Embed Media Flags
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-media-flags
enum class EmbedMediaFlags : uint32_t {
  IS_ANIMATED = 1 << 5,
};

/// Embed Flags
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-flags
enum class EmbedFlags : uint32_t {
  CONTAINS_EXPLICIT_CONTENT = 1 << 4,
  IS_CONTENT_INVENTORY_ENTRY = 1 << 5,
  CONTAINS_GORE_CONTENT = 1 << 6,
  CONTAINS_SELF_HARM_CONTENT = 1 << 7,
};

/// Embed Field Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-field-structure
struct EmbedField {
  std::string name;
  std::string value;
  std::optional<bool> is_inline;
};

/// Embed Footer Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-footer-structure
struct EmbedFooter {
  std::string text;
  std::optional<std::string> icon_url;
  std::optional<std::string> proxy_icon_url;
};

/// Embed Image Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-image-structure
struct EmbedImage {
  std::string url;
  std::optional<std::string> proxy_url;
  std::optional<uint32_t> height;
  std::optional<uint32_t> width;
  std::optional<std::string> content_type;
  std::optional<std::string> placeholder;
  std::optional<uint8_t> placeholder_version;
  std::optional<std::string> description;
  std::optional<EmbedMediaFlags> flags;
};

/// Discord Embed Video Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-video-structure
struct EmbedVideo {
  std::optional<std::string> url;
  std::optional<std::string> proxy_url;
  std::optional<uint32_t> height;
  std::optional<uint32_t> width;
  std::optional<std::string> content_type;
  std::optional<std::string> placeholder;
  std::optional<uint8_t> placeholder_version;
  std::optional<std::string> description;
  std::optional<EmbedMediaFlags> flags;
};

/// Embed Provider Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-provider-structure
struct EmbedProvider {
  std::optional<std::string> name;
  std::optional<std::string> url;
};

/// Embed Author Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#embed-object-embed-author-structure
struct EmbedAuthor {
  std::string name;
  std::optional<std::string> url;
  std::optional<std::string> icon_url;
  std::optional<std::string> proxy_icon_url;
};

/// Embed Structure
/// Source: https://docs.discord.com/developers/resources/message#embed-object
struct Embed {
  std::optional<std::string> title;
  std::optional<std::string> type;
  std::optional<std::string> description;
  std::optional<std::string> url;
  std::optional<std::chrono::sys_time<std::chrono::milliseconds>> timestamp;
  std::optional<uint32_t> color;
  std::optional<EmbedFooter> footer;
  std::optional<EmbedImage> image;
  std::optional<EmbedImage> thumbnail;
  std::optional<EmbedVideo> video;
  std::optional<EmbedProvider> provider;
  std::optional<EmbedAuthor> author;
  std::vector<EmbedField> fields;
};

} // namespace domain
