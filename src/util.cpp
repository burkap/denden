
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

btVector3 glm_to_bt_vec3(glm::vec3 v){
    return btVector3(v.x, v.y, v.z);
}

btQuaternion glm_to_bt_quat(glm::quat q)
{
    return btQuaternion(q.x, q.y, q.z, q.w); // glmquat WXYZ -> btquat XYZW
}

glm::vec3 euler_to_direction_vec(double yaw, double pitch){
    glm::vec3 vec;
    vec.x = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    vec.y = sin(glm::radians(pitch));
    vec.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(vec);
}
