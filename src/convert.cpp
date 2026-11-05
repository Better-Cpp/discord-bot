#include "convert.hpp"
#include <optional>

namespace discord_bot::convert {

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
                      .global_name =
                          user.global_name.empty()
                              ? std::nullopt
                              : std::optional<std::string>{user.global_name},
                      .avatar = user.avatar.to_string(),
                      .bot = user.is_bot(),
                      .system = user.is_system(),
                      .mfa_enabled = user.is_mfa_enabled(),
                      .banner = std::nullopt,
                      .verified = user.is_verified(),
                      .flags = user.flags};
}

} // namespace discord_bot::convert
