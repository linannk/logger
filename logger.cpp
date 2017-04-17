#include "logger.h"
BEGIN_LOGGER_NAMESPACE
LogHelper::LogUtil& LogHelper::LogUtil::Inst() {
    static LogUtil s_inst;
    return s_inst;
}
END_LOGGER_NAMESPACE
