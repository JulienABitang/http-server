#ifndef HTTP_CONFIG_H
#define HTTP_CONFIG_H

typedef struct {
  char root_path[255];
  int cpu_count;
} Config;

extern Config config;

int parse_args(int argc, char **argv);
#endif
