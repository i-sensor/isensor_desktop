#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <QString>
#include <fstream>

enum LOG_LEVEL
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

enum LOGGING_RESULTS
{
    FILE_IS_NOT_OPENED = -2,
    INVALID_LOG_LEVEL,
    SUCCESS
};

/*
 * Logger class
 * is not thread safe
 */
class Logger
{

public:
    Logger(const QString& csLogFileName, const QString& csLogFilePath, const QString& csOwnerName, const LOG_LEVEL& ceDefaultLogLevel = LOG_LEVEL::INFO);
    ~Logger();

public: //methods

    /*
     * setLogLevel - sets level for logger
     */
    void setLogLevel(const LOG_LEVEL ceLogLevel);

    /*
     * log - writes logs to file
     */
    int log(const LOG_LEVEL& ceLogLevel, const char* cszLogMessage, ...);

    /*
     * getLogger - creates logger
     */
    static Logger* getLogger(const QString& csLogFileName, const QString& csLogFilePath, const QString& csOwnerName, const LOG_LEVEL& ceDefaultLogLevel = LOG_LEVEL::INFO);

private: //methods

    /*
     * getDateTime - forms time&date
     */
    QString getDateTime();

    /*
     * convertLogLevelToString - converts log level of the logger into string
     */
    QString convertLogLevelToString(const LOG_LEVEL eLevel);

private: //fields
    std::fstream m_file;
    QString m_sLogFileName;
    QString m_sLogFilePath;
    QString m_sOwnerName;
    LOG_LEVEL m_eLogLevel = LOG_LEVEL::INFO; //default log level

};

#endif // _LOGGER_H_
