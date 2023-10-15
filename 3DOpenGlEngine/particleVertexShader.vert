#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float aPscale;
out vec3 Color;



uniform mat4 camera;
uniform mat4 model;

void main()
{
    vec4 worldPos=model*vec4(aPos,1);
    vec4 cameraPos=camera*worldPos;
    float dist=length(cameraPos.xyz);
    gl_Position = camera*model * vec4(aPos.x, aPos.y,aPos.z, 1.0);
    Color=aColor;
      gl_PointSize = aPscale/dist;
}