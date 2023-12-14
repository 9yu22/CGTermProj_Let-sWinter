#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTexture;

out vec3 fPos;
out vec3 fTexture;

void main() 
{
    fPos = vPos;
    fTexture = vPos;
}