//
// Created by x on 19-11-23.
//
#include <gtest/gtest.h>
#include <glog/logging.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

TEST(LOG, SIMPLE)
{
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");

    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", {});
    SPDLOG_DEBUG("Some debug message");

    // Set the default logger to file logger
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
    spdlog::set_default_logger(file_logger);
}
TEST(LOG, GLOG){
    google::InitGoogleLogging("/tmp/glgo.log");
    google::SetLogDestination(google::INFO, "log/"); // 把日志同时记录文件，最低级别为INFO

    // 通过GFLAGS来设置参数，更多选项可以在logging.cc里面查询
    // 日志等级分为INFO, WARNING, ERROR, FATAL,如果是FATAL级别这直接运行报错
    FLAGS_stderrthreshold = google::INFO;
    FLAGS_colorlogtostderr = true;

    LOG(INFO) << "Hello GLOG";
    LOG(WARNING) << "Hello GLOG";
    // 条件输出
    LOG_IF(INFO, 20 > 10) << "20 > 10";
    // 频率输出，本质上是通过google::COUNTER这个计数机实现的
    for (int i = 0; i < 10; i++)
    {
        LOG_EVERY_N(ERROR, 3) << "每隔3次输出一次 " << i;
        LOG_FIRST_N(ERROR, 2) << "前两次输出 " << i;
        LOG_IF_EVERY_N(WARNING, 1 < 2, 2) << "条件输出+频率" << google::COUNTER;
    }
    google::ShutdownGoogleLogging();
}
TEST(LOG, EASYLOG){
}