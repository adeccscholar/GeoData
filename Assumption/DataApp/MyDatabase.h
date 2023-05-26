#pragma once

#include <adecc_Scholar/MyForm.h>

#include "MyDatabaseExceptions.h"
#include "MyDatabaseCredentials.h"

#include <utility>
#include <tuple>
#include <type_traits>
#include <string>
#include <vector>
#include <regex>
#include <optional>

// C++20 und darüber
#include <concepts>
#include <ranges>
#include <format>location>

using namespace std::literals;

#if defined BUILD_WITH_QT

#include <QtSQL>

template <typename ty>
struct is_my_db_value_type {
   static constexpr bool value = std::is_same<std::remove_cvref_t<ty>, int>::value ||
      std::is_same<std::remove_cvref_t<ty>, bool>::value ||
      std::is_same<std::remove_cvref_t<ty>, double>::value ||
      std::is_same<std::remove_cvref_t<ty>, std::string>::value;
   };

template <typename ty>
struct is_my_db_param_type {
   static constexpr bool value = is_my_db_value_type<ty> ||
      std::is_convertible<ty, const char*>::value;
   };

template <typename ty>
concept my_db_value_type = is_my_db_value_type<ty>::value;

template <typename ty>
concept my_db_param_type = is_my_db_param_type<ty>::value;



template <my_db_credentials base_type>
class TMyQtDb : public base_type{
public:
   using database_type       = QSqlDatabase; 
   using database_conv       = QSqlDatabase&;
   using database_const_conv = QSqlDatabase const&;
   using database_para       = QSqlDatabase&;
   using database_const_para = QSqlDatabase const&;

   using query_type       = QSqlQuery;
   using query_conv       = QSqlQuery&;
   using query_const_conv = QSqlQuery const&;
   using query_para       = QSqlQuery&;
   using query_const_para = QSqlQuery const&;

private:
   database_type database;
public:
   TMyQtDb(void) : base_type() { }
   TMyQtDb(base_type const& ref) : base_type(ref) { } 

   std::string GetInformations(void) const { return base_type::GetInformations();  }
   operator base_type& () { return static_cast<base_type&>(*this); }

   TMyQtDb& operator = (base_type const& ref) {
      static_cast<base_type&>(*this) = ref;
      return *this;
      }

   TMyQtDb& operator = (base_type&& ref) {
      static_cast<base_type&>(*this).swap(ref);
      return *this;
      }

   void swap(TMyQtDb& ref) noexcept {
      using std::swap;
      swap(database, ref.database);
      static_cast<base_type&>(*this).swap(static_cast<base_type&>(ref));
      }

   database_conv Database(void) { return database;  }
   database_const_conv Database(void) const { return database; }

   query_type CreateQueryObject() {
      QSqlQuery qry(database);
      return qry;
      }

   std::pair<bool, std::string> Open(void) {
      if (database.isOpen()) database.close();
      std::string param;
      base_type& srv = static_cast<base_type&>(*this);

      if constexpr(std::is_same<base_type, TMSSQL>::value) {
         static constexpr auto driver = []() {
            return "SQL Server Native Client 11.0"s;
            };

         database = database_type::addDatabase("QODBC");

         param = "Driver={"s + driver() + "};"s +
            "SERVER="s + srv.Server() + ";"s +
            "DATABASE="s + srv.Database() + ";"s;
         if (srv.Integrated()) param += "Trusted_Connection=yes;"s;
         else {
            param += "Uid="s + srv.User() + ";"s +
                     "Pwd="s + srv.Password() + ";"s;
            }
         database.setDatabaseName(QString::fromStdString(param));
         }
      else if constexpr (std::is_same<base_type, TMyOracle>::value) {
         database = database_type::addDatabase("QOCI");
         if (srv.UseTNS()) {
            param += "Service="s + srv.Service();
            database.setHostName(QString::fromStdString(srv.Service()));
            database.setDatabaseName("");
            database.setConnectOptions(QString::fromStdString("SERVICE_NAME="s + srv.Service()));
            }
         else {
            param += srv.Host() + ":"s + std::to_string(srv.Port()) + "/"s + srv.Database();
            database.setHostName(QString::fromStdString(srv.Host()));
            database.setPort(srv.Port());
            database.setDatabaseName(QString::fromStdString(srv.Database()));
            }
         database.setUserName(QString::fromStdString(srv.User()));
         database.setPassword(QString::fromStdString(srv.Password()));
        }
      else if constexpr (std::is_same<base_type, TMyMySQL>::value) {
         database = database_type::addDatabase("QMYSQL");
         param += srv.Host() + ":"s + std::to_string(srv.Port()) + "/"s + srv.Database();
         database.setHostName(QString::fromStdString(srv.Host()));
         database.setPort(srv.Port());
         database.setDatabaseName(QString::fromStdString(srv.Database()));
         database.setUserName(QString::fromStdString(srv.User()));
         database.setPassword(QString::fromStdString(srv.Password()));
      }
      else static_assert_no_supported();

      if (auto ret = database.open(); ret) return { ret, ""s };
      else {
         return { ret, database.lastError().text().toStdString() + "\n"s + param };
      }
   }


