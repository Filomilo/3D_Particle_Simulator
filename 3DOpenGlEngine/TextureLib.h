/**
 * @file TextureLib.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg texture library class
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "Texture.h"
/**
 * @brief mainyl static class conating txture
 * 
 * class intielized at start of 3d eingine conaitng texture to be used by other instance, currentyl on airal font
 * 
 */
class TextureLib
{

public:
/**
 * @brief point to texture
 * 
 */
	static  std::shared_ptr<Texture> ArialFontTex;

/**
 * @brief consturctor that intlizes all static textures
 * 
 */
	static void initTextureLib();
/**
 * @brief a destructro delteign textures
 * 
 */
	static void uninnit()
	{
		ArialFontTex = nullptr;

	}
};

