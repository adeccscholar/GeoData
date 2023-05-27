#pragma once

#include <string>
#include <tuple>
#include <format>

using namespace std::literals;

class TMyCredential {
private:
   std::tuple<std::string, std::string, bool> data;
public:

   constexpr TMyCredential(std::string const& usr, std::string const& pwd, bool bis = false) : data { usr, pwd, bis } { }
   constexpr TMyCredential() : TMyCredential(""s, ""s, false) { }
   TMyCredential(TMyCredential const& ref) : data(ref.data) { }
   TMyCredential(TMyCredential&& ref) noexcept { swap(ref);  }
   virtual ~TMyCredential() = default;

   TMyCredential& operator = (TMyCredential const& ref) {
      data = ref.data;
      return *this;
      }

   TMyCredential& operator = (TMyCredential&& ref) noexcept {
      swap(ref);
      return *this;
      }

   auto operator <=> (TMyCredential const& ref) const = default;



   void swap(TMyCredential& ref) noexcept {
      std::swap(data, ref.data);
      }

   std::string const& User(void) const { return std::get<0>(data); }
   std::string const& Password(void) const { return std::get<1>(data); }
   bool        Integrated(void) const { return std::get<2>(data); }


   std::string GetCredential(bool boSecure = true) const {
      if (Integrated()) return "connected with integrated security"s;
      else return std::format("User: {} Password: {}", User(), boSecure ? "*****"s : Password());
      }

};

class TMyMSSQL : public TMyCredential {
   friend void swap(TMyMSSQL& lhs, TMyMSSQL& rhs) noexcept { lhs.swap(rhs);  }
private:
   std::string strServer;    ///< datbase server, optional \ instance name
   std::string strDatabase;  ///< database name
public:
   TMyMSSQL(std::string const& s, std::string const& d, bool b, std::string const& u, std::string const& p) :
      TMyCredential(u, p, b), strServer(s), strDatabase(d) { }

   TMyMSSQL(void) : TMyMSSQL("(local)"s, "master"s, true, ""s, ""s) { }
   TMyMSSQL(std::string const& db) : TMyMSSQL("(local)"s, db, true, ""s, ""s) { }
   TMyMSSQL(std::string const& srv, std::string const& db) : TMyMSSQL(srv, db, true, ""s, ""s) { }

   TMyMSSQL(TMyMSSQL const& ref) :
      TMyCredential(ref), strServer(ref.strServer), strDatabase(ref.strDatabase) { }

   TMyMSSQL(TMyMSSQL&& ref) noexcept { swap(ref);  }

   virtual ~TMyMSSQL(void) { }

   TMyMSSQL& operator = (TMyMSSQL const& ref) {
      strServer = ref.strServer;
      strDatabase = ref.strDatabase;
      static_cast<TMyCredential&>(*this).operator = (static_cast<TMyCredential const&>(ref));
      return *this;
      }

   TMyMSSQL& operator = (TMyMSSQL&& ref) noexcept {
      swap(ref);
      return *this;
      }

   TMyMSSQL& operator += (TMyCredential const& ref) {
      static_cast<TMyCredential&>(*this).operator = (ref);
      return *this;
      }

   TMyMSSQL& operator += (TMyCredential&& ref) {
      static_cast<TMyCredential&>(*this).swap(ref);
      return *this;
      }

   void swap(TMyMSSQL& ref) noexcept {
      using std::swap;
      swap(strServer,    ref.strServer);
      swap(strDatabase,  ref.strDatabase);
      static_cast<TMyCredential&>(*this).swap(static_cast<TMyCredential&>(ref));
      }

   // Selektoren

   std::string const& Server(void) const { return strServer; }
   std::string const& Database(void) const { return strDatabase; }

   std::string GetDatabase(void) const { return std::format("{}/{}", strServer, strDatabase); }
   std::string GetServer(void) const { return std::format("{} {}", ServerType(), GetDatabase()); }
   std::string GetInformation(void) const { return std::format("{} ({})", GetServer(), GetCredential()); }

   static constexpr std::string ServerType(void) { return "MS SQL"s; }
   static constexpr bool HasIntegratedSecurity(void) { return true; }

};


class TMyOracle : public TMyCredential {
   friend void swap(TMyOracle& lhs, TMyOracle& rhs) { lhs.swap(rhs); }
private:
   bool        boUseTNS = true;
   std::string strService = "XE";
   std::string strHost = "localhost";
   int         iPort = 1521;
   std::string strDatabase = "XE";
public:
   TMyOracle() : TMyOracle("localhost"s, 1521, ""s, ""s, ""s) { }
   TMyOracle(std::string const& hst, int prt, std::string const& db, std::string const& usr, std::string const& pwd) :
      TMyCredential(usr, pwd), boUseTNS(false), strHost(hst), iPort(prt), strService(""s), strDatabase(db) { }
   TMyOracle(std::string const& d, std::string const& u, std::string const& p) :
      TMyCredential(u,p), boUseTNS(false), strHost("localhost"), iPort(1521), strService(""s), strDatabase(d) { }
   TMyOracle(bool usetns, std::string const& d, std::string const& u, std::string const& p) :
      TMyCredential(u,p), boUseTNS(usetns), strHost(""), iPort(1521), strService(d), strDatabase(d) { }

