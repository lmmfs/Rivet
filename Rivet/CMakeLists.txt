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
Source/Rivet/Window.h
Source/Rivet/Window.cpp
Source/Rivet/App.h
Source/Rivet/App.cpp
Source/Rivet/Editor.h
Source/Rivet/Editor.cpp
Source/Rivet/Input.h
Source/Rivet/Input.cpp
Source/Rivet/Logger.h
Source/Rivet/Logger.cpp
Source/Rivet/Events/Event.h
Source/Rivet/Events/EventQueue.h
Source/Rivet/Events/EventQueue.cpp
Source/Rivet/Renderer/Shader.h
Source/Rivet/Renderer/Shader.cpp
Source/Rivet/Renderer/Buffer.h
Source/Rivet/Renderer/Buffer.cpp
Source/Rivet/Renderer/BufferLayout.h
Source/Rivet/Renderer/BufferLayout.cpp
Source/Rivet/Renderer/Texture.h
Source/Rivet/Renderer/Texture.cpp
Source/Rivet/Renderer/Camera2D.h
Source/Rivet/Renderer/Camera2D.cpp
Source/Rivet/Renderer/Renderer2D.h
Source/Rivet/Renderer/Renderer2D.cpp
Source/Rivet/Assets/AssetCache.h
Source/Rivet/Assets/TextureManager.h
Source/Rivet/Assets/TextureManager.cpp
Source/Rivet/Assets/ShaderManager.h
Source/Rivet/Assets/ShaderManager.cpp
Source/Rivet/Physics/PhysicsTypes.h
Source/Rivet/Physics/Physics.h
Source/Rivet/Physics/Physics.cpp
Source/Rivet/Audio/AudioEngine.h
Source/Rivet/Audio/AudioEngine.cpp
Source/Rivet/Audio/Sound.h
Source/Rivet/Audio/Audio.h
Source/Rivet/Audio/Audio.cpp
Source/Rivet/Assets/AudioManager.h
Source/Rivet/Assets/AudioManager.cpp
Source/Rivet/UI/Font.h
Source/Rivet/UI/Font.cpp
Source/Rivet/UI/UI.h
Source/Rivet/UI/UI.cpp
Source/Rivet/UI.h
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
