#pragma once
#include "logger.h"

#define LOG_TAG "ppl"
#define LOG() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::LOG, LOG_TAG, __FILE__, __LINE__)

#ifdef LOG_INFO
#define INFO() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::INFO, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_INFO

#ifdef LOG_DEBUG
#define DEBUG() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::DEBUG, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_DEBUG

#ifdef LOG_WARNING
#define WARNING() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::WARNING, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_WARNING

#ifdef LOG_ERROR
#define ERROR() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::ERROR, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_ERROR

#ifdef LOG_FATAL
#define FATAL() \
    LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::FATAL, LOG_TAG, __FILE__, __LINE__)

#define CHECK_IF(expression) \
    LOGGER_NAMESPACE::LogHelper((expression) ? LOGGER_NAMESPACE::LogHelper::LOG : LOGGER_NAMESPACE::LogHelper::FATAL, LOG_TAG, __FILE__, __LINE__, true)

#endif // LOG_FATAL
