//
// Created by gregory on 29/01/2020.
//

#ifndef ZIA_LOG_H
#define ZIA_LOG_H

#include <cstdint>
#include <string>

class Log {

public:
    enum type {
        DEBUG,
        RELEASE
    };

    explicit Log(Log::type);
    ~Log();

private:
    std::string m_buffer;
    uint64_t m_line;
    uint64_t m_nbrError;
    uint64_t m_nbrWarn;
    uint64_t m_nbrInfos;
    Log::type m_instance;

};

#ifdef DEBUG
static const Log LOG(Log::DEBUG);
#else
static const Log LOG(Log::RELEASE);
#endif

#endif //ZIA_LOG_H
