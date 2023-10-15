#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 Color;



uniform mat4 camera;
uniform mat4 model;

void main()
{
    gl_Position = camera*model * vec4(aPos.x, aPos.y,aPos.z, 1.0);
    Color=aColor;
}