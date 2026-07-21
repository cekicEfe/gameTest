#ifndef RENDERBACKEND_HPP
#define RENDERBACKEND_HPP

#include <OGRE/Bites/OgreApplicationContext.h>
#include <OGRE/Bites/OgreCameraMan.h>
#include <OGRE/Bites/OgreInput.h>
#include <OGRE/Ogre.h>
#include <OgreRTShaderSystem.h>

#include <exception>
#include <iostream>


namespace RlClone {


class KeyHandler : public OgreBites::InputListener {
    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
};


class RenderBackend {
public:
    RenderBackend();
    ~RenderBackend();

    OgreBites::ApplicationContext ctx;
    RlClone::KeyHandler key_handler;
};


} // namespace RlClone


#endif /* RENDERBACKEND_HPP */
