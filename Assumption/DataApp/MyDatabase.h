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
#include <format>

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
class TMyQtDb : public base_type {
public:
   using database_type = QSqlDatabase;
   using database_conv = QSqlDatabase&;
   using database_const_conv = QSqlDatabase const&;
   using database_para = QSqlDatabase&;
   using database_const_para = QSqlDatabase const&;

   using query_type = QSqlQuery;
   using query_conv = QSqlQuery&;
   using query_const_conv = QSqlQuery const&;
   using query_para = QSqlQuery&;
   using query_const_para = QSqlQuery const&;

private:
   database_type database;
public:
   TMyQtDb(void) : base_type() { }
   TMyQtDb(base_type const& ref) : base_type(ref) { }

   std::string GetInformations() const { return base_type::GetInformation(); }
   operator base_type& () { return static_cast<base_type&>(*this); }

   TMyQtDb& operator = (base_type const& ref) {
      static_cast<base_type&>(*this) = ref;
      return *this;
   }

   TMyQtDb& operator = (base_type&& ref) {
      static_cast<base_type&>(*this).swap(ref);
      return *this;
   }

   database_conv Database() { return database; }
   database_const_conv Database() const { return database; }


   //TMyQuery<TMyQtDb, base_type> CreateQuery(void) const {
   //   TMyQuery<TMyQtDb, base_type> query;
   query_type CreateQueryObject(void) const {
      QSqlQuery query(database);
      return query;
   }

   void swap(TMyQtDb& ref) {
      using std::swap;
      swap(database, ref.database);
      static_cast<base_type&>(*this).swap(static_cast<base_type&>(ref));
   }

