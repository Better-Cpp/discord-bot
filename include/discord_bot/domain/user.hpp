#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

#include "snowflake.hpp"

namespace discord_bot::domain {

/// Source: https://docs.discord.com/developers/resources/user#user-object
struct User {
  Snowflake id;
  std::string username;
  uint16_t discriminator{0};
  std::optional<std::string> global_name;
  std::optional<std::string> avatar;
  std::optional<bool> bot;
  std::optional<bool> system;
  std::optional<bool> mfa_enabled;
  std::optional<std::string> banner;
  std::optional<uint32_t> accent_color;
  std::optional<std::string> locale;
  std::optional<bool> verified{false};
  std::optional<std::string> email;
  std::optional<uint32_t> flags;
  std::optional<uint8_t> premium_type;
  std::optional<uint32_t> public_flags;
  // TODO: add other fields when needed

  [[nodiscard]] std::string_view display_name() const noexcept {
    if (global_name.has_value() && !global_name->empty()) {
      return *global_name;
    }
    return username;
  }

  [[nodiscard]] std::string mention() const {
    return "<@" + id.to_string() + ">";
  }
};

} // namespace discord_bot::domain
