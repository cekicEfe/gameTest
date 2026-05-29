#include <Game/Layers.hpp>


using namespace JPH;


bool RlClone::PhysicsBackend::ObjectLayerPairFilterImpl::ShouldCollide(
    ObjectLayer inObject1, ObjectLayer inObject2) const {
    switch (inObject1) {
        case Layers::NON_MOVING:
            return inObject2 == Layers::MOVING; // Non moving only collides with moving
        case Layers::MOVING: return true; // Moving collides with everything
        default: JPH_ASSERT(false); return false;
    }
}


RlClone::PhysicsBackend::BPLayerInterfaceImpl::BPLayerInterfaceImpl() {
    // Create a mapping table from object to broad phase layer
    mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
    mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
}


uint RlClone::PhysicsBackend::BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const {
    return BroadPhaseLayers::NUM_LAYERS;
}


BroadPhaseLayer
RlClone::PhysicsBackend::BPLayerInterfaceImpl::GetBroadPhaseLayer(ObjectLayer inLayer) const {
    JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
    return mObjectToBroadPhase[inLayer];
}


#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
const char* RlClone::PhysicsBackend::BPLayerInterfaceImpl::GetBroadPhaseLayerName(
    BroadPhaseLayer inLayer) const {
    switch ((BroadPhaseLayer::Type)inLayer) {
        case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING: return "NON_MOVING";
        case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING: return "MOVING";
        default: JPH_ASSERT(false); return "INVALID";
    }
}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED


bool RlClone::PhysicsBackend::ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(
    ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const {
    switch (inLayer1) {
        case Layers::NON_MOVING: return inLayer2 == BroadPhaseLayers::MOVING;
        case Layers::MOVING: return true;
        default: JPH_ASSERT(false); return false;
    }
}


ValidateResult RlClone::PhysicsBackend::MyContactListener::OnContactValidate(
    const Body& inBody1,
    const Body& inBody2,
    RVec3Arg inBaseOffset,
    const CollideShapeResult& inCollisionResult) {
    std::cout << "Contact validate callback" << std::endl;

    // Allows you to ignore a contact before it is created (using layers to not
    // make objects collide is cheaper!)
    return ValidateResult::AcceptAllContactsForThisBodyPair;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactAdded(
    const Body& inBody1,
    const Body& inBody2,
    const ContactManifold& inManifold,
    ContactSettings& ioSettings) {
    std::cout << "A contact was added" << std::endl;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactPersisted(
    const Body& inBody1,
    const Body& inBody2,
    const ContactManifold& inManifold,
    ContactSettings& ioSettings) {
    std::cout << "A contact was persisted" << std::endl;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactRemoved(
    const SubShapeIDPair& inSubShapePair) {
    std::cout << "A contact was removed" << std::endl;
}


void RlClone::PhysicsBackend::MyBodyActivationListener::OnBodyActivated(
    const BodyID& inBodyID, uint64 inBodyUserData) {
    std::cout << "A body got activated" << std::endl;
}


void RlClone::PhysicsBackend::MyBodyActivationListener::OnBodyDeactivated(
    const BodyID& inBodyID, uint64 inBodyUserData) {
    std::cout << "A body went to sleep" << std::endl;
}
