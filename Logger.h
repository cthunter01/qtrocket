#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

/// \cond
// C headers
// C++ headers
#include <fstream>
#include <mutex>
#include <string_view>

// 3rd party headers
/// \endcond

/**
 * @todo write docs
 */
class Logger
{
public:
   enum class LogLevel
   {
      ERROR,
      WARN,
      INFO,
      DEBUG,
      PERF
   };

   static Logger* getInstance();
   ~Logger();

   Logger(Logger const&) = delete;
   Logger(Logger&&) = delete;
   Logger& operator=(Logger const&) = delete;
   Logger& operator=(Logger&&) = delete;

   void setLogLevel(const LogLevel& lvl);
   
   inline void error(std::string_view msg) { log(msg, LogLevel::ERROR); }
   inline void warn(std::string_view msg)  { log(msg, LogLevel::WARN); }
   inline void info(std::string_view msg)  { log(msg, LogLevel::INFO); }
   inline void debug(std::string_view msg) { log(msg, LogLevel::DEBUG); }
   inline void perf(std::string_view msg) { log(msg,  LogLevel::PERF); }

   void log(std::ostream& o, const std::string& msg);

private:

   void log(std::string_view msg, const LogLevel& lvl);

   LogLevel currentLevel;
   std::ofstream outFile;
   static Logger* instance;
   std::mutex mtx;
   Logger();
};

#endif // UTILS_LOGGER_H
