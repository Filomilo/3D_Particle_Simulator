#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;


out vec2 Uv;

uniform mat4 model;

void main()
{
    gl_Position = model*vec4(aPos.x-1, aPos.y+1,aPos.z, 1.0);
    Uv=aUv;
}