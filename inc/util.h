#ifndef UTIL_H
#define UTIL_H

#include <libgen.h>        // dirname
#include <linux/limits.h>  // PATH_MAX
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // readlink

const char* get_exe_path();

#endif