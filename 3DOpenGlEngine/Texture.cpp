#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(std::string file, int width, int height, int channels)
	: width(width),
	height(height),
	channels(channels)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &channels, 0);
	if (!data)
	{
		throw std::runtime_error("couldnt load photo");
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}



void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}