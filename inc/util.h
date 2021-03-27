#ifndef UTIL_H
#define UTIL_H

#include <libgen.h>        // dirname
#include <linux/limits.h>  // PATH_MAX
#include <stdlib.h>
#include <unistd.h>  // readlink

#include <string>

std::string get_exe_path();

#endif
