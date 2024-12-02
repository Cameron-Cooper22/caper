#include "Log.hpp"
#include "../includes.hpp"

void Logging::log(LogLevel level, const char *fmt, ...) {
  std::string level_str = "";

  switch (level) {
    // maybe add timestamp but for now this is fine
    case LOG: level_str = "[LOG] "; break;
    case WARN: level_str = "[WARN] "; break;
    case ERR: level_str = "[ERR] "; break;
    case CRIT: level_str = "[ERR] "; break;
    case INFO: level_str = "[INFO] "; break;
    default: break;
  }

  char buf[LOGMESSAGESIZE] = "";
  char* output_str;
  int msg_len;

  va_list args;
  va_start(args, fmt);
  msg_len = vsnprintf(buf, sizeof buf, fmt, args);
  va_end(args);

  if ((long unsigned int)msg_len < sizeof buf) {
    // put on heap
    output_str = strdup(buf);
  } else {
    output_str = (char*) malloc(msg_len + 1);
    if (!output_str) {
      std::cout << "CRITICAL: Cannot alloc size " << msg_len + 1 << " for log! (Out of memory?)\n";
      return;
    }

    va_start(args, fmt);
    vsnprintf(output_str, msg_len + 1U, fmt, args);
    va_end(args);
  }

  std::cout << level_str << output_str << "\n";

  free(output_str);
}
