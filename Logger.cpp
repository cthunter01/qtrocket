
/// \cond
// C headers
// C++ headers
#include <iostream>

// 3rd party headers
/// \endcond

// qtrocket headers
#include "Logger.h"

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance()
{
    if(!instance)
    {
        instance = new Logger();
    }
    return instance;
}

Logger::Logger()
{
    outFile.open("log.txt");
}

Logger::~Logger()
{
    outFile.close();
}

void Logger::log(std::string_view msg, const LogLevel& lvl)
{
    std::lock_guard<std::mutex> lck(mtx);
    // The fallthrough is intentional. Logging is automatically enabled for
    // all levels at or lower than the current level.
    switch(currentLevel)
    {
      case LogLevel::PERF:
       if(lvl == LogLevel::PERF)
         {
            outFile << "[PERF] " << msg << std::endl;
            std::cout << "[PERF] " << msg << "\n";
         }
         [[fallthrough]];
      case LogLevel::DEBUG:
          if(lvl == LogLevel::DEBUG)
         {
            outFile << "[DEBUG] " << msg << std::endl;
             std::cout << "[DEBUG] " << msg << "\n";
         }
         [[fallthrough]];
      case LogLevel::INFO:
          if(lvl == LogLevel::INFO)
         {
            outFile << "[INFO] " << msg << std::endl;
             std::cout << "[INFO] " << msg << "\n";
         }
         [[fallthrough]];
      case LogLevel::WARN:
          if(lvl == LogLevel::WARN)
         {
            outFile << "[WARN] " << msg << std::endl;
             std::cout << "[WARN] " << msg << "\n";
         }
         [[fallthrough]];
      // Regardless of what level is set, ERROR is always logged, so
      // rather than explicitly check for the ERROR case, we just use default case
      default:
          if(lvl == LogLevel::ERROR)
         {
            outFile << "[ERROR] " << msg << std::endl;
             std::cout << "[ERROR] " << msg << "\n";
         }
   }
}

void Logger::setLogLevel(const LogLevel& lvl)
{
   currentLevel = lvl;
}

void Logger::log(std::ostream& o, const std::string& msg)
{
   std::lock_guard<std::mutex> lck(mtx);
   o << msg << std::endl;
}

