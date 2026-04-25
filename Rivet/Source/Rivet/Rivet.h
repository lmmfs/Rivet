#pragma once

#include <glad/gl.h>

// Core
#include "Core/App.h"
#include "Core/Editor.h"
#include "Core/Input.h"
#include "Core/Logger.h"
#include "Core/Window.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventQueue.h"
#include "Core/Assets/TextureManager.h"
#include "Core/Assets/ShaderManager.h"
#include "Core/Assets/AudioManager.h"
#include "Core/Audio/Audio.h"
#include "Core/UI.h"

// Renderer — Common
#include "Renderer/Common/Shader.h"
#include "Renderer/Common/Buffer.h"
#include "Renderer/Common/BufferLayout.h"
#include "Renderer/Common/Texture.h"

// Renderer — 2D
#include "Renderer/2D/Camera.h"
#include "Renderer/2D/Renderer.h"

// Physics — 2D
#include "Physics/2D/Physics.h"
