#pragma once

#include <string>
#include <format>

using namespace std::literals;

class TMSSQL {
   friend void swap(TMSSQL& lhs, TMSSQL& rhs) noexcept { lhs.swap(rhs);  }
private:
   std::string strServer;    ///< datbase server, optional \ instance name
   std::string strDatabase;  ///< database name
   bool        boIntegrated;
   std::string strUser;
   std::string strPassword;
public:
   TMSSQL(std::string const& s, std::string const& d, bool b, std::string const& u, std::string const& p) :
      strServer(s), strDatabase(d), boIntegrated(b), strUser(u), strPassword(p) { }

   TMSSQL(void) : TMSSQL ("(local)"s, "master"s, true, ""s, ""s) { }
   TMSSQL(std::string const& db) : TMSSQL("(local)"s, db, true, ""s, ""s) { }
   TMSSQL(std::string const& srv, std::string const& db) : TMSSQL(srv, db, true, ""s, ""s) { }

   TMSSQL(TMSSQL const& ref) : 
      strServer(ref.strServer), strDatabase(ref.strPassword), boIntegrated(ref.boIntegrated), strUser(ref.strUser), strPassword(ref.strPassword) { }

   TMSSQL(TMSSQL&& ref) noexcept { swap(ref);  }

   virtual ~TMSSQL(void) { }

   TMSSQL& operator = (TMSSQL const& ref) {
      strServer = ref.strServer;
      strDatabase = ref.strDatabase;
      boIntegrated  = ref.boIntegrated;
      strUser = ref.strUser;
      strPassword = ref.strPassword;
      return *this;
      }

   TMSSQL& operator = (TMSSQL&& ref) noexcept {
      swap(ref);
      return *this;
      }

   void swap(TMSSQL& ref) noexcept {
      using std::swap;
      swap(strServer,    ref.strServer);
      swap(strDatabase,  ref.strDatabase);
      swap(boIntegrated, ref.boIntegrated);
      swap(strUser,      ref.strUser);
      swap(strPassword,  ref.strPassword);
      }

   // Selektoren

   std::string const& Server(void) const { return strServer; }
   std::string const& Database(void) const { return strDatabase; }
   bool        Integrated(void) const { return boIntegrated; }
   std::string const& User(void) const { return strUser; }
   std::string const& Password(void) const { return strPassword; }

   std::string GetInformation(void) const { return std::format("MS SQL Server {}/{}", strServer, strDatabase); }
};


class TMyOracle {
   friend void swap(TMyOracle& lhs, TMyOracle& rhs) { lhs.swap(rhs); }
private:
   bool        boUseTNS = true;
   std::string strService = "XE";
   std::string strHost = "localhost";
   int         iPort = 1521;
   std::string strDatabase = "XE";
   std::string strUser = "system";
   std::string strPassword = "tiger";
public:
   TMyOracle() : TMyOracle("localhost"s, 1521, ""s, ""s, ""s) { }
   TMyOracle(std::string const& hst, int prt, std::string const& db, std::string const& usr, std::string const& pwd) :
      boUseTNS(false), strHost(hst), iPort(prt), strService(""s), strDatabase(db), strUser(usr), strPassword(pwd) { }
   TMyOracle(std::string const& d, std::string const& u, std::string const& p) :
      boUseTNS(false), strHost("localhost"), iPort(1521), strService(""s), strDatabase(d), strUser(u), strPassword(p) { }
   TMyOracle(bool usetns, std::string const& d, std::string const& u, std::string const& p) :
      boUseTNS(usetns), strHost(""), iPort(1521), strService(d), strDatabase(d), strUser(u), strPassword(p) { }

   TMyOracle(TMyOracle const& ref) {
      boUseTNS = ref.boUseTNS;
      strService = ref.strService;
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      strUser = ref.strUser;
      strPassword = ref.strPassword;
   }

   TMyOracle(TMyOracle&& ref) noexcept { swap(ref); }

