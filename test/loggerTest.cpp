//
// Created by gregory on 03/02/2020.
//

#include <iostream>
#include "gtest/gtest.h"
#include "Log.hpp"

TEST(LogLibrary, warningLog) {
    std::ifstream stream;
    std::stringstream ss1, ss2;
    std::string date;
    std::string line;
    std::vector<std::string> allLine;

    auto time = std::time(nullptr);
    WARNLOG("test warning");
    ss1 << std::put_time(std::localtime(&time), "%F"); // ISO 8601 without timezone information.
    date = ss1.str();
    stream.open("report_" + date + ".log");
    while (std::getline(stream, line, '\n'));
    ss2 << std::put_time(std::localtime(&time), "%m/%d %T");
    ASSERT_EQ(line, "0: " + ss2.str() + "\tWARNING\t(func LogLibrary_warningLog_Test::TestBody)\ttest warning");
}

TEST(LogLibrary, infosLog) {
    std::ifstream stream;
    std::stringstream ss1, ss2;
    std::string date;
    std::string line;
    std::vector<std::string> allLine;

    auto time = std::time(nullptr);
    INFOSLOG("test infos");
    ss1 << std::put_time(std::localtime(&time), "%F"); // ISO 8601 without timezone information.
    date = ss1.str();
    stream.open("report_" + date + ".log");
    while (std::getline(stream, line, '\n'));
    ss2 << std::put_time(std::localtime(&time), "%m/%d %T");
    ASSERT_EQ(line, "1: " + ss2.str() + "\tINFOS\t(func LogLibrary_infosLog_Test::TestBody)\ttest infos");
}

TEST(LogLibrary, errorLog) {
    std::ifstream stream;
    std::stringstream ss1, ss2;
    std::string date;
    std::string line;
    std::vector<std::string> allLine;

    auto time = std::time(nullptr);
    ERRLOG("test error");
    ss1 << std::put_time(std::localtime(&time), "%F"); // ISO 8601 without timezone information.
    date = ss1.str();
    stream.open("report_" + date + ".log");
    while (std::getline(stream, line, '\n'));
    ss2 << std::put_time(std::localtime(&time), "%m/%d %T");
    ASSERT_EQ(line, "2: " + ss2.str() + "\tERROR\t(func LogLibrary_errorLog_Test::TestBody)\ttest error");
}