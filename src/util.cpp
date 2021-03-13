
#include <util.h>

const char* get_exe_path() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    const char* path;
    if (count != -1) {
        path = dirname(result);
    }
    return path;
}