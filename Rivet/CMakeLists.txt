#
# Rivet
#

# Download stb_truetype.h if not present
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/stb/stb_truetype.h")
    message(STATUS "Downloading stb_truetype.h...")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/nothings/stb/master/stb_truetype.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/stb/stb_truetype.h"
        STATUS DOWNLOAD_STATUS
    )
    list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
    if(NOT STATUS_CODE EQUAL 0)
        message(FATAL_ERROR "[Rivet] Failed to download stb_truetype.h — check internet connection")
    endif()
endif()

set(SOURCES
Vendor/stb/stb_image.h
Vendor/stb/stb_image.cpp
Vendor/stb/stb_truetype.h
Vendor/stb/stb_truetype.cpp
Vendor/miniaudio/miniaudio.h
Vendor/miniaudio/miniaudio.cpp
Source/Rvtph.h
# Core
Source/Rivet/Core/App.h
Source/Rivet/Core/App.cpp
Source/Rivet/Core/Window.h
Source/Rivet/Core/Window.cpp
Source/Rivet/Core/Editor.h
Source/Rivet/Core/Editor.cpp
Source/Rivet/Core/Input.h
Source/Rivet/Core/Input.cpp
Source/Rivet/Core/Logger.h
Source/Rivet/Core/Logger.cpp
Source/Rivet/Core/Events/Event.h
Source/Rivet/Core/Events/EventQueue.h
Source/Rivet/Core/Events/EventQueue.cpp
Source/Rivet/Core/Assets/AssetCache.h
Source/Rivet/Core/Assets/TextureManager.h
Source/Rivet/Core/Assets/TextureManager.cpp
Source/Rivet/Core/Assets/ShaderManager.h
Source/Rivet/Core/Assets/ShaderManager.cpp
Source/Rivet/Core/Assets/AudioManager.h
Source/Rivet/Core/Assets/AudioManager.cpp
Source/Rivet/Core/Audio/AudioEngine.h
Source/Rivet/Core/Audio/AudioEngine.cpp
Source/Rivet/Core/Audio/Sound.h
Source/Rivet/Core/Audio/Audio.h
Source/Rivet/Core/Audio/Audio.cpp
Source/Rivet/Core/UI.h
Source/Rivet/Core/UI/Font.h
Source/Rivet/Core/UI/Font.cpp
Source/Rivet/Core/UI/UI.h
Source/Rivet/Core/UI/UI.cpp
# Renderer — Common
Source/Rivet/Renderer/Common/Shader.h
Source/Rivet/Renderer/Common/Shader.cpp
Source/Rivet/Renderer/Common/Buffer.h
Source/Rivet/Renderer/Common/Buffer.cpp
Source/Rivet/Renderer/Common/BufferLayout.h
Source/Rivet/Renderer/Common/BufferLayout.cpp
Source/Rivet/Renderer/Common/Texture.h
Source/Rivet/Renderer/Common/Texture.cpp
# Renderer — 2D
Source/Rivet/Renderer/2D/Camera.h
Source/Rivet/Renderer/2D/Camera.cpp
Source/Rivet/Renderer/2D/Renderer.h
Source/Rivet/Renderer/2D/Renderer.cpp
# Renderer — 3D
Source/Rivet/Renderer/3D/Camera3D.h
Source/Rivet/Renderer/3D/Camera3D.cpp
Source/Rivet/Renderer/3D/Mesh.h
Source/Rivet/Renderer/3D/Mesh.cpp
Source/Rivet/Renderer/3D/ObjLoader.h
Source/Rivet/Renderer/3D/ObjLoader.cpp
# Physics — 2D
Source/Rivet/Physics/2D/PhysicsTypes.h
Source/Rivet/Physics/2D/Physics.h
Source/Rivet/Physics/2D/Physics.cpp
)

add_library(Rivet STATIC)

target_sources(Rivet PRIVATE ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Rivet PUBLIC glfw)
target_link_libraries(Rivet PUBLIC glad)
target_link_libraries(Rivet PUBLIC glm)
target_link_libraries(Rivet PUBLIC spdlog)
target_link_libraries(Rivet PUBLIC imgui)
target_link_libraries(Rivet PUBLIC box2d)

target_include_directories(Rivet PUBLIC "Source" "Vendor/stb" "Vendor/miniaudio")

# miniaudio needs dl, pthread, and m on Linux
if(UNIX)
    target_link_libraries(Rivet PUBLIC dl pthread m)
endif()

target_precompile_headers(Rivet PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Rvtph.h"
)
