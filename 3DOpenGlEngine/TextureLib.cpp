#include "TextureLib.h"
#include "FontTexture.h"
  std::shared_ptr<Texture> TextureLib::ArialFontTex=nullptr;


void TextureLib::initTextureLib()
{
	
	TextureLib::ArialFontTex = std::make_shared<FontTexture>("Assets/arial.ttf", "Assets/arial.png");

}
