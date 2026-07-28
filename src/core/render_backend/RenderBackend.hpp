#ifndef RENDERBACKEND_HPP
#define RENDERBACKEND_HPP

#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Bites/OgreCameraMan.h>
#include <OGRE/Bites/OgreInput.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/Ogre.h>
#include <OgreRTShaderSystem.h>

#include <exception>
#include <iostream>


namespace RlClone {


class InputHandler : public OgreBites::InputListener {
private:
    std::set<OgreBites::Keycode> active_keys;
    int last_x = 0;
    int last_y = 0;
    int scroll_y = 0;

    bool left_button_pressed = false;
    bool right_button_pressed = false;

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
    bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;
    bool mousePressed(const OgreBites::MouseButtonEvent& evt) override;
    bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) override;
public:
    bool IsKeyPressed(OgreBites::Keycode key) const;
  
    int GetMouseLastX() const;
    int GetMouseLastY() const;
    int GetMouseLastScroll() const;

    bool IsMouseLeftButtonPressed() const;
    bool IsMouseRightButtonPressed() const;  
};


class RenderBackend {
public:
    RenderBackend();
    ~RenderBackend();

    OgreBites::ApplicationContext ctx;
    RlClone::InputHandler key_handler;
    Ogre::SceneManager* main_scene_manager;
    Ogre::Viewport* main_viewport;
};


} // namespace RlClone


#endif /* RENDERBACKEND_HPP */
