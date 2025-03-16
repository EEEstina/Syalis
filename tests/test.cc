#include <iostream>
#include <thread>
#include "../syalis/log.h"
#include "../syalis/util.h"

int main(int argc, char** argv) {
    syalis::Logger::ptr logger(new syalis::Logger);
    logger->addAppender(syalis::LogAppender::ptr(new syalis::StdoutLogAppender));

    syalis::FileLogAppender::ptr file_appender(new syalis::FileLogAppender("./log.txt"));

    syalis::LogFormatter::ptr fmt(new syalis::LogFormatter("%d%T%p%T%m\n"));
    file_appender->setFormatter(fmt);
    
    file_appender->setLevel(syalis::LogLevel::ERROR);

    logger->addAppender(file_appender);

    // syalis::LogEvent::ptr event(new syalis::LogEvent(__FILE__, __LINE__, 0, syalis::GetThreadId(), syalis::GetFiberId(), time(0)));
    // event->getSS() << "hello syalis" << std::endl;

    // logger->log(syalis::LogLevel::DEBUG, event);

    std::cout << "hello my log" << std::endl;

    SYALIS_LOG_INFO(logger) << "TEST";
    SYALIS_LOG_ERROR(logger) << "TEST ERROR";

    SYALIS_LOG_FMT_ERROR(logger, "TEST FMT ERROR %s", "aa");

    auto l = syalis::LoggerMgr::GetInstance()->getLogger("xx");
    SYALIS_LOG_INFO(l) << "xxx";

    return 0;
}
