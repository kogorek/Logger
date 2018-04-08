#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <map>

enum logLevels
{
    DEBUG = 0, INFO, WARNING, ERROR, CRITICAL, NONE
};

class Logger
{
    private:
        int defaultLogLevel;
        bool logToConsole;
        std::fstream *logFile;
        std::string logFormatPattern;

        static std::string replaceSubstring(const std::string& target, 
                const std::string& substring, 
                const std::string& replaceWith);
        static const std::string logLevelToString(const int logLevel);
        static std::string formatDate(const std::string& text);
        static std::string formatFileName(const std::string& filename);
        static std::string formatLog(const int debugLevel, 
                const std::string& logText, 
                const std::string& logFormat);

        void writeLog(const int debugLevel, const std::string& logText);

    public:
        Logger(int defaultLogLevel = logLevels::ERROR);
        ~Logger();
        void closeFile();
        void setLogToConsole(bool loggingToConsole);
        void openFile(const std::string &fileName);
        void setLogFormat(const std::string& format);
        void log(const std::string &text, const int logLevel = logLevels::INFO);
        void log(const std::ostringstream &os, const int logLevel = logLevels::INFO);
};

#endif //LOGGER_HPP
