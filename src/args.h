#ifndef HTTP_ARG_H
#define HTTP_ARG_H

#define ARG_INT(long, short, help, target)                                     \
  {                                                                            \
      .long_name = (long),                                                     \
      .short_name = (short),                                                   \
      .type = ARG_TYPE_INT,                                                    \
      .target_var = (target),                                                  \
      .help_msg = (help),                                                      \
  }

#define ARG_BOOL(long, short, help, target)                                    \
  {                                                                            \
      .long_name = (long),                                                     \
      .short_name = (short),                                                   \
      .type = ARG_TYPE_BOOL,                                                   \
      .target_var = (target),                                                  \
      .help_msg = (help),                                                      \
  }

#define ARG_STRING(long, short, help, target)                                  \
  {                                                                            \
      .long_name = (long),                                                     \
      .short_name = (short),                                                   \
      .type = ARG_TYPE_STRING,                                                 \
      .target_var = (target),                                                  \
      .help_msg = (help),                                                      \
  }

typedef enum {
  ARG_TYPE_INT,
  ARG_TYPE_BOOL,
  ARG_TYPE_STRING,
} ArgType;

typedef struct {
  const char *long_name;
  const char short_name;
  const char *help_msg;
  void *target_var;
  ArgType type;
} ArgOption;

#endif
