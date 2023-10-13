#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aN;



out vec2 Uv;
out vec3 N;
out vec3 P;
out vec3 eyeP;


uniform mat4 camera;
uniform mat4 model;

void main()
{
    gl_Position = camera*model * vec4(aPos.x, aPos.y,aPos.z, 1.0);
    Uv=vec2(aUv); 
    N=aN;
    P=aPos;
}