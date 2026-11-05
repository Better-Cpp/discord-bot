#pragma once

#include <dpp/dpp.h>

#include <discord_bot/domain/snowflake.hpp>
#include <discord_bot/domain/user.hpp>

namespace discord_bot::convert {

domain::Snowflake to_domain(dpp::snowflake id);
std::optional<domain::Snowflake> to_optional_domain(dpp::snowflake id);

domain::User to_domain(dpp::user user);

} // namespace discord_bot::convert
