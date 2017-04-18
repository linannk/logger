#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define LOGGER_LOG
#define LOGGER_INFO
#define LOGGER_DEBUG
#define LOGGER_WARNING
#define LOGGER_ERROR
#define LOGGER_FATAL

#define LOGGER_NAMESPACE logger
#define BEGIN_LOGGER_NAMESPACE namespace LOGGER_NAMESPACE {
#define END_LOGGER_NAMESPACE }

BEGIN_LOGGER_NAMESPACE
#ifdef WIN32
//#undef FOREGROUND_BLUE
//#undef FOREGROUND_GREEN
//#undef FOREGROUND_RED
//#undef FOREGROUND_INTENSITY
//#undef BACKGROUND_BLUE
//#undef BACKGROUND_GREEN
//#undef BACKGROUND_RED
//#undef BACKGROUND_INTENSITY

#define LOGGER_FOREGROUND_BLUE 0x01
#define LOGGER_FOREGROUND_GREEN 0x02
#define LOGGER_FOREGROUND_RED 0x04
#define LOGGER_FOREGROUND_INTENSITY 0x08

#define LOGGER_BACKGROUND_BLUE 0x10
#define LOGGER_BACKGROUND_GREEN 0x20
#define LOGGER_BACKGROUND_RED 0x40
#define LOGGER_BACKGROUND_INTENSITY 0x80
#else
#define LOGGER_FOREGROUND_GREEN 0x02
#define LOGGER_FOREGROUND_RED 0x01
#define LOGGER_FOREGROUND_BLUE 0x04
#define LOGGER_FOREGROUND_INTENSITY 0x00
#endif

void SetConsoleForegroundColor(FILE* stream, unsigned short clr);
void ResetConsoleForegroundColor(FILE* stream);
class LogHelper {
public:
    enum Level {
        LOG,
#ifdef LOGGER_INFO
        INFO,
#endif // LOG_INFO
#ifdef LOGGER_DEBUG
        DEBUG,
#endif // LOG_DEBUG
#ifdef LOGGER_WARNING
        WARNING,
#endif // LOG_WARNING
#ifdef LOGGER_ERROR
        ERROR,
#endif // LOG_ERROR
#ifdef LOGGER_FATAL
        FATAL
#endif // LOG_FATAL
    };
    class LogUtil {
    public:
        static LogUtil& Inst();
        void   WriteTitle(Level level, const char* tag, const char* file, int line)
        {
            //! Write tag
            //! Write filename ?
            //! Write code line ?
            //! Write time stamp ?
#if defined(WIN32)
            const char* ch_idx = strrchr(file, '\\') + 1;
#else
            const char* ch_idx = strrchr(file, '/') + 1;
#endif
            time_t t = time(NULL);
            struct tm* tm_buf = gmtime(&t);
            const char* asc_tm_str = asctime(tm_buf);
            char tm_str_buf[512] = { 0 };
            for (size_t i = 0; asc_tm_str[i] != '\n'; ++i)
            {
                tm_str_buf[i] = asc_tm_str[i];
            }
            const char* level_strings[] = {
                "*",
#ifdef LOGGER_INFO
                "!",
#endif // LOG_INFO
#ifdef LOGGER_DEBUG
                "#",
#endif // LOG_DEBUG
#ifdef LOGGER_WARNING
                "!",
#endif // LOG_WARNING
#ifdef LOGGER_ERROR
                "@",
#endif // LOG_ERROR
#ifdef LOGGER_FATAL
                "$"
#endif // LOG_FATAL
            };

            const unsigned short colors[] = {
                0x07 | LOGGER_FOREGROUND_INTENSITY,                      //! LOG
                LOGGER_FOREGROUND_GREEN | LOGGER_FOREGROUND_INTENSITY,   //! INFO
                LOGGER_FOREGROUND_BLUE | LOGGER_FOREGROUND_GREEN | LOGGER_FOREGROUND_INTENSITY,       //! DEBUG
                LOGGER_FOREGROUND_RED | LOGGER_FOREGROUND_GREEN | LOGGER_FOREGROUND_INTENSITY, //! WARNINGS
                LOGGER_FOREGROUND_RED | LOGGER_FOREGROUND_INTENSITY,                            //! ERROR
                LOGGER_FOREGROUND_BLUE | LOGGER_FOREGROUND_RED | LOGGER_FOREGROUND_INTENSITY   //! FATAL
            };

            SetConsoleForegroundColor((&log_stream_)[level], colors[level]);
            if (strlen(tag) != 0) {
                this->PrintMessage(level, "[%s %s %s %s %d]", level_strings[level], tag, tm_str_buf, ch_idx, line);
            }
            else {
                this->PrintMessage(level, "[%s %s %s %d]", level_strings[level], tm_str_buf, ch_idx, line);
            }
            ResetConsoleForegroundColor((&log_stream_)[level]);
        }

        FILE* GetLogStream(Level level) const {
            return (&log_stream_)[level];
        }
        
