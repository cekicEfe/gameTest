#include "Listener.hpp"


JPH::ValidateResult RlClone::PhysicsBackend::MyContactListener::OnContactValidate(
    const JPH::Body& inBody1,
    const JPH::Body& inBody2,
    JPH::RVec3Arg inBaseOffset,
    const JPH::CollideShapeResult& inCollisionResult) {
    std::cout << "Contact validate callback" << std::endl;

    return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactAdded(
    const JPH::Body& inBody1,
    const JPH::Body& inBody2,
    const JPH::ContactManifold& inManifold,
    JPH::ContactSettings& ioSettings) {
    std::cout << "A contact was added" << std::endl;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactPersisted(
    const JPH::Body& inBody1,
    const JPH::Body& inBody2,
    const JPH::ContactManifold& inManifold,
    JPH::ContactSettings& ioSettings) {
    std::cout << "A contact was persisted" << std::endl;
}


void RlClone::PhysicsBackend::MyContactListener::OnContactRemoved(
    const JPH::SubShapeIDPair& inSubShapePair) {
    std::cout << "A contact was removed" << std::endl;
}


void RlClone::PhysicsBackend::MyBodyActivationListener::OnBodyActivated(
    const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) {
    std::cout << "A body got activated" << std::endl;
}


void RlClone::PhysicsBackend::MyBodyActivationListener::OnBodyDeactivated(
    const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) {
    std::cout << "A body went to sleep" << std::endl;
}
