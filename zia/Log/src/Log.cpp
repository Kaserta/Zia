//
// Created by gregory on 29/01/2020.
//

#include <fstream>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Log.hpp"

Log::Log(Log::instanceType type) noexcept : m_line(0), m_nbrWarn(0), m_nbrInfos(0), m_nbrError(0) {
    std::string date_str = getCurrentTimeForFileName();

    m_instance = type;
    if (m_instance == Debug)
        m_filename = "DEBUG_REPORT.log";
    else if (m_instance == Release)
        m_filename = "report_" + date_str + ".log";
    m_fileStream.open(m_filename, std::ofstream::out | std::ofstream::app);
    if (!m_fileStream.is_open()) {
        std::cerr << "Failed to open file : " << m_filename << SYSERROR() << std::endl;
    }
}

Log::~Log() noexcept {
    if (m_nbrError > 0)
        std::cerr << m_nbrError << " Errors happened during the execution of the program." << std::endl;
    if (m_fileStream.is_open()) {
        std::cout << "You should check the log file: " << m_filename << std::endl;
        std::cout << "There was " << m_line << " line wrote in it after this run." << std::endl;
    }
    m_fileStream.close();
}

struct tm *Log::getLocalTime() {
    auto time = std::time(nullptr);
    return std::localtime(&time);
}

std::string Log::getCurrentTimeForFileName() {
    std::stringstream stringStream;
    std::string date;

    stringStream << std::put_time(getLocalTime(), "%F_%T"); // ISO 8601 without timezone information.
    date = stringStream.str();
    std::replace(date.begin(), date.end(), ':', '-');
    return date;
}

std::string Log::createTimeStampLog() {
    std::stringstream stringStream;
    std::string date;

    stringStream << std::put_time(getLocalTime(), "%m/%d %T");
    return stringStream.str();
}

void Log::writeLog(Log::typeLog logType, std::string msg, const std::string &funcCalling, std::string file,
                   const std::string &lineInFile) {
    if (m_instance == Debug)
        writeDebug(logType, msg, funcCalling, file, lineInFile);
    else if (m_instance == Release)
        writeRelease(logType, msg, funcCalling);
}

void Log::writeDebug(Log::typeLog logType, std::string& msg, const std::string &funcCalling, std::string &file,
                     const std::string &lineInFile) {
    file.erase(0, file.find_last_of("\\/") + 1);
    switch (logType) {
        case WARN:
            m_fileStream << std::to_string(m_line) + ": " + createTimeStampLog() + "\tWARNING\t(file: " + file + " | func " + funcCalling + " | line " +
                    lineInFile + ")\t" + msg << std::endl;
            m_nbrWarn++;
            break;
        case INFOS:
            m_fileStream << std::to_string(m_line) + ": " + createTimeStampLog() + "\tINFOS\t(file: " + file + " | func " + funcCalling + " | line " +
                            lineInFile + ")\t" + msg << std::endl;
            m_nbrInfos++;
            break;
        case ERRORS:
            m_fileStream << std::to_string(m_line) + ": " + createTimeStampLog() + "\tERROR\t(file: " + file + " | func " + funcCalling + " | line " +
                    lineInFile + ")\t" + msg << std::endl;
            m_nbrError++;
            break;
    }
    m_line++;
}

void Log::writeRelease(Log::typeLog logType, std::string &msg, const std::string &funcCalling) {
    switch (logType) {
        case WARN:
            m_fileStream << std::to_string(m_line) + ": " + createTimeStampLog() + "\tWARNING\t(func " + funcCalling + ")\t" + msg << std::endl;
            m_nbrWarn++;
            break;
        case INFOS:
            m_fileStream << std::to_string(m_line) + ": " + createTimeStampLog() + "\tINFOS\t(func " + funcCalling + ")\t" + msg << std::endl;
            m_nbrInfos++;
            break;
        case ERRORS:
            m_fileStream << std::to_string(m_line) + ": " + createTimeStampLog() + "\tERROR\t(func " + funcCalling + ")\t" + msg << std::endl;
            m_nbrError++;
            break;
    }
    m_line++;
}

#ifdef DEBUG
Log LOG(Log::Debug);
#else
Log LOG(Log::Release);
#endif
