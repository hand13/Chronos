#include <codecvt>
#include <iostream>
#include "Log.h"

#include <Poco/AutoPtr.h>
#include <Poco/Channel.h>
#include <Poco/FileChannel.h>
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/SplitterChannel.h>
#include <Poco/AsyncChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>

using Poco::AutoPtr;
using Poco::PatternFormatter;
using Poco::SimpleFileChannel;
using Poco::ConsoleChannel;
using Poco::SplitterChannel;
using Poco::AsyncChannel;
using Poco::FormattingChannel;
using Poco::Channel;

namespace Chronos {

    void Log(const std::wstring& msg,unsigned int level) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversion;
        std::string out = conversion.to_bytes(msg);
        if(level == 0){
            std::cout<<out<<std::endl;
        }else {
            std::cerr<<out<<std::endl;
        }
    }

    Logger::Logger(Poco::Logger & logger):_logger(&logger){
    }

    void Logger::info(const std::string& msg){
        _logger->information(msg);
    }
    void Logger::debug(const std::string& msg){
        _logger->debug(msg);
    }

    void Logger::warning(const std::string& msg){
        _logger->warning(msg);
    }
    void Logger::fatal(const std::string& msg){
        _logger->fatal(msg);
    }

    Logger Logger::root(){
        return Logger(Poco::Logger::root());
    }

    Logger Logger::get(const std::string& name){
        return Logger(Poco::Logger::get(name));
    }

    static AutoPtr<Channel> createFileChannel(){
        Poco::AutoPtr<Poco::SimpleFileChannel> file(new Poco::SimpleFileChannel("test.log"));
        AutoPtr<PatternFormatter> pf(new PatternFormatter);
        //%U filepath %O filename %u line
        pf->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s : %t");
        AutoPtr<FormattingChannel> fc(new FormattingChannel(pf,file));
        AutoPtr<AsyncChannel> res(new AsyncChannel(fc));
        return res;
    }

    static AutoPtr<Channel> createConsoleChannel(){
        Poco::AutoPtr<Poco::ConsoleChannel> cons(new Poco::ConsoleChannel);
        AutoPtr<PatternFormatter> pf(new PatternFormatter);
        pf->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s : %t");
        AutoPtr<FormattingChannel> fc(new FormattingChannel(pf,cons));
        AutoPtr<AsyncChannel> res(new AsyncChannel(fc));
        return res;
    }


    void LoggerConfig::initLogger(){
        splitterChannel= new SplitterChannel;
        splitterChannel->addChannel(createFileChannel());
        splitterChannel->addChannel(createConsoleChannel());
        Poco::Logger::root().setChannel(splitterChannel);
        Poco::Logger::root().information("logger inited");
    }
}