#include "logger.h"
#include <memory>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

Logger::Logger(){}

Logger::Logger(const std::string& file_name) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("[%H:%M:%S] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_name, 1024 * 1024 * 5, 3);
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    this->logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
    spdlog::register_logger(this->logger);
    this->logger->set_level(spdlog::level::debug);
    this->logger->flush_on(spdlog::level::debug);
}

void Logger::info(const QString& msg){
    this->logger->info(msg.toStdString());

}

void Logger::warn(const QString& msg){
    logger->warn(msg.toStdString());

}

void Logger::error(const QString& msg){
    logger->error(msg.toStdString());

}