   TMyOracle& operator = (TMyOracle const& ref) {
      boUseTNS = ref.boUseTNS;
      strService = ref.strService;
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      strUser = ref.strUser;
      strPassword = ref.strPassword;
      return *this;
   }



   TMyOracle& operator = (TMyOracle&& ref) noexcept {
      swap(ref);
      return *this;
   }

   void swap(TMyOracle& ref) noexcept {
      using std::swap;
      swap(boUseTNS, ref.boUseTNS);
      swap(strService, ref.strService);
      swap(strHost, ref.strHost);
      swap(iPort, ref.iPort);
      swap(strDatabase, ref.strDatabase);
      swap(strUser, ref.strUser);
      swap(strPassword, ref.strPassword);
   }

   bool               UseTNS(void) const { return boUseTNS; }
   std::string const& Service(void) const { return strService; }
   std::string const& Host(void) const { return strHost; }
   int                Port(void) const { return iPort; }
   std::string const& Database(void) const { return strDatabase; }
   std::string const& User(void) const { return strUser; }
   std::string const& Password(void) const { return strPassword; }

   std::string GetInformations(void) const {
      if (boUseTNS)
         return std::format("Oracle Server Service={}", strService);
      else
         return std::format("Oracle Server {}:{}/{}", strHost, iPort, strDatabase);
   }
};



class TMyMySQL {
   friend void swap(TMyMySQL& lhs, TMyMySQL& rhs) { lhs.swap(rhs); }
private:
   std::string strHost = "localhost";
   int         iPort = 3306;
   std::string strDatabase = "Instant";
   std::string strUser = "";
   std::string strPassword = "";
public:
   TMyMySQL() : TMyMySQL("localhost"s, 3306, ""s, ""s, ""s) { }
   TMyMySQL(std::string const& hst, int prt, std::string const& db, std::string const& usr, std::string const& pwd) :
      strHost(hst), iPort(prt), strDatabase(db), strUser(usr), strPassword(pwd) { }
   TMyMySQL(std::string const& d, std::string const& u, std::string const& p) :
      strHost("localhost"), iPort(3306), strDatabase(d), strUser(u), strPassword(p) { }

   TMyMySQL(TMyMySQL const& ref) {
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      strUser = ref.strUser;
      strPassword = ref.strPassword;
   }
   TMyMySQL(TMyMySQL&& ref) noexcept { swap(ref); }


   TMyMySQL& operator = (TMyMySQL const& ref) {
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      strUser = ref.strUser;
      strPassword = ref.strPassword;
      return *this;
   }

   TMyMySQL& operator = (TMyMySQL&& ref) noexcept {
      swap(ref);
      return *this;
   }

   void swap(TMyMySQL& ref) noexcept {
      using std::swap;
      swap(strHost, ref.strHost);
      swap(iPort, ref.iPort);
      swap(strDatabase, ref.strDatabase);
      swap(strUser, ref.strUser);
      swap(strPassword, ref.strPassword);
   }

   std::string const& Host(void) const { return strHost; }
   int                Port(void) const { return iPort; }
   std::string const& Database(void) const { return strDatabase; }
   std::string const& User(void) const { return strUser; }
   std::string const& Password(void) const { return strPassword; }

   std::string GetInformations(void) const { return std::format("MySQL Server {}:{}/{}", strHost, iPort, strDatabase); }
};


template <typename ty>
struct is_my_db_credentials {
   static constexpr bool value = 
      std::is_same<std::remove_cvref_t<ty>, TMyMSSQL>::value ||
      std::is_same<std::remove_cvref_t<ty>, TMyOracle>::value ||
      std::is_same<std::remove_cvref_t<ty>, TMyMySQL>::value;
};

template <typename ty>
concept my_db_credentials = is_my_db_credentials<ty>::value &&
   requires (ty t) {
      { t.GetInformations() } -> std::convertible_to <std::string>;
};

