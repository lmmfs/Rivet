#version 460 core

in vec2 v_UV;
in vec4 v_Tint;

uniform sampler2D u_Texture;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_Texture, v_UV) * v_Tint;
}
