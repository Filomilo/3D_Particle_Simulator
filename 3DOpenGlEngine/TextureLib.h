#pragma once
#include "Texture.h"

class TextureLib
{

public:
	static Texture* ArialFontTex;


	static void initTextureLib();

	static void uninnit()
	{
		delete ArialFontTex;

	}
};

