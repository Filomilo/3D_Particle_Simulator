#include "TextureLib.h"
#include "FontTexture.h"
 Texture* TextureLib::ArialFontTex=nullptr;


void TextureLib::initTextureLib()
{
	
	TextureLib::ArialFontTex = new FontTexture("Assets/arial.ttf", "Assets/arial.png");

}
