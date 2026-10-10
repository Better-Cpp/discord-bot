#pragma once

#include <string>

#include <dpp/dpp.h>

class Bot {
public:
  explicit Bot(std::string const& token);
  void run();

private:
  void on_log(dpp::log_t const& event);
  void on_ready(dpp::ready_t const& event);
  void on_slashcommand(dpp::slashcommand_t const& event);

  dpp::cluster cluster;
};
