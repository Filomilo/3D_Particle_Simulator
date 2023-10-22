
#version 330 core

out vec4 FragColor;
in vec2 Uv;
uniform sampler2D colorTexture;


void main()
{
    
		vec4 objectColor =vec4( texture(colorTexture, Uv));

	
    FragColor=vec4(objectColor);

} 