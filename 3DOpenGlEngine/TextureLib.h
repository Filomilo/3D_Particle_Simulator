#pragma once
#include "Texture.h"

class TextureLib
{

public:
	static  std::shared_ptr<Texture> ArialFontTex;


	static void initTextureLib();

	static void uninnit()
	{
		ArialFontTex = nullptr;

	}
};

