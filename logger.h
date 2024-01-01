#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <time.h>

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDCYAN "\033[1m\033[36m"

#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_DEBUG 2
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_ERROR 4

#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_INFO
#endif

#define LOG_TIME(file)                                                         \
  do {                                                                         \
    time_t t = time(NULL);                                                     \
    struct tm *tm = localtime(&t);                                             \
    fprintf(file, "[%02d:%02d:%02d] ", tm->tm_hour, tm->tm_min, tm->tm_sec);   \
  } while (0)

#define LOG_INFO(...)                                                          \
  do {                                                                         \
    if (CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO) {                                 \
      fprintf(stdout, BOLDGREEN);                                              \
      LOG_TIME(stdout);                                                        \
      fprintf(stdout, "[INFO] " RESET __VA_ARGS__);                            \
    }                                                                          \
  } while (0)

#define LOG_DBG(...)                                                           \
  do {                                                                         \
    if (CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG) {                                \
      fprintf(stdout, BOLDCYAN);                                               \
      LOG_TIME(stdout);                                                        \
      fprintf(stdout, "[DEBUG] " RESET __VA_ARGS__);                           \
    }                                                                          \
  } while (0)

#define LOG_WARN(...)                                                          \
  do {                                                                         \
    if (CURRENT_LOG_LEVEL <= LOG_LEVEL_WARN) {                                 \
      fprintf(stdout, BOLDYELLOW);                                             \
      LOG_TIME(stdout);                                                        \
      fprintf(stdout, "[WARNING] " RESET __VA_ARGS__);                         \
    }                                                                          \
  } while (0)

#define LOG_ERR(...)                                                           \
  do {                                                                         \
    if (CURRENT_LOG_LEVEL <= LOG_LEVEL_ERROR) {                                \
      fprintf(stderr, BOLDRED);                                                \
      LOG_TIME(stderr);                                                        \
      fprintf(stderr, "[ERROR] " RESET __VA_ARGS__);                           \
    }                                                                          \
  } while (0)

#endif // LOGGER_H_