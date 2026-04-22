#
# Rivet
#

set(SOURCES
Vendor/stb/stb_image.h
Vendor/stb/stb_image.cpp
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

target_include_directories(Rivet PUBLIC "Source" "Vendor/stb")

target_precompile_headers(Rivet PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Source/Rvtph.h"
)
