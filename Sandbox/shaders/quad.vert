#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_UV;
layout(location = 2) in vec4 a_Tint;

uniform mat4 u_ViewProj;

out vec2 v_UV;
out vec4 v_Tint;

void main()
{
    v_UV    = a_UV;
    v_Tint  = a_Tint;
    gl_Position = u_ViewProj * vec4(a_Position, 0.0, 1.0);
}
