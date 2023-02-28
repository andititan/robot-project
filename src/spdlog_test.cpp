#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

void logger_output(std::string text){
    auto mylogger = spdlog::basic_logger_mt("mylogger", "logs.txt");
    mylogger->info(text);
}

int main(){
    logger_output("Hello world");
}
