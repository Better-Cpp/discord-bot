#pragma once

#include <charconv>
#include <cstdint>
#include <format>
#include <functional>
#include <stdexcept>
#include <string>
#include <string_view>

namespace discord_bot::domain {

class Snowflake {
public:
  static constexpr uint64_t DiscordEpoch = 1420070400000ULL;

  constexpr Snowflake() noexcept = default;
  constexpr explicit Snowflake(uint64_t val) noexcept : value_(val) {}

  explicit Snowflake(std::string_view sv) {
    if (sv.empty()) {
      value_ = 0;
      return;
    }
    auto const res = std::from_chars(sv.data(), sv.data() + sv.size(), value_);
    if (res.ec != std::errc{}) {
      throw std::invalid_argument("Failed to parse Snowflake from string");
    }
  }

  [[nodiscard]] constexpr uint64_t value() const noexcept { return value_; }

  [[nodiscard]] constexpr explicit operator uint64_t() const noexcept {
    return value_;
  }

  [[nodiscard]] constexpr uint64_t timestamp_ms() const noexcept {
    return (value_ >> 22) + DiscordEpoch;
  }

  [[nodiscard]] std::string to_string() const { return std::to_string(value_); }

  constexpr auto operator<=>(Snowflake const&) const noexcept = default;
  constexpr bool operator==(Snowflake const&) const noexcept = default;

private:
  uint64_t value_{0};
};

} // namespace discord_bot::domain

template <> struct std::hash<discord_bot::domain::Snowflake> {
  size_t operator()(discord_bot::domain::Snowflake const& sf) const noexcept {
    return std::hash<uint64_t>{}(sf.value());
  }
};

template <>
struct std::formatter<discord_bot::domain::Snowflake>
    : std::formatter<uint64_t> {
  auto format(discord_bot::domain::Snowflake const& sf,
              std::format_context& ctx) const {
    return std::formatter<uint64_t>::format(sf.value(), ctx);
  }
};