   std::pair<bool, std::string>Open(void) {
      if (database.isOpen()) database.close();
      std::string param;
      base_type& srv = static_cast<base_type&>(*this);
      if constexpr (std::is_same<base_type, TMyMSSQL>::value) {

         static constexpr auto driver = []() {
            if constexpr (std::is_same<base_type, TMyMSSQL>::value)
               return "SQL Server Native Client 11.0"s;
            else if constexpr (std::is_same<base_type, TMyOracle>::value || std::is_same<base_type, TMyMySQL>::value)
               return ""s;
            else static_assert_no_supported();
         };

         database = database_type::addDatabase("QODBC");

         param = "DRIVER={"s + driver() + "};"s +
            "SERVER="s + srv.Server() + ";"s +
            "DATABASE="s + srv.Database() + ";"s;
         if (srv.Integrated()) param += "Trusted_Connection=yes;"s;   // Integrated Security=SSPI;
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

      if (auto ret = database.open(); ret == true) return { ret, ""s };
      else {
         return { ret, database.lastError().text().toStdString() + "\n" + param };
      }
   }

   bool Connected() {
      return database.isOpen();
   }

   void Close() {
      database.close();
   }


   // --------------------------------------------------------------------------------------------------
   // Hilfsmethoden für Querys

   static std::pair<bool, std::string> SetSQL(query_para query, std::string const& strSQL) {
      if (auto ret = query.prepare(QString::fromStdString(strSQL)); ret) return { ret, ""s };
      else {
         /*
         std::ostringstream params;
         params << "Parameter:\n";
         //for (auto const& para : query.boundValues()) params.emplace_back(para.toString().toStdString());
         std::ranges::copy(query.boundValues()
                             | std::views::transform([](auto d) { return d.toString().toStdString(); }),
                           std::ostream_iterator<std::string>(std::cout, "\n"));
         */
         return { ret, query.lastError().text().toStdString() };
      }
   }

   static std::string GetSQL(query_para query) { return query.lastQuery().toStdString(); }

   static std::tuple<bool, std::string, std::vector<std::string>> Execute(query_para query) {
      if (auto ret = query.exec(); ret) return { ret, ""s, { } };
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
   static std::optional<ret_type> Get(query_para query, std::string const& field, bool required) {
      if (!query.isActive() || !query.isValid()) throw std::runtime_error("Query isn't active or valid.");
      QVariant attribut = query.value(QString::fromStdString(field));
      // prüfen invalid and null
      if (!attribut.isValid()) {
         if (required) throw std::runtime_error(std::format("attribute {} isn't valid.", field));
         else return { };
      }
      else {
         if (attribut.isNull()) return { };
         if constexpr (std::is_same<ret_type, std::string>::value) return std::make_optional(attribut.toString().toStdString());
         else if constexpr (std::is_same<ret_type, int>::value) return std::make_optional(attribut.toInt());
         else if constexpr (std::is_same<ret_type, double>::value) return std::make_optional(attribut.toDouble());
         else if constexpr (std::is_same<ret_type, std::chrono::year_month_day>::value) {
            QDate date = attribut.toDateTime().date().toDateTime();
            return std::make_optional(std::chrono::year_month_day { std::chrono::year(date.year()),
               std::chrono::month(date.month()),
               std::chrono::day(date.day()) });
         }
         else if constexpr (std::is_same<ret_type, std::chrono::system_clock::time_point>::value) {
            std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(attribut.toDateTime().toSecsSinceEpoch());
         }
         else static_assert_no_supported();
      }
}

   template <my_db_param_type param_type>
   static bool Set(query_para query, std::string const& field_name, param_type const& param) {
      QString field = QString::fromStdString(":"s + field_name);
      if constexpr (is_optional<param_type>::value) {
         if (!param) {
            QVariant nullValue = QVariant(QVariant::Null);
            query.bindValue(field, nullValue);
            return query.boundValue(field).isValid();
         }
         else {
            //using datatype = std::remove_cvref_t<param_type>;
            query.bindValue(field, *param);
            return query.boundValue(field).isValid();
         }
      }
      else {
         if constexpr (std::is_same<std::remove_cvref_t<param_type>, std::string>::value) {
            query.bindValue(field, QString::fromLatin1(QByteArray::fromStdString(param)));
         }
         else if constexpr (std::is_same<std::remove_cvref_t<param_type>, std::wstring>::value) {
            query.bindValue(field, QString::fromWStdString(param));
         }
         else if constexpr (std::is_same<std::remove_cvref_t<param_type>, std::chrono::year_month_day>::value) {
            QDate date(param.year(), static_cast<int>(param.month()), static_cast<int>(param.day()));
            query.bindValue(field, date);
         }
         else if constexpr (std::is_same<param_type, std::chrono::system_clock::time_point>::value) {
            QDateTime dateTime = QDateTime::fromSecsSinceEpoch(std::chrono::system_clock::to_time_t(param));
            query.bindValue(field, dateTime);
         }
         else {
            query.bindValue(field, param);
         }
         return query.boundValue(field).isValid();
      }
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

//template <template <typename> typename framework_type, typename server_type, typename... ret_types>
template <template <typename> typename framework_type, typename server_type>
concept my_db_frame_work = my_db_credentials<server_type> &&
   requires(framework_type<server_type> t) {
   typename framework_type<server_type>::database_type;
   typename framework_type<server_type>::database_conv;
   typename framework_type<server_type>::database_const_conv;
   typename framework_type<server_type>::database_para;
   typename framework_type<server_type>::database_const_para;
   typename framework_type<server_type>::query_type;
   typename framework_type<server_type>::query_conv;
   typename framework_type<server_type>::query_const_conv;
   typename framework_type<server_type>::query_para;
   typename framework_type<server_type>::query_const_para;
   { t.Database() } -> std::convertible_to<typename framework_type<server_type>::database_conv>;
   { t.Database() } -> std::convertible_to<typename framework_type<server_type>::database_const_conv>;
   { t.Open() } -> std::convertible_to<std::pair<bool, std::string>>;
   { t.Connected() } -> std::convertible_to<bool>;
   { t.Close() } -> std::convertible_to<void>;
   { t.CreateQueryObject() } -> std::convertible_to<typename framework_type<server_type>::query_type>;
      requires requires(typename framework_type<server_type>::query_para p, std::string const& s) {
         { framework_type<server_type>::SetSQL(p, s) } -> std::convertible_to<std::pair<bool, std::string>>;
         { framework_type<server_type>::GetSQL(p) } -> std::convertible_to<std::string>;
         { framework_type<server_type>::Execute(p) } -> std::convertible_to<std::tuple<bool, std::string, std::vector<std::string>>>;
         { framework_type<server_type>::First(p) } -> std::convertible_to<bool>;
         { framework_type<server_type>::IsEof(p) } -> std::convertible_to<bool>;
         { framework_type<server_type>::Next(p) } -> std::convertible_to<bool>;
   };
};
template <template <class> typename framework_type, typename server_type>
concept my_db_declaration = my_db_frame_work<framework_type, server_type>;

template <template <class> class framework_type, class server_type>
   requires my_db_declaration<framework_type, server_type>
class TMyDatabase;

template <template <class> class framework_type, class server_type>
   requires my_db_declaration<framework_type, server_type>
class TMyQuery {
private:
   using framework = framework_type<server_type>;
   typename framework::query_type query;
   TMyDatabase<framework_type, server_type>& database;
   std::vector<std::string> params;

   TMyQuery() = delete;
   TMyQuery(TMyDatabase<framework_type, server_type>& db) : database(db) { }

   operator typename framework::query_conv() { return query;  }

};

template <template <class> class framework_type, class server_type>
// requires my_db_declaration<framework_type, server_type, int, bool, double, std::string>
   requires my_db_declaration<framework_type, server_type>
class TMyDatabase : public framework_type<server_type> {
private:
   using framework = framework_type<server_type>;

public:
   using type_server = server_type;

   TMyDatabase() : framework_type<server_type>() { }
   TMyDatabase(framework_type<server_type> const& ref) : framework_type<server_type>(ref) { }

   virtual ~TMyDatabase(void) {
      Close();
   }

   TMyDatabase& operator = (server_type const& ref) {
      static_cast<framework&>(*this) = ref;
      return *this;
   }

   operator typename framework::database_conv() { return framework::Database(); }

   bool Open(src_loc const& loc = src_loc::current()) {
      if (auto [ret, msg] = framework::Open(); ret) {
         return ret;
      }
      else {
         throw TMy_Db_Exception("database couldn't be open.", msg, framework::GetInformations(), { }, loc);
      }
   }

   void Close(void) { framework::Close(); }


   TMyQuery<framework_type, server_type> CreateQuery(void) {
      TMyQuery<framework_type, server_type> tmp(*this);
      tmp.Create();
      //tmp = std::move(framework::CreateQuery());
      return tmp;
   }

   std::string Status(void) {
      return std::format("{} {}", framework::Connected() ? "connected to" : "disconnected from", framework::GetInformations());
   }

};