        void SetLogStream(Level level, FILE* stream) {
            FILE** start_stream = &log_stream_;
            FILE* old_stream = start_stream[level];
            for (int i = 0; i < sizeof(LogUtil) / sizeof(void*); ++i) {
                if (old_stream == start_stream[level] && start_stream[level] != stdout
                    && start_stream[level] != stderr)
                {
                    start_stream[level] = NULL;
                }
            }
            if (old_stream != NULL && old_stream != stdout && old_stream != stderr) {
                fclose(old_stream);
            }
            start_stream[level] = stream;
        }
    private:
        LogUtil()
            : log_stream_(stdout)
#ifdef LOGGER_INFO
            , info_stream_(stdout)
#endif // LOG_INFO
#ifdef LOGGER_DEBUG
            , debug_stream_(stdout)
#endif // LOG_DEBUG
#ifdef LOGGER_WARNING
            , warning_stream_(stderr)
#endif // LOG_WARNING
#ifdef LOGGER_ERROR
            , error_stream_(stderr)
#endif // LOG_ERROR
#ifdef LOGGER_FATAL
            , fatal_stream_(stderr)
#endif // LOG_FATAL
        {
            const char* env_lst[] = {
                getenv("LOG_LOG_FILE"),
#ifdef LOGGER_INFO
                getenv("INFO_LOG_FILE"),
#endif // LOG_INFO
#ifdef LOGGER_DEBUG
                getenv("DEBUG_LOG_FILE"),
#endif // LOG_DEBUG
#ifdef LOGGER_WARNING
                getenv("WARNING_LOG_FILE"),
#endif // LOG_WARNING
#ifdef LOGGER_ERROR
                getenv("ERROR_LOG_FILE"),
#endif // LOG_ERROR
#ifdef LOGGER_FATAL
                getenv("FATAL_LOG_FILE")
#endif // LOG_FATAL
            };

            //! Trick
            FILE** start_stream = &log_stream_;
            for (int i = 0; i < sizeof(LogUtil) / sizeof(void*); ++i) {
                for (int j = 0; j < i - 1; ++j) {
                    if (env_lst[i] && 0 == strcmp(env_lst[i], env_lst[j])) {
                        start_stream[i] = start_stream[j];
                        goto UNIQUE_FILE_NAME;
                    }
                }
                if (env_lst[i]) {
                    if (strcmp(env_lst[i], "null") == 0) {
                        start_stream[i] = fopen(env_lst[i], "wb");
                    }
                    else {
                        start_stream[i] = NULL;
                    }
                }
            UNIQUE_FILE_NAME:;
            }
        }

    public:
        ~LogUtil() {
            //! Trick
            FILE** stream_start = &log_stream_;
            for (int i = 0; i < sizeof(LogUtil) / sizeof(void*); ++i) {
                for (int j = i + 1; j < sizeof(LogUtil) / sizeof(void*); ++j) {
                    if (stream_start[i] == stream_start[j]) {
                        goto NOT_UNIQUE_STREAM;
                    }
                }
                if (stream_start[i] != stdout
                    && stream_start[i] != stderr
                    && stream_start[i] != NULL)
                {
                    fclose(stream_start[i]);
                }
            NOT_UNIQUE_STREAM:;
            }
        }

    public:
        int PrintMessage(Level level, const char* fmt, ...) {
            FILE* stream = (&log_stream_)[level];
            if (!stream) {
                return 0;
            }
            va_list ap;
            va_start(ap, fmt);
            int iRet = vfprintf(stream, fmt, ap);
            va_end(ap);
            return iRet;
        }

    private:
        FILE* log_stream_;
#ifdef LOGGER_INFO
        FILE* info_stream_;
#endif // LOG_INFO
#ifdef LOGGER_DEBUG
        FILE* debug_stream_;
#endif // LOG_DEBUG
#ifdef LOGGER_WARNING
        FILE* warning_stream_;
#endif // LOG_WARNING
#ifdef LOGGER_ERROR
        FILE* error_stream_;
#endif // LOG_ERROR
#ifdef LOGGER_FATAL
        FILE* fatal_stream_;
#endif // LOG_FATAL
    };

public:
    LogHelper(Level level, const char* tag, const char* file, int line, bool ignore_non_fatal_message = false, bool abort_fatal = false)
        : level_(level)
        , util_(LogUtil::Inst())
        , ignore_(ignore_non_fatal_message)
        , abort_(abort_fatal)
    {
        if (level == FATAL) {
            ignore_ = false;
        }
        if (!ignore_) {
            util_.WriteTitle(level, tag, file, line);
        }
    }

    ~LogHelper() {
        if (!ignore_) {
            //! Write end tag
            //! Generally, it is newline
            util_.PrintMessage(level_, "\n");
        }
        if (abort_ && level_ == FATAL) {
            util_.~LogUtil();
            abort();
        }

    }

    LogHelper& operator << (char ch) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %c", ch);
        }
        return *this;
    }

    LogHelper& operator << (int i) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %d", i);
        }
        return *this;
    }

    LogHelper& operator << (long l) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %ld", l);
        }
        return *this;
    }

    LogHelper& operator << (long long ll) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %ll", ll);
        }
        return *this;
    }

    LogHelper& operator << (float f) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %f", f);
        }
        return *this;
    }

    LogHelper& operator << (double d) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %lf", d);
        }
        return *this;
    }

    LogHelper& operator << (long double ld) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %llf", ld);
        }
        return *this;
    }

    LogHelper& operator << (const char* message) {
        if (!ignore_) {
            util_.PrintMessage(level_, " %s", message);
        }
        return *this;
    }
private:
    Level level_;
    LogUtil& util_;
    bool ignore_;
    bool abort_;
};

END_LOGGER_NAMESPACE

