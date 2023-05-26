#pragma once
#include <stdexcept>

#include <optional>
#include <string>
#include <chrono>
#include <format>
#include <source_location>

using namespace std::literals;
using src_loc = std::source_location;

class TMy_Db_Exception : public std::runtime_error {
private:
   std::string                the_details;
   std::optional<std::string> the_database_infos;
   std::optional<std::string> the_query_infos;
   src_loc                    the_location;
   std::chrono::time_point<std::chrono::system_clock> timepoint;
public:
   TMy_Db_Exception(std::string const& msg, std::string const& det, std::optional<std::string> const& db = { },
      std::optional<std::string> const& qry = { }, src_loc const& loc = src_loc::current()) : std::runtime_error(msg) {
      the_details = det;
      the_database_infos = db;
      the_query_infos = qry;
      the_location = loc;
      timepoint = std::chrono::system_clock::now();
   }

   std::string                const& details() const { return the_details; }
   std::optional<std::string> const& database_infos() const { return  the_database_infos; }
   std::optional<std::string> const& query_infos() const { return the_query_infos; }
   src_loc                    const& location() const { return the_location; }

   std::string information(void) const {
      std::string ret = std::format("database error: {}\n", what());
      if (the_database_infos) ret += std::format("database: {}", *the_database_infos);
      if (the_query_infos) ret += std::format("database: {}", *the_query_infos);
      auto timestamp = std::chrono::current_zone()->to_local(timepoint);
      ret += std::format("{0:}\n{1:%d.%m.%Y %X} in file \"{2:}\" at line {3:}", the_details, timestamp,
         the_location.file_name(), the_location.line());
      return ret;
   }

};
