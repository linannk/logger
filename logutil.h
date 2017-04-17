#pragma once
#include "logger.h"

#define LOG_TAG "ppl"
#define LOG() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::LOG, LOG_TAG, __FILE__, __LINE__)

#ifdef LOGGER_INFO
#define INFO() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::INFO, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_INFO

#ifdef LOGGER_DEBUG
#define DEBUG() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::DEBUG, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_DEBUG

#ifdef LOGGER_WARNING
#define WARNING() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::WARNING, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_WARNING

#ifdef LOGGER_ERROR
#define ERROR() LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::ERROR, LOG_TAG, __FILE__, __LINE__)
#endif // LOG_ERROR

#ifdef LOGGER_FATAL
#define FATAL() \
    LOGGER_NAMESPACE::LogHelper(LOGGER_NAMESPACE::LogHelper::FATAL, LOG_TAG, __FILE__, __LINE__)

#define CHECK_IF(expression) \
    LOGGER_NAMESPACE::LogHelper((expression) ? LOGGER_NAMESPACE::LogHelper::LOG : LOGGER_NAMESPACE::LogHelper::FATAL, LOG_TAG, __FILE__, __LINE__, true)

#endif // LOG_FATAL
