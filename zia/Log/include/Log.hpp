//
// Created by gregory on 29/01/2020.
//

#ifndef ZIA_LOG_HPP
#define ZIA_LOG_HPP

#include <cstdint>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#include <fstream>

#define SYSERROR()  GetLastError()
#else
    #include <errno.h>
    #define SYSERROR()  errno
#endif

class Log {

public:
    enum instanceType {
        Debug,
        Release
    };
    enum typeLog {
        WARN,
        INFOS,
        ERRORS
    };

    explicit Log(Log::instanceType) noexcept;

    ~Log() noexcept;

    void writeLog(Log::typeLog logType, std::string msg, const std::string &funcCalling, std::string file, const std::string &lineInFile);

private:
    std::string getCurrentTimeForFileName();

    std::string createTimeStampLog();

    void writeDebug(Log::typeLog logType, std::string& msg, const std::string &funcCalling, std::string &file, const std::string &lineInFile);

    void writeRelease(Log::typeLog logType, std::string& msg, const std::string &funcCalling);

    struct tm *getLocalTime();

private:
    std::ofstream m_fileStream;
    std::string m_filename;
    uint64_t m_line;
    uint64_t m_nbrError;
    uint64_t m_nbrWarn;
    uint64_t m_nbrInfos;
    Log::instanceType m_instance;
};

extern Log LOG;

#define WARNLOG(MSG) LOG.writeLog(Log::WARN, MSG, __FUNCTION__, __FILE__, std::to_string(__LINE__))
#define INFOSLOG(MSG) LOG.writeLog(Log::INFOS, MSG, __FUNCTION__, __FILE__, std::to_string(__LINE__))
#define ERRLOG(MSG) LOG.writeLog(Log::ERRORS, MSG, __FUNCTION__, __FILE__, std::to_string(__LINE__))

#endif //ZIA_LOG_HPP
