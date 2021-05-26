
#include <util.h>

std::string get_exe_path() {
    static bool cached = false;
    static std::string path;
    if (!cached) {
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if (count != -1) {
            path = std::string(dirname(result));
        }
        cached = true;
    }
    return path;
}

bool is_number(std::string str){
    for (char const &ch : str) {
        if (std::isdigit(ch) == 0) return false;
    }
    return true;
}
