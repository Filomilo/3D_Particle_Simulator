/**
 * @file UiText.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conating uiText clas
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 #pragma once
#include <windows.h>

#include "FontTexture.h"
#include "TextureLib.h"
#include "UiPlane.h"
/**
 * @brief Ui class alowing to print basic text on screen
 * 
 */
class UiText :
    public UiPlane
{
    /**
     * @brief Texture map with font symbols
     * 
     * Texture class that handles gneret font texture that contains all letetrs nad symbols used int text rendering
     */
	 std::shared_ptr<FontTexture> font;
     /**
      * @brief help varaible to define character postion
      * 
      * its a help value used to define character position on screen after print previous position
      * 
      */
    Vector2f offset = Vector2f(0,0);
    /**
     * @brief size of font to define size of character on screen
     * 
     */
    float fontSize = 12;
    /**
     * @brief scale factor in reenedering
     * 
     * a heling value to better control size of characters on screen
     */
    const float ScaleFactor = 8;
    /**
     * @brief global varaible 
     * 
     * a varaible set base on fint size to help with priniting text on screen 
     * 
     */
    float rowHeight=0;
    /**
     * @brief size of font texture
     * 
     * pixel resultion of texture used to print texture
     * 
     */
    float texSize = 1024;
/**
 * @brief a varaible defing width of character
 * 
 * a helpful varaible used to for renderign characters on screen
 * 
 */
    float letterWidth=0;
    int activeRow = 1;
    
/**
 * @brief fucntion print next character on screne
 * 
 * a method taht used to print character on scrren next in positon or 
 * to offset cursor if its space or new line
 * 
 * @param letter 
 */
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
        if (letter == ' ') {
            offset.x += letterWidth/2;
            return;
        }
        if (letter == '\n')
        {
            activeRow++;
            offset =Vector2f(0,0);
            return;
        }

        Vector2f leftBounderyPos, rigtBounderyPos, Offset;
        std::shared_ptr<Float> advance = std::make_shared<Float>();
        font->getChar(letter, &leftBounderyPos, &rigtBounderyPos, &Offset, advance);
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
/**
 * @brief cleanup method
 * 
 * an method overide used for reset geomtery and cursor
 * 
 */
    virtual void cleanGeo() override
    {
        UiPlane::cleanGeo();
        offset.x = 0;
        offset.y = 0;
        activeRow = 1;
    }

/**
 * @brief Set the Scale Data 
 * 
 * a mrthod taht based on parmeter texture set size paramters used for printing
 * 
 */
    void setScaleData()
    {
        Vector2f leftBounderyPos, rigtBounderyPos, Offset;
        std::shared_ptr<Float> advance=std::make_shared<Float>();

 
        font->getChar('A', &leftBounderyPos, &rigtBounderyPos, &Offset, advance);
        float letterWidtt = rigtBounderyPos.x - leftBounderyPos.x;
        float letterHeight = rigtBounderyPos.y - leftBounderyPos.y;


        this->rowHeight = (letterHeight * fontSize) / ScaleFactor;
        this->letterWidth = (letterWidtt * fontSize) / ScaleFactor;
    }


public:
/**
 * @brief Set the Text object
 * 
 * set text and rest gemmetry and cretes a new one with provided text
 * 
 * @param text  text to be shown on scrren
 */
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


/**
 * @brief Construct a new Ui Text object
 * 
 * constuct a new ui text object with specifed text nad size, its set deault font and calcuates sieze paramters based on that
 * 
 * @param text 
 * @param fontSize 
 */
    UiText(std::string text,float fontSize=1): UiPlane(nullptr)
    {
        setMat(std::make_shared<Material>(ShaderLib::UiShader));
        this->fontSize = fontSize;
        font =std::static_pointer_cast<FontTexture>(TextureLib::ArialFontTex);
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

