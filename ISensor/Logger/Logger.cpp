#include "Logger.h"

#include <QDateTime>

#include <iomanip>
#include <stdarg.h>

Logger::Logger(const QString& csLogFileName, const QString& csLogFilePath, const QString& csOwnerName, const LOG_LEVEL& ceDefaultLogLevel)
    : m_sLogFileName{csLogFileName}, m_sLogFilePath(csLogFilePath), m_sOwnerName(csOwnerName), m_eLogLevel{ceDefaultLogLevel}
{
    std::string sLogFile = csLogFilePath.toStdString() + csLogFileName.toStdString();
    m_file.open(sLogFile, std::ios::app | std::ios::out);
}

Logger::~Logger()
{
    if(m_file.is_open())
    {
        m_file.close();
    }
}

int Logger::log(const LOG_LEVEL& ceLogLevel, const char* cszLogMessage, ...)
{
    int iResult = LOGGING_RESULTS::SUCCESS;

    do
    {
        if(!m_file.is_open())
        {
            iResult = LOGGING_RESULTS::FILE_IS_NOT_OPENED;
            break;
        }

        if(m_eLogLevel > ceLogLevel) //If provided log level is not valid
        {
            iResult = LOGGING_RESULTS::INVALID_LOG_LEVEL;
            break;
        }

        //prepare all parts for log message
        QString sDateTime = getDateTime();
        QString sLogLevel = convertLogLevelToString(ceLogLevel);

        //main message
        va_list args;
        va_start(args, cszLogMessage);

        char szMessageAndAdditionalArgs[256];
        vsnprintf(szMessageAndAdditionalArgs, sizeof(szMessageAndAdditionalArgs), cszLogMessage, args);

        m_file.setf(std::ios::left);

        m_file << "[" << sDateTime.toStdString() << "] ["
               << m_sOwnerName.toStdString()     << "] [" << std::setw(5)
               << sLogLevel.toStdString()        << "] - " << szMessageAndAdditionalArgs << std::endl;

    } while(false);

    return iResult;
}

QString Logger::getDateTime()
{
    return QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz");
}

QString Logger::convertLogLevelToString(const LOG_LEVEL eLevel)
{
    QString sLogLevel = "UNKNOWN";
    switch(eLevel)
    {
    case LOG_LEVEL::FATAL:
        sLogLevel = "FATAL";
        break;
    case LOG_LEVEL::ERROR:
        sLogLevel = "ERROR";
        break;
    case LOG_LEVEL::WARN:
        sLogLevel = "WARN";
        break;
    case LOG_LEVEL::INFO:
        sLogLevel = "INFO";
        break;
    case LOG_LEVEL::DEBUG:
        sLogLevel = "DEBUG";
        break;
    case LOG_LEVEL::TRACE:
        sLogLevel = "TRACE";
        break;
    }

    return sLogLevel;
}

Logger* Logger::getLogger(const QString& csLogFileName, const QString& csLogFilePath, const QString& csOwnerName, const LOG_LEVEL& ceDefaultLogLevel)
{
    return new Logger(csLogFileName, csLogFilePath, csOwnerName, ceDefaultLogLevel);
}

