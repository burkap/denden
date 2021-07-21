#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <bullet/BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <bullet/BulletCollision/CollisionShapes/btConeShape.h>
#include <bullet/BulletCollision/CollisionShapes/btCylinderShape.h>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <components/collider.h>
#include <components/model.h>

Collider::Collider() {
    collision_shape = new btBoxShape(btVector3(16, 0, 16));
}

BoxCollider::BoxCollider(float x, float y, float z){
    collision_shape = new btBoxShape(btVector3(x, y, z));
}

SphereCollider::SphereCollider(float radius){
    collision_shape = new btSphereShape(radius);
}

CapsuleCollider::CapsuleCollider(float radius, float height){
    collision_shape = new btCapsuleShape(radius, height);
}

CylinderCollider::CylinderCollider(float x, float y, float z){
    collision_shape = new btCylinderShape(btVector3(x, y, z));
}

ConeCollider::ConeCollider(float radius, float height){
    collision_shape = new btConeShape(radius, height);
}

MeshCollider::MeshCollider(Model model){
    collision_shape = create_mesh_shape(model);
}

Collider::~Collider() { delete collision_shape; }

btCollisionShape* Collider::create_mesh_shape(Model& model){
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

btCollisionShape* Collider::get_collision_shape() {
    return collision_shape;
}

void Collider::set_collision_shape(btCollisionShape* cs) {
    collision_shape = cs;
}
