/**
 * @file FontTexture.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng font textuer calsls
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#pragma warning(disable:4996)
#include "Texture.h"
#include "Vector2f.h"

/**
 * @brief calss for gerneating  font texture
 * 
 */
class FontTexture :
    public Texture
{
    /**
     * @brief main method to generate fotn texture
     * 
     * @param fontFileName font file
     * @param destinationTex desitino of font texute
     */
    void genFontTex(std::string fontFileName, std::string  destinationTex);


public:
/**
 * @brief lcahracter to ber genrated start
 * 
 */
    int charBeigin = 32;
    /**
     * @brief amount f cahracter to ber genreated
     * 
     */
    int charAmount = 96;
    void* charData=nullptr;

/**
 * @brief Construct a new Font Texture object
 * 
 * @param fontFileName 
 * @param destinationTex 
 */
    FontTexture(std::string fontFileName, std::string destinationTex);
    /**
     * @brief Get the Char object
     * 
     * returns in pointer data aobut sepcifc postion of character sepcifed
     * 
     * @param letter 
     * @param upperLeftPostion 
     * @param rightDoownPostiion 
     * @param offset 
     * @param advance 
     */
    void getChar(char letter, Vector2f* upperLeftPostion, Vector2f* rightDoownPostiion, Vector2f* offset, std::shared_ptr<Float> advance);

};

