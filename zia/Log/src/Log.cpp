//
// Created by gregory on 29/01/2020.
//

#include "Log.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include <iostream>

Log::Log(Log::type type) : m_line(0) {
    m_instance = type;
}

Log::~Log() {
    auto now = std::chrono::system_clock::now();
    auto date = std::chrono::system_clock::to_time_t(now);
    std::string date_str = std::ctime(&date);

    if (m_nbrError == 0)
        std::cerr << "No error occured during this execution." << std::endl;

    if (m_instance == Log::DEBUG)
        std::ofstream m_fileStream("DEBUG_REPORT.log", std::ofstream::out);
    else if (m_instance == Log::RELEASE)
        std::ofstream m_fileStream("report" + date_str + ".log", std::ofstream::out);
}