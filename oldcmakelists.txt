cmake_minimum_required(VERSION 3.20)

project(RevEngineProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -g")

add_subdirectory($ENV{JOLT_REPO}/Build include/)
target_compile_options(Jolt PRIVATE
    -Wno-array-bounds
)
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
set(RevEngineDependencies Jolt glfw raylib OgreBites)

add_executable(RevEngine)

target_include_directories(RevEngine PRIVATE $ENV{JOLT_REPO}/)
target_include_directories(RevEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

target_link_libraries(RevEngine PRIVATE ${RevEngineDependencies})

# -----------------------------------------------------------------------------
# OGRE plugins.cfg / resources.cfg generation
#
# On Linux, Ogre::DynLib::load() only appends ".so.<MAJOR>.<MINOR>" to a plugin
# name if the name doesn't already contain ".so" (see OgreDynLib.cpp). Nix's
# Ogre plugin .so files are versioned on disk (e.g. Codec_Assimp.so.14.5.2), so
# a bare "Plugin=Codec_Assimp" line makes Ogre guess a filename that may not
# exist. Instead we discover the *real* on-disk filenames at configure time and
# write them verbatim - since they already contain ".so", Ogre won't try to
# guess a suffix, and this keeps working across future Ogre version bumps.
# -----------------------------------------------------------------------------

function(reveng_get_target_location out_var target)
    foreach(prop IMPORTED_LOCATION IMPORTED_LOCATION_NOCONFIG IMPORTED_LOCATION_RELEASE
                 IMPORTED_LOCATION_RELWITHDEBINFO IMPORTED_LOCATION_DEBUG LOCATION)
        get_target_property(_loc ${target} ${prop})
        if(_loc)
            set(${out_var} "${_loc}" PARENT_SCOPE)
            return()
        endif()
    endforeach()
    message(FATAL_ERROR "reveng: could not determine the on-disk location of target '${target}'")
endfunction()

if(TARGET OgreMain)
    set(_ogre_main_target OgreMain)
elseif(TARGET Ogre::Main)
    set(_ogre_main_target Ogre::Main)
else()
    message(FATAL_ERROR "reveng: no OgreMain (or Ogre::Main) target after find_package(OGRE)")
endif()

reveng_get_target_location(_ogre_main_location ${_ogre_main_target})
get_filename_component(_ogre_lib_dir "${_ogre_main_location}" DIRECTORY)
get_filename_component(_ogre_prefix "${_ogre_lib_dir}" DIRECTORY)

# Standard Ogre install layout puts plugins in <libdir>/OGRE. Try a couple of
# fallbacks in case the nixpkgs layout differs.
set(_ogre_plugin_dir_candidates
    "${_ogre_lib_dir}/OGRE"
    "${_ogre_prefix}/lib/OGRE"
)

set(OGRE_PLUGIN_DIR "")
foreach(_cand ${_ogre_plugin_dir_candidates})
    if(EXISTS "${_cand}")
        set(OGRE_PLUGIN_DIR "${_cand}")
        break()
    endif()
endforeach()

if(NOT OGRE_PLUGIN_DIR)
    message(FATAL_ERROR
        "reveng: could not locate the OGRE plugin directory near ${_ogre_main_location}. "
        "Set OGRE_PLUGIN_DIR manually, e.g. -DOGRE_PLUGIN_DIR=/nix/store/.../lib/OGRE")
endif()

message(STATUS "reveng: OGRE plugin directory: ${OGRE_PLUGIN_DIR}")

# Logical plugin names we want -> resolved to whatever the real filename is.
# Add/remove from this list as your project needs.
set(_ogre_wanted_plugins
    RenderSystem_GL3Plus
    RenderSystem_Vulkan
    Codec_Assimp
    Codec_STBI
    Plugin_ParticleFX
)

set(_ogre_plugin_lines "")
foreach(_plug ${_ogre_wanted_plugins})
    file(GLOB _plug_matches "${OGRE_PLUGIN_DIR}/${_plug}.so*")
    if(_plug_matches)
        list(GET _plug_matches 0 _plug_file)
        get_filename_component(_plug_name "${_plug_file}" NAME)
        string(APPEND _ogre_plugin_lines "Plugin=${_plug_name}\n")
        message(STATUS "reveng: found OGRE plugin ${_plug} -> ${_plug_name}")
    else()
        message(STATUS "reveng: OGRE plugin '${_plug}' not found in ${OGRE_PLUGIN_DIR}, skipping")
    endif()
endforeach()

set(_plugins_cfg_content "PluginFolder=${OGRE_PLUGIN_DIR}\n\n${_ogre_plugin_lines}")
set(_plugins_cfg_path "${CMAKE_BINARY_DIR}/plugins.cfg")
file(WRITE "${_plugins_cfg_path}" "${_plugins_cfg_content}")

# resources.cfg: project-specific asset search paths. Adjust/extend as needed.
set(_resources_cfg_content
"[General]
FileSystem=${CMAKE_CURRENT_SOURCE_DIR}/media
")
set(_resources_cfg_path "${CMAKE_BINARY_DIR}/resources.cfg")
file(WRITE "${_resources_cfg_path}" "${_resources_cfg_content}")

# Copy both next to the built executable so relative-path lookups
# ("plugins.cfg" / "resources.cfg" in the current working directory,
# as OgreBites::ApplicationContext expects by default) just work.
add_custom_command(TARGET RevEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${_plugins_cfg_path}" "$<TARGET_FILE_DIR:RevEngine>/plugins.cfg"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${_resources_cfg_path}" "$<TARGET_FILE_DIR:RevEngine>/resources.cfg"
    COMMENT "reveng: staging plugins.cfg / resources.cfg next to RevEngine"
)

install(TARGETS RevEngine DESTINATION bin)
install(FILES "${_plugins_cfg_path}" "${_resources_cfg_path}" DESTINATION bin)
