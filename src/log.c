#include "log.h"
#include <stdarg.h>

void init_logfile() {
    logfile = fopen("emulator.log", "a");
}
void log_debug(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(logfile, format, args);
    va_end(args);
    fflush(logfile);
}