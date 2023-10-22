#pragma once
#pragma warning(disable:4996)
#include "Texture.h"



class FontTexture :
    public Texture
{
    void genFontTex(std::string fontFileName, std::string  destinationTex);
public:
    int charBeigin = 32;
    int charAmount = 96;
    void* charData=nullptr;


    FontTexture(std::string fontFileName, std::string destinationTex);

};

