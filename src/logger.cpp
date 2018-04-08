#include "logger.hpp"

std::string Logger::replaceSubstring(const std::string& target, const std::string& substring, 
        const std::string& replaceWith)
{
    std::string output = target;
    size_t pos = output.find(substring);
    while( pos != std::string::npos)
    {
        output.replace(pos, substring.size(), replaceWith);
        pos = output.find(substring, pos + substring.size());
    }
    return output;
}

const std::string Logger::logLevelToString(const int logLevel)
{
    static std::map<int, std::string> stringLogLevels = {
        {logLevels::DEBUG, "DEBUG"},
        {logLevels::INFO, "INFO"},
        {logLevels::WARNING, "WARNING"},
        {logLevels::ERROR, "ERROR"},
        {logLevels::CRITICAL, "CRITICAL"},
        };
    return stringLogLevels[logLevel];
}

std::string Logger::formatDate(const std::string& text)
{

    std::string output = text;
    time_t now = time(0);
    tm *tme = gmtime(&now);

    std::string day = std::to_string(tme->tm_mday);
    output = Logger::replaceSubstring(output, "%D", day);

    std::string month = std::to_string(tme->tm_mon + 1);
    output = Logger::replaceSubstring(output, "%M", month);

    std::string year = std::to_string(tme->tm_year + 1900);
    output = Logger::replaceSubstring(output, "%Y", year);

    std::string hour = std::to_string(tme->tm_hour);
    output = Logger::replaceSubstring(output, "%h", hour);

    std::string minutes = std::to_string(tme->tm_min);
    output = Logger::replaceSubstring(output, "%m", minutes);

    std::string seconds = std::to_string(tme->tm_sec);
    output = Logger::replaceSubstring(output, "%s", seconds);
    return output;
}

std::string Logger::formatFileName(const std::string& filename)
{
    std::string output = Logger::formatDate(filename);
    return output;
}

std::string Logger::formatLog(const int debugLevel, 
        const std::string& logText, 
        const std::string& logFormat)
{
    std::string output = logFormat;
    output = replaceSubstring(output, "%t", logText);
    output = replaceSubstring(output, "%dl", Logger::logLevelToString(debugLevel));
    output = Logger::formatDate(output);
   return output;
}

void Logger::writeLog(const int debugLevel, const std::string& logText)
{
    const std::string formatedLog = Logger::formatLog(debugLevel, logText, logFormatPattern);

    if(logToConsole)
        std::cout << formatedLog << "\n";
    if(logFile != nullptr)
        *logFile << formatedLog << "\n";
}

 Logger::Logger(int defaultLogLevel):
    defaultLogLevel(defaultLogLevel),
    logToConsole(true),
    logFile(nullptr),
    logFormatPattern("[%Y/%M/%D %h:%m:%s] %dl: %t")
{}

 Logger::~Logger()
{
    closeFile();
}

void Logger::closeFile()
{
    if(logFile != nullptr)
    {
        delete logFile;
        logFile = nullptr;
    }
}

void Logger::setLogToConsole(bool loggingToConsole)
{
    logToConsole = loggingToConsole;
}

void Logger::openFile(const std::string &fileName)
{
    closeFile();
    std::string formatedFileName = Logger::formatFileName(fileName);
    logFile = new std::fstream(formatedFileName, std::ios_base::out | std::ios_base::app);
}

void Logger::setLogFormat(const std::string& format)
{
    logFormatPattern = format; 
}

void Logger::log(const std::string &text, const int logLevel)
{
    if(defaultLogLevel <= logLevel)
        writeLog(logLevel, text);
}

void Logger::log(const std::ostringstream &os, const int logLevel)
{
    if(defaultLogLevel <= logLevel)
        writeLog(logLevel, os.str());
}