   bool Connected() const {
      return db.isOpen();
      }

   void Close() {
      database.close();
      }


   // ----------------------------------------------------------------------------------------

   static std::string GetSQL(query_para query) {
       return query.lastQuery().toStdString();
       }

   static std::pair<bool, std::string> SetSQL(query_para query, std::string const& strSQL) {
      if (auto ret = query.prepare(QString::fromStdString(strSQL)); ret) return { ret, "" };
      else return { ret, query.lastError().text().toStdString() };
      }

   static std::tuple<bool, std::string, std::vector<std::string>> Execute(query_para query) {
      if (auto ret = query.exec(); ret) [[likely]] return { ret, "", { } };
      else {
         std::vector<std::string> params;
         for (auto const& para : query.boundValues()) params.emplace_back(para.toString().toStdString());
         return { ret, query.lastError().text().toStdString(), params };
         }
      }

   static bool First(query_para query) { return query.first(); }
   static bool IsEof(query_para query) { return query.isValid(); }
   static bool Next(query_para query) { return query.next(); }

   template <my_db_value_type ret_type>
   static std::optional<ret_type> Get(query_param query, std::string const& field, bool required) {
       }

   template <my_db_param_type param_type>
   static bool Set(query_param query, std::string const& field, param_type const& param) {
      }
 
};

class TMyFDAC { };

#elif defined BUILD_WITH_FMX || defined BUILD_WITH_VCL
#error We wait for C++20
class TMyQtDb {};

class TMyFDAC { };

#else
#error not defined
#endif

template <typename ty>
concept my_db_frame_work = requires(ty t) {
   { ty::local } -> std::convertible_to<std::string>;
   typename ty::database_type;
   typename ty::database_conv;
   typename ty::database_para;
   typename ty::query_type;
   typename ty::query_conv;
   typename ty::query_para;
   { ty::Create() } -> std::convertible_to<typename ty::database_type>;
      requires requires (typename ty::database_para p) {
         { ty::CreateQuery(p) } -> std::convertible_to<typename ty::query_type>;
         { ty::Connected(p) } -> std::convertible_to<bool>;
         { ty::Close(p) } -> std::convertible_to<void>;

     };
      requires requires (typename ty::database_para p, std::string const& s, bool b) {
          { ty::Open(p, s, s, b, s, s) } -> std::convertible_to<std::pair<bool, std::string>>;
     };
        requires requires (typename ty::query_para p) {
         { ty::GetSQL(p) } -> std::convertible_to<std::string>;
         { ty::First(p) } -> std::convertible_to<bool>;
         { ty::IsEof(p) } -> std::convertible_to<bool>;
         { ty::Next(p) } -> std::convertible_to<bool>;
         { ty::Execute(p) } -> std::convertible_to <std::tuple<bool, std::string, std::vector<std::string>>>;
     };
        requires requires (typename ty::query_para p, std::string const& s, bool b) {
           { ty::SetSQL(p, s) } -> std::convertible_to<std::pair<bool, std::string>>;
   };

};

template <my_db_frame_work ty> class TMyDatabase;

template <my_db_frame_work ty> class TMyQuery {
private:
   typename ty::query_type query;
   TMyDatabase<ty>& database;
   std::vector<std::string> params;

   TMyQuery() = delete;
   TMyQuery(TMyDatabase<ty>& db) : database(db) { }

   operator typename ty::query_conv() { return query;  }

};

template <my_db_frame_work ty> class TMyDatabase {
private:
   std::string strServer;
   std::string strDatabase;
   bool        boIntegrated;
   std::string strUser;
   std::string strPassword;

   typename ty::database_type db;

public:
   TMyDatabase(std::string const& s, std::string const& d, bool b, std::string const& u, std::string const& p) :
      strServer(s), strDatabase(d), boIntegrated(b), strUser(u), strPassword(p) {
      db = ty::Create();
      }

   TMyDatabase() : TMyDatabase(""s, ""s, false, ""s, ""s) { } 
   TMyDatabase(std::string const& data) : TMyDatabase(ty::local, data, true, ""s, ""s) { }
   TMyDatabase(std::string const& server, std::string const& data) : TMyDatabase(server, data, true, ""s, ""s) { }

   operator typename ty::database_conv() { return db; };

   bool Open(src_loc const& loc = src_loc::current()) {
      if (auto [ret, msg] = ty::Open(db, strServer, strDatabase, boIntegrated, strUser, strPassword); ret) return ret;
      else {
         std::string strInfo = std::format("database {}/{} couldn't be open.", strServer, strDatabase);
         throw TMy_Db_Exception(strInfo, msg, { }, { }, loc);
         }
      } 
};

