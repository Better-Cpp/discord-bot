#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "snowflake.hpp"
#include "user.hpp"

namespace domain {

/// Emoji Structure
/// Source: https://docs.discord.com/developers/resources/emoji#emoji-object
struct Emoji {
  std::optional<Snowflake> id;
  std::optional<std::string> name;
  std::vector<Snowflake> roles;
  std::optional<User> user;
  std::optional<bool> require_colons;
  std::optional<bool> managed;
  std::optional<bool> animated;
  std::optional<bool> available;
};

/// Reaction Count Details Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#reaction-count-details-object
struct ReactionCountDetails {
  uint32_t burst{0};
  uint32_t normal{0};
};

/// Reaction Structure
/// Source:
/// https://docs.discord.com/developers/resources/message#reaction-object
struct Reaction {
  uint32_t count{0};
  ReactionCountDetails count_details{};
  bool me{false};
  bool me_burst{false};
  Emoji emoji;
  std::vector<std::string> burst_colors;
};

} // namespace domain
