#pragma once
#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/SplitterChannel.h>

#include <iostream>
#include <string>


namespace Chronos {
inline void Log(const std::string &msg) { std::cout << msg << std::endl; }
void Log(const std::wstring &msg, unsigned int level = 0);

/**
 * @brief 包装一下
 *
 */
class Logger {
   private:
    Poco::Logger *_logger;
    Logger(Poco::Logger &logger);

   public:
    Logger() { _logger = nullptr; }
    Logger(const Logger &logger) { _logger = logger._logger; }
    void info(const std::string &msg);
    void debug(const std::string &msg);
    void warning(const std::string &msg);
    void fatal(const std::string &msg);

    static Logger root();
    static Logger get(const std::string &name);
};

class LoggerConfig {
   private:
    Poco::AutoPtr<Poco::SplitterChannel> splitterChannel;

   public:
    void initLogger();
};
}  // namespace Chronos