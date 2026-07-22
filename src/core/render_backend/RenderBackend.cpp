#include "render_backend/RenderBackend.hpp"


bool RlClone::InputHandler::keyPressed(const OgreBites::KeyboardEvent& evt) {
    active_keys.insert(evt.keysym.sym);
    return true;
}


bool RlClone::InputHandler::keyReleased(const OgreBites::KeyboardEvent& evt) {
    active_keys.erase(evt.keysym.sym);
    return true;
}


bool RlClone::InputHandler::mouseMoved(const OgreBites::MouseMotionEvent& evt) {
    // Save current mouse X and Y coordinates
    last_x = evt.x;
    last_y = evt.y;
    return true;
}


bool RlClone::InputHandler::mousePressed(const OgreBites::MouseButtonEvent& evt) {
    if (evt.button == OgreBites::BUTTON_LEFT) {
        left_button_pressed = true;
    }
    if (evt.button == OgreBites::BUTTON_RIGHT) {
        right_button_pressed = true;
    }
    return true;
}


bool RlClone::InputHandler::mouseReleased(const OgreBites::MouseButtonEvent& evt) {
    if (evt.button == OgreBites::BUTTON_LEFT) {
        left_button_pressed = false;
    }
    if (evt.button == OgreBites::BUTTON_RIGHT) {
        right_button_pressed = false;
    }
    return true;
}


bool RlClone::InputHandler::mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) {
    // Read scroll data from the event structure
    scroll_y = evt.y; // Positive = Scroll Up, Negative = Scroll Down
    // Return true if you have consumed the event, false to pass it down the chain
    return true;
}


bool RlClone::InputHandler::IsKeyPressed(OgreBites::Keycode key) const {
    return active_keys.find(key) != active_keys.end();
}


int RlClone::InputHandler::GetMouseLastX() const {
    return last_x;
}


int RlClone::InputHandler::GetMouseLastY() const {
    return last_y;
}


int RlClone::InputHandler::GetMouseLastScroll() const {
    return scroll_y;
}


bool RlClone::InputHandler::IsMouseLeftButtonPressed() const {
    return left_button_pressed;
}


bool RlClone::InputHandler::IsMouseRightButtonPressed() const {
    return right_button_pressed;
}


RlClone::RenderBackend::RenderBackend() : ctx("RenderBackend") {
    this->ctx.initApp();

    Ogre::Root* root = ctx.getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();
    scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("MainCamera");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    ctx.getRenderWindow()->addViewport(cam);
    ctx.addInputListener(&key_handler);
}


RlClone::RenderBackend::~RenderBackend() {
    this->ctx.closeApp();
}
