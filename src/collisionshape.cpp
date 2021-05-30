#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <bullet/BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <bullet/BulletCollision/CollisionShapes/btConeShape.h>
#include <bullet/BulletCollision/CollisionShapes/btCylinderShape.h>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <collisionshape.h>
#include <model.h>

CollisionShape::CollisionShape() {
    collision_shape = new btBoxShape(btVector3(16, 0, 16));
}

BoxShape::BoxShape(float x, float y, float z){
    collision_shape = new btBoxShape(btVector3(x, y, z));
}

SphereShape::SphereShape(float radius){
    collision_shape = new btSphereShape(radius);
}

CapsuleShape::CapsuleShape(float radius, float height){
    collision_shape = new btCapsuleShape(radius, height);
}

CylinderShape::CylinderShape(float x, float y, float z){
    collision_shape = new btCylinderShape(btVector3(x, y, z));
}

ConeShape::ConeShape(float radius, float height){
    collision_shape = new btConeShape(radius, height);
}

MeshShape::MeshShape(Model model){
    collision_shape = create_mesh_shape(model);
}

CollisionShape::~CollisionShape() { delete collision_shape; }

btCollisionShape* CollisionShape::create_mesh_shape(Model& model){
    btTriangleMesh* trimesh = new btTriangleMesh();
    for (Mesh& m : model.get_meshes()){
        std::vector<Vertex> vertices = m.get_vertices();
        std::vector<unsigned int> indices = m.get_indices();
        for(int i = 0; i < indices.size(); i+=3){
            glm::vec3 v1 = vertices[indices[i]].pos;
            glm::vec3 v2 = vertices[indices[i+1]].pos;
            glm::vec3 v3 = vertices[indices[i+2]].pos;
            trimesh->addTriangle(btVector3(v1.x, v1.y, v1.z), btVector3(v2.x, v2.y, v2.z), btVector3(v3.x, v3.y, v3.z));
        }
    }
    return new btBvhTriangleMeshShape(trimesh, true);
}

btCollisionShape* CollisionShape::get_collision_shape() {
    return collision_shape;
}

void CollisionShape::set_collision_shape(btCollisionShape* cs) {
    collision_shape = cs;
}
