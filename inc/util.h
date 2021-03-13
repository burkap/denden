#ifndef UTIL_H
#define UTIL_H

#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX
#include <stdlib.h>
#include <string.h>

const char* get_exe_path();

#endif