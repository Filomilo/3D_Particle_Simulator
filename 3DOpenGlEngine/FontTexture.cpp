#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"



#include "Texture.h"

#include "FontTexture.h"

#include "Vector2f.h"
#define BufferSize 100000
#define fontRes 1024
#define fontHeight 30

void FontTexture::genFontTex(std::string fontFileName, std::string saveFileName) 
{
    unsigned char* fontBuffer=new   unsigned char[BufferSize];
    FILE* fontFile;
    fopen_s(&fontFile, fontFileName.c_str(), "rb");

    if(!fontFile)
    {
        throw(std::runtime_error("could not load font file"));
    }
    fseek(fontFile, 0, SEEK_END);
    long fileSize= ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);

    unsigned char* fontData = new unsigned char[fileSize];
    if(!fontData)
    {
        fclose(fontFile);
        throw(std::runtime_error("could not allocate memory"));;
    }

    fread(fontData, 1, fileSize, fontFile);
    fclose(fontFile);

    unsigned char* bitmap = new unsigned char[fontRes* fontRes];




    stbtt_BakeFontBitmap(fontData, 0, fontRes / sqrt(96), bitmap, fontRes, fontRes, charBeigin, charAmount, (stbtt_bakedchar*)charData);
    stbi_write_png(saveFileName.c_str(), fontRes, fontRes,1,bitmap, fontRes);

	//  this->genData(data, fontRes, fontRes, 8, GL_RGBA);
	delete bitmap;
    delete fontBuffer;
    genTex(saveFileName, 1024, 1024, 8, GL_RED);

}

FontTexture::FontTexture(std::string fontFileName, std::string destinationTex)
{
    charData = new stbtt_bakedchar[96];
    genFontTex(fontFileName, destinationTex);
}

void FontTexture::getChar(char letter, Vector2f* upperLeftPostion, Vector2f* rightDoownPostiion, Vector2f* offset, Float* advance)
{
    stbtt_bakedchar info = ((stbtt_bakedchar*)this->charData)[letter - charBeigin];
    upperLeftPostion->x = info.x0;
    upperLeftPostion->y = info.y0;

    rightDoownPostiion->x = info.x1;
    rightDoownPostiion->y = info.y1;

    offset->x = info.xoff;
    offset->y = info.yoff;

    advance->x = info.xadvance;

}

