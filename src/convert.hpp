#pragma once

#include <dpp/dpp.h>

#include <discord_bot/domain/attachment.hpp>
#include <discord_bot/domain/events.hpp>
#include <discord_bot/domain/message.hpp>
#include <discord_bot/domain/snowflake.hpp>
#include <discord_bot/domain/user.hpp>

namespace discord_bot::convert {
std::optional<std::string> to_optional(std::string const& s);
std::chrono::sys_time<std::chrono::milliseconds> to_time(std::time_t t);
std::optional<std::chrono::sys_time<std::chrono::milliseconds>>
to_optional_time(std::time_t t);

domain::Snowflake to_domain(dpp::snowflake id);
std::optional<domain::Snowflake> to_optional_domain(dpp::snowflake id);

domain::User to_domain(dpp::user user);
domain::Attachment to_domain(dpp::attachment const& a);
domain::MessageReference to_domain(dpp::message::message_ref const& r);
domain::Message to_domain(dpp::message const& m);

domain::MessageCreate to_domain(dpp::message_create_t const& e);
domain::MessageUpdate to_domain(dpp::message_update_t const& e);
domain::MessageDelete to_domain(dpp::message_delete_t const& e);
domain::MessageDeleteBulk to_domain(dpp::message_delete_bulk_t const& e);
domain::Ready to_domain(dpp::ready_t const& e, dpp::cluster const& cluster);
} // namespace discord_bot::convert
