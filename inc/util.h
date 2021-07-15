#ifndef UTIL_H
#define UTIL_H

#include <libgen.h>        // dirname
#include <linux/limits.h>  // PATH_MAX
#include <stdlib.h>
#include <unistd.h>  // readlink
#include <bullet/LinearMath/btVector3.h>
#include <bullet/LinearMath/btQuaternion.h>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>

std::string get_exe_path();
bool is_number(std::string str);
btVector3 glm_to_bt_vec3(glm::vec3 v);
btQuaternion glm_to_bt_quat(glm::quat q);
glm::vec3 euler_to_direction_vec(double yaw, double pitch);

#endif
