#pragma once
#include <string>

#define LOGMESSAGESIZE 1024

enum LogLevel {
  NONE = -1,
  LOG 	= 0,
  WARN = 1,
  ERR = 2,
  CRIT = 3,
  INFO = 4
};

namespace Logging {
  // may switch this so that the log could have a target, i.e. stderr or file
  void log(LogLevel level, const char *fmt, ...);
}
