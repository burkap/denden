#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <camera.h>
#include <collisionshape.h>
#include <component.h>
#include <cubemap.h>
#include <debugdrawer.h>
#include <gameobject.h>
#include <globals.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <lightobject.h>
#include <model.h>
#include <renderer.h>
#include <rigidbody.h>
#include <scene.h>
#include <shader.h>
#include <stddef.h> /* offsetof */
#include <texture.h>
#include <transform.h>
#include <util.h>

#include <cmath>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <configparser.h>
#include <shadermanager.h>
#include <app.h>

int main() {
    App app;
    return 1;
}
