#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <memory>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <QString>

class Logger
{
public:

    Logger(const std::string& file_name);
    Logger();
    void info(const QString& msg);
    void warn(const QString& msg);
    void error(const QString& msg);

private:
    std::shared_ptr<spdlog::logger> logger;



};

#endif // LOGGER_H
