 #pragma once
#include <windows.h>

#include "FontTexture.h"
#include "TextureLib.h"
#include "UiPlane.h"
class UiText :
    public UiPlane
{
    FontTexture* font;
    Vector2f offset = Vector2f(0,0);
    float fontSize = 12;
    const float ScaleFactor = 8;
    float rowHeight=0;
    float texSize = 1024;

    float letterWidth=0;
    int activeRow = 1;
    

    void addCharacter(char letter)
    {
        /*
       
        int amountOfPOints = this->points.size();
        float texSize = 1024;
        Vector2f polygonSize= leftBounderyPos- rigtBounderyPos;
        float widthRatio = polygonSize.x / polygonSize.y;
        widthRatio *= fontSize;
		leftBounderyPos = leftBounderyPos / texSize;
        rigtBounderyPos = rigtBounderyPos / texSize;
        this->addPoint(offset.x +0-1,  + 0, 0);
        this->addPoint(offset.x + 1* widthRatio - 1,  + 0, 0);
        this->addPoint(offset.x + 1* widthRatio - 1,  fontSize, 0);
        this->addPoint(offset.x + 0 - 1,   fontSize, 0);
        offset.x +=1.3* widthRatio;

        this->addVertex(amountOfPOints+0, { 0.000000, 1.000000 ,0.000000 }, { leftBounderyPos .x,1 - rigtBounderyPos.y });
        this->addVertex(amountOfPOints + 1, { 0.000000, 1.000000, 0.000000 }, { rigtBounderyPos.x ,1 - rigtBounderyPos.y });
        this->addVertex(amountOfPOints + 2, { 0.000000, 1.000000 ,0.000000 }, { rigtBounderyPos.x,1- leftBounderyPos.y });
        this->addVertex(amountOfPOints + 3, { 0.000000, 1.000000, 0.000000 }, { leftBounderyPos.x, 1-leftBounderyPos.y});

        this->addFace({ amountOfPOints + 0,amountOfPOints + 1,amountOfPOints + 2,amountOfPOints + 3 });


        std::cout << "test";
        */
       // std::cout << letter << ": "<<std::endl;
        if (letter == ' ')
            offset.x += letterWidth/2;
        if (letter == '\n')
        {
            activeRow++;
            offset =Vector2f(0,0);
        }

        Vector2f leftBounderyPos, rigtBounderyPos, Offset;
        Float advance;
        font->getChar(letter, &leftBounderyPos, &rigtBounderyPos, &Offset, &advance);
    //    std::cout << "leftBounderyPos: " << leftBounderyPos << std::endl;;
      //  std::cout << "rigtBounderyPos: " << rigtBounderyPos << std::endl;;
  //      std::cout << "Offset: " << leftBounderyPos << std::endl;;
//        std::cout << "advance: " << advance << std::endl;;

        float letterWidtt = rigtBounderyPos.x - leftBounderyPos.x;
        float letterHeight= rigtBounderyPos.y - leftBounderyPos.y;
        letterWidtt =  (letterWidtt* fontSize)/ ScaleFactor;
        letterHeight = (letterHeight * fontSize)/ ScaleFactor;

      //  std::cout << "letterWidtt: " << letterWidtt << std::endl;;
       // std::cout << "letterHeight: " << letterHeight << std::endl;



        Vector2f leftUp = Vector2f(0,(-1* this->rowHeight)*activeRow+letterHeight)+offset;
        Vector2f rightDown = Vector2f(letterWidtt , (-1 * this->rowHeight) * activeRow)+offset;



       // leftBounderyPos.x, 1 - rigtBounderyPos.y
    

        Vector2f LeftUpUV = Vector2f(leftBounderyPos.x / texSize, 1 - leftBounderyPos.y/ texSize);
        Vector2f rightDownUV = Vector2f(rigtBounderyPos.x/texSize, 1-rigtBounderyPos.y / texSize);

        this->addRect(leftUp, rightDown, LeftUpUV , rightDownUV);
        offset = offset + Vector2f(letterWidtt, 0);
      //  std::cout << std::endl << std::endl;

    }

    virtual void cleanGeo() override
    {
        UiPlane::cleanGeo();
        offset.x = 0;
        offset.y = 0;
        activeRow = 1;
    }


    void setScaleData()
    {
        Vector2f leftBounderyPos, rigtBounderyPos, Offset;
        Float advance;

 
        font->getChar('A', &leftBounderyPos, &rigtBounderyPos, &Offset, &advance);
        float letterWidtt = rigtBounderyPos.x - leftBounderyPos.x;
        float letterHeight = rigtBounderyPos.y - leftBounderyPos.y;


        this->rowHeight = (letterHeight * fontSize) / ScaleFactor;
        this->letterWidth = (letterWidtt * fontSize) / ScaleFactor;
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
//        set_render_mode(GL_LINE);

        setScaleData();

        for (char letter : text)
        {
            addCharacter(letter);
        }
        this->init();
   
    }
};

