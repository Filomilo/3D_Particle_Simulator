#pragma once
#include <windows.h>

#include "FontTexture.h"
#include "TextureLib.h"
#include "UiPlane.h"
class UiText :
    public UiPlane
{
    FontTexture* font;
    float offset = 0;
    float fontSize = 1;
    void addCharacter(char letter)
    {
        Vector2f leftBounderyPos,rigtBounderyPos,Offset;
        Float advance;
        font->getChar(letter, &leftBounderyPos, &rigtBounderyPos,&Offset,&advance);
        int amountOfPOints = this->points.size();
        float texSize = 1024;
        Vector2f polygonSize= leftBounderyPos- rigtBounderyPos;
        float widthRatio = polygonSize.x / polygonSize.y;
        widthRatio *= fontSize;
		leftBounderyPos = leftBounderyPos / texSize;
        rigtBounderyPos = rigtBounderyPos / texSize;
        this->addPoint(offset +0-1,  + 0, 0);
        this->addPoint(offset + 1* widthRatio - 1,  + 0, 0);
        this->addPoint(offset + 1* widthRatio - 1,  fontSize, 0);
        this->addPoint(offset + 0 - 1,   fontSize, 0);
        offset += 1* widthRatio;

        this->addVertex(amountOfPOints+0, { 0.000000, 1.000000 ,0.000000 }, { leftBounderyPos .x,1 - rigtBounderyPos.y });
        this->addVertex(amountOfPOints + 1, { 0.000000, 1.000000, 0.000000 }, { rigtBounderyPos.x ,1 - rigtBounderyPos.y });
        this->addVertex(amountOfPOints + 2, { 0.000000, 1.000000 ,0.000000 }, { rigtBounderyPos.x,1- leftBounderyPos.y });
        this->addVertex(amountOfPOints + 3, { 0.000000, 1.000000, 0.000000 }, { leftBounderyPos.x, 1-leftBounderyPos.y});

        this->addFace({ amountOfPOints + 0,amountOfPOints + 1,amountOfPOints + 2,amountOfPOints + 3 });


        std::cout << "test";
    }

    virtual void cleanGeo() override
    {
        UiPlane::cleanGeo();
        offset = 0;
    }

public:

    void setText(std::string text)
    {

        this->cleanGeo();
        for (char letter : text)
        {
            addCharacter(letter);
        }
        updateVbo();
        updateEbo();
    }

    UiText(std::string text,float fontSize=1): UiPlane(nullptr)
    {
        setMat(new Material(ShaderLib::UiShader));
        this->fontSize = fontSize;
        font =(FontTexture*) TextureLib::ArialFontTex;
        this->mat->addTex("ColorTexture",font);
        set_usage(GL_DYNAMIC_DRAW);
        for (char letter : text)
        {
            addCharacter(letter);
        }
        this->init();
   
    }
};

