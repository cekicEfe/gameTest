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
    main_scene_manager = root->createSceneManager();
    main_scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(main_scene_manager);

    // and tell it to render into the main window
    ctx.getRenderWindow()->addViewport(nullptr, 0);
    
    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    this->main_viewport = ctx.getRenderWindow()->getViewport(0);
    this->main_viewport->setBackgroundColour(fadeColour);
    main_scene_manager->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 600, 900);
    
    ctx.addInputListener(&key_handler);
}


RlClone::RenderBackend::~RenderBackend() {
    this->ctx.closeApp();
}