   TMyOracle(TMyOracle const& ref) {
      boUseTNS = ref.boUseTNS;
      strService = ref.strService;
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      static_cast<TMyCredential&>(*this).operator = (static_cast<TMyCredential const&>(ref));
   }

   TMyOracle(TMyOracle&& ref) noexcept { swap(ref); }

   TMyOracle& operator = (TMyOracle const& ref) {
      boUseTNS = ref.boUseTNS;
      strService = ref.strService;
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      return *this;
   }


   TMyOracle& operator = (TMyOracle&& ref) noexcept {
      swap(ref);
      return *this;
      }


   TMyOracle& operator += (TMyCredential const& ref) {
      static_cast<TMyCredential&>(*this).operator = (ref);
      return *this;
      }

   TMyOracle& operator += (TMyCredential&& ref) {
      static_cast<TMyCredential&>(*this).swap(ref);
      return *this;
      }


   void swap(TMyOracle& ref) noexcept {
      using std::swap;
      static_cast<TMyCredential&>(*this).swap(static_cast<TMyCredential&>(ref));
      swap(boUseTNS, ref.boUseTNS);
      swap(strService, ref.strService);
      swap(strHost, ref.strHost);
      swap(iPort, ref.iPort);
      swap(strDatabase, ref.strDatabase);
   }

   bool               UseTNS(void) const { return boUseTNS; }
   std::string const& Service(void) const { return strService; }
   std::string const& Host(void) const { return strHost; }
   int                Port(void) const { return iPort; }
   std::string const& Database(void) const { return strDatabase; }

   std::string GetDatabase(void) const { 
      if (boUseTNS) return std::format("Service={}", strService);
      else          return std::format("{}:{}/{}", strHost, iPort, strDatabase);
      }

   std::string GetServer(void) const { return std::format("{} {}", ServerType(), GetDatabase()); }
   std::string GetInformation(void) const { return std::format("{} ({})", GetServer(), GetCredential()); }

   static constexpr std::string ServerType(void) { return "Oracle"s; }
   static constexpr bool HasIntegratedSecurity(void) { return false; }

};



class TMyMySQL : public TMyCredential {
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
      TMyCredential(usr, pwd), strHost(hst), iPort(prt), strDatabase(db) { }
   TMyMySQL(std::string const& d, std::string const& u, std::string const& p) :
      TMyCredential(u,p), strHost("localhost"), iPort(3306), strDatabase(d) { }

   TMyMySQL(TMyMySQL const& ref) {
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      static_cast<TMyCredential&>(*this).operator = (static_cast<TMyCredential const&>(ref));
      }

   TMyMySQL(TMyMySQL&& ref) noexcept { swap(ref); }


   TMyMySQL& operator = (TMyMySQL const& ref) {
      strHost = ref.strHost;
      iPort = ref.iPort;
      strDatabase = ref.strDatabase;
      static_cast<TMyCredential&>(*this).operator = (static_cast<TMyCredential const&>(ref));
      return *this;
      }

   TMyMySQL& operator = (TMyMySQL&& ref) noexcept {
      swap(ref);
      return *this;
   }

   void swap(TMyMySQL& ref) noexcept {
      using std::swap;
      static_cast<TMyCredential&>(*this).swap(static_cast<TMyCredential&>(ref));
      swap(strHost, ref.strHost);
      swap(iPort, ref.iPort);
      swap(strDatabase, ref.strDatabase);
   }

   std::string const& Host(void) const { return strHost; }
   int                Port(void) const { return iPort; }
   std::string const& Database(void) const { return strDatabase; }

   std::string GetDatabase(void) const { return std::format("{}:{}/{}", strHost, iPort, strDatabase); }
   std::string GetServer(void) const { return std::format("{} {}", ServerType(), GetDatabase()); }
   std::string GetInformation(void) const { return std::format("{} ({})", GetServer(), GetCredential()); }

   static constexpr std::string ServerType(void) { return "MySQL"s; }
   static constexpr bool HasIntegratedSecurity(void) { return false; }

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
   std::is_base_of<TMyCredential, ty>::value &&
   std::is_default_constructible<ty>::value &&
   std::is_copy_constructible<ty>::value&&
   std::is_move_constructible<ty>::value&&
   std::has_virtual_destructor<ty>::value&&
   std::is_assignable<ty&, ty const&>::value&&
   std::is_assignable<ty&, ty&&>::value&&

   requires (ty t) {
      { ty::ServerType() } -> std::convertible_to<const std::string>;
      { ty::HasIntegratedSecurity() } -> std::same_as<bool>;
      { t.GetDatabase() } -> std::same_as<std::string>;
      { t.GetServer() } -> std::same_as<std::string>;
      { t.GetInformation() } -> std::convertible_to <std::string>;
         requires requires (TMyCredential const& p, TMyCredential && pref) {
            { t += p } -> std::same_as<ty&>;
            { t += std::move(pref) } -> std::same_as<ty&>;
      };
   };

