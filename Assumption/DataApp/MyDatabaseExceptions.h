#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <chrono>
#include <optional>
#include <source_location>

using src_loc    = std::source_location;
using time_stamp = std::chrono::time_point<std::chrono::system_clock>;


namespace std {

   template <>
   struct formatter<std::source_location> : formatter<std::string_view> {
      template <typename FormatContext>
      auto format(const std::source_location& loc, FormatContext& ctx) {
         std::string_view format_str = "{}:{}:{}:{}";
         return formatter<std::string_view>::format(format_str, loc.file_name(), loc.line(), loc.column(), loc.function_name(), ctx);
      }
   };

}


class TMyExceptionInformation {
   friend void swap(TMyExceptionInformation& lhs, TMyExceptionInformation& rhs) noexcept { lhs.swap(rhs); }
private:
   time_stamp the_timepoint;
   src_loc    the_location;
public:
   TMyExceptionInformation(time_stamp const& timept = std::chrono::system_clock::now(), src_loc const& loc = src_loc::current()) :
      the_timepoint(timept), the_location(loc) {}

   TMyExceptionInformation(TMyExceptionInformation const& ref) :
      the_timepoint(ref.the_timepoint), the_location(ref.the_location) {}

   TMyExceptionInformation(TMyExceptionInformation&& ref) noexcept { swap(ref); }

   virtual ~TMyExceptionInformation() = default;

   void swap(TMyExceptionInformation& ref) noexcept {
      using std::swap;
      swap(the_timepoint, ref.the_timepoint);
      swap(the_location, ref.the_location);
      }

   time_stamp const& timepoint(void) const { return the_timepoint; }
   src_loc    const& location(void) const { return the_location; };


   std::string TimePosition() const { return TimePosition(the_timepoint, the_location); }
   std::string Time() const { return Time(the_timepoint); }
   std::string Position() const { return Position(the_location); }


   static std::string TimePosition(time_stamp const& _time, src_loc const& loc) {
      auto const cz_ts = std::chrono::current_zone()->to_local(_time);
      auto const millis = std::chrono::duration_cast<std::chrono::milliseconds>(_time.time_since_epoch()) % 1000;
      return std::format("[Error at {:%d.%m.%Y %X},{:03d} in file \"{}\" at line {}]", cz_ts, millis.count(), loc.file_name(), loc.line());
      }

   static std::string Time(time_stamp const& _time) {
      auto const cz_ts = std::chrono::current_zone()->to_local(_time);
      auto const millis = std::chrono::duration_cast<std::chrono::milliseconds>(_time.time_since_epoch()) % 1000;
      return std::format("{:%d.%m.%Y %X},{:03d}", cz_ts, millis.count());
      }

   static std::string Position(src_loc const& loc) {
      return std::format("in file \"{}\" at line {}", loc.file_name(), loc.line());
      }

};

class TMy_InputError : public std::runtime_error {
public:
   TMy_InputError(std::string const& msg) : std::runtime_error(msg) { }
};

class TMy_UserBreak : public std::runtime_error {
public:
   TMy_UserBreak(std::string const& msg) : std::runtime_error(msg) { }
};

class TMy_RuntimeError : public TMyExceptionInformation, public std::runtime_error {
private:
   mutable std::string strMessage; ///< Hilfsviable um Speicherdauer der Rückgabe sicherzustellen
public:
   TMy_RuntimeError(std::string strMsg, src_loc const& loc = src_loc::current(), 
                    time_stamp timepoint = std::chrono::system_clock::now()) :
         TMyExceptionInformation(timepoint, loc), 
         std::runtime_error(strMsg + TimePosition(timepoint, loc)) { }
   TMy_RuntimeError(TMy_RuntimeError const& ref) : TMyExceptionInformation(ref), std::runtime_error(ref) { }

   const char* what() const noexcept override {
      strMessage = std::format("{}\n{}", std::runtime_error::what(), TimePosition());
      return strMessage.c_str();
      }
};

class TMy_Db_Exception : public TMyExceptionInformation, public std::runtime_error {
private:
   std::string                the_details;
   std::optional<std::string> the_database_infos;
   std::optional<std::string> the_query_infos;

   mutable std::string strMessage; ///< Hilfsviable um Speicherdauer der Rückgabe sicherzustellen

public:
   TMy_Db_Exception(std::string const& msg, std::string const& det, std::optional<std::string> const& db = { },
                    std::optional<std::string> const& qry = { },
                    src_loc const& loc = src_loc::current(),
                    time_stamp timepoint = std::chrono::system_clock::now())
              : TMyExceptionInformation(timepoint, loc), std::runtime_error(msg) {
      the_details = det;
      the_database_infos = db;
      the_query_infos = qry;
      }

   std::string                const& details() const { return the_details; }
   std::optional<std::string> const& database_infos() const { return  the_database_infos; }
   std::optional<std::string> const& query_infos() const { return the_query_infos; }

   std::string                       position() const { return TimePosition();  }

   std::string information(void) const {
      std::string ret = std::format("database error: {}\n{}\n\n", std::runtime_error::what(), the_details);
      if (the_database_infos) ret += std::format("database:\n{}\n\n", *the_database_infos);
      if (the_query_infos) ret += std::format("statement:\n{}\n\n", *the_query_infos);
      ret += TimePosition();
      return ret;
      }

   const char* what() const noexcept override {
      strMessage = std::format("{}\n{}", std::runtime_error::what(), TimePosition());
      return strMessage.c_str();
      }
};