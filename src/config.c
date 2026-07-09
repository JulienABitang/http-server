#include "config.h"
#include "args.h"
#include <stdio.h>
#include <unistd.h>

Config config = {.root_path = "www/", .cpu_count = 4};

static ArgOption option[] = {
    ARG_STRING("root", 'R', "path to root directory", &config.root_path),
    ARG_BOOL("log", 'l', "Enable Logging", NULL),
};

static int option_count = sizeof(option) / sizeof(ArgOption);

void print_help() {
  puts("Usage: http-server [OPTION]...\nA simple HTTP server! Do not expect "
       "much.\n\nOptions:");
  for (int i = 0; i < option_count; i++) {
    printf("-%c, --%-20s %s\n", option[i].short_name, option[i].long_name,
           option[i].help_msg);
  }
  puts("\nCoutesy of Julien A Bitang <JFA3082 at RIT dot EDU> :)");
}
int parse_args(int argc, char **argv) {}
