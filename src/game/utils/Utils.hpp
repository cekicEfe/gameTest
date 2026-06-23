#ifndef UTILS_HPP
#define UTILS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>

#include <raylib.h>
#include <raymath.h>

namespace RlClone {

/*!
 * *** USED AI FOR THIS ***
 * \brief Walks every sub-mesh of a raylib Model, applies the model's transform to
 * each vertex, and packs everything into a single Jolt MeshShape.
 */
extern JPH::RefConst<JPH::Shape> CreateConcaveShapeFromModel(const Model& model);

} // namespace RlClone::Demo

#endif
