#include "Utils.hpp"


JPH::RefConst<JPH::Shape> RlClone::CreateConcaveShapeFromModel(const Model& model) {
    JPH::VertexList vertices;
    JPH::IndexedTriangleList triangles;

    for (int m = 0; m < model.meshCount; m++) {
        const Mesh& mesh = model.meshes[m];
        const uint32_t baseVertex = (uint32_t)vertices.size();

        vertices.reserve(vertices.size() + mesh.vertexCount);
        for (int v = 0; v < mesh.vertexCount; v++) {
            Vector3 pos = {
                mesh.vertices[v * 3 + 0],
                mesh.vertices[v * 3 + 1],
                mesh.vertices[v * 3 + 2]};
            pos = Vector3Transform(pos, model.transform);
            vertices.push_back(JPH::Float3(pos.x, pos.y, pos.z));
        }

        triangles.reserve(triangles.size() + mesh.triangleCount);
        if (mesh.indices != nullptr) {
            for (int t = 0; t < mesh.triangleCount; t++) {
                triangles.push_back(
                    JPH::IndexedTriangle(
                        baseVertex + mesh.indices[t * 3 + 0],
                        baseVertex + mesh.indices[t * 3 + 1],
                        baseVertex + mesh.indices[t * 3 + 2]));
            }
        }
        else {
            for (int t = 0; t < mesh.triangleCount; t++) {
                triangles.push_back(
                    JPH::IndexedTriangle(
                        baseVertex + t * 3 + 0,
                        baseVertex + t * 3 + 1,
                        baseVertex + t * 3 + 2));
            }
        }
    }

    JPH::MeshShapeSettings shapeSettings(vertices, triangles);

    JPH::Shape::ShapeResult result = shapeSettings.Create();
    if (result.HasError()) {
        TraceLog(LOG_ERROR, "Jolt: failed to build mesh shape: %s", result.GetError().c_str());
        return nullptr;
    }

    return result.Get();
}
