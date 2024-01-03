/**
 * @file PhongMat.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file cocnaitng phong material class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma 
#include "Material.h"
#include "ShaderLib.h"
/**
 * a class that wraps basci phong material to its own class to simplfy mangaing it .
 */
class PhongMat:
public Material
{
private:
	/**
	 * optional pointer to texture color .
	 */
	 std::shared_ptr<Texture> colorTex=nullptr;
	 /**
	  * optional pointer to notmal map of geometry.
	  */
	 std::shared_ptr<Texture> normalTex = nullptr;
	 /**
	  * optional pointer to emsiioin texxture of geometry.
	  */
	 std::shared_ptr<Texture> emissionTex = nullptr;
	 /**
	  * optional pointer to roughness/specular texture of geometry.
	  */
	 std::shared_ptr<Texture> roughTex = nullptr;

	 /**
	  * vind active texture to theit postion in phong shader.
	  * 
	  */
	void bindTex() override
	{
		int i=0;
		glActiveTexture(GL_TEXTURE0 + i++);
		if (colorTex == nullptr)
			Texture::unbind();
		else
			colorTex->bind();

		glActiveTexture(GL_TEXTURE0 + i++);
		if (normalTex == nullptr)
			Texture::unbind();
		else
			normalTex->bind();

		glActiveTexture(GL_TEXTURE0 + i++);
		if (roughTex == nullptr)
			Texture::unbind();
		else
			roughTex->bind();



		glActiveTexture(GL_TEXTURE0 + i++);
		if (emissionTex == nullptr)
			Texture::unbind();
		else
			emissionTex->bind();


			
	}

public:
	PhongMat(): Material(ShaderLib::phongShader)
	{
	
	}

	/**
	 * getter for color texture.
	 * 
	 * \return color texutre
	 */
	 std::shared_ptr<Texture> get_color_tex() const
	{
		return colorTex;
	}
	 /**
	  * setter for color texture.
	  * 
	  * \param color_tex
	  */
	void set_color_tex( std::shared_ptr<Texture> color_tex)
	{
		colorTex = color_tex;
	}
	/**
	 * getter fro normal texture.
	 * 
	 * \return normal map
	 */
	 std::shared_ptr<Texture> get_normal_tex() const
	{
		return normalTex;
	}
	 /**
	  * .setter normal map of model
	  * 
	  * \param normal_tex 
	  */
	void set_normal_tex( std::shared_ptr<Texture> normal_tex)
	{
		normalTex = normal_tex;
	}
	/**
	 * getter for emssion texture.
	 * 
	 * \return 
	 */
	 std::shared_ptr<Texture> get_emission_tex() const
	{
		return emissionTex;
	}
	 /**
	  * setter for emission texture.
	  * 
	  * \param emission_tex
	  */
	void set_emission_tex( std::shared_ptr<Texture> emission_tex)
	{
		emissionTex = emission_tex;
	}
	/**
	 * setter for roughned/sepcular texture.
	 * 
	 * \param tex
	 */
	void set_rough_tex( std::shared_ptr<Texture> tex)
	{
		roughTex = tex;
	}


	~PhongMat()
	{
	
	}
	/**
	 * setter color texture with creation of it already in method.
	 * 
	 * \param str localisation of texture in files
	 * \param i wifth of texutre
	 * \param i1 height of texture
	 * \param i2 bit depth of texture
	 */
	void set_color_tex(const char* str, int i, int i1, int i2)
	{
		set_color_tex(std::make_shared<Texture>(str, i, i1, i2));
	}
	/**
	 * setter normal texture with creation of it already in method.
	 *
	 * \param str localisation of texture in files
	 * \param i wifth of texutre
	 * \param i1 height of texture
	 * \param i2 bit depth of texture
	 */
	void set_normal_tex(const char* str, int i, int i1, int i2)
	{
		set_normal_tex(std::make_shared<Texture>(str, i, i1, i2));
	}
	/**
 * setter rougness texture with creation of it already in method.
 *
 * \param str localisation of texture in files
 * \param i wifth of texutre
 * \param i1 height of texture
 * \param i2 bit depth of texture
 * \param type color type of texture
 */
	void set_rough_tex(const char* str, int i, int i1, int i2, int type=GL_RED)
	{
		set_rough_tex(std::make_shared<Texture>(str, i, i1, i2, type));
	}
	/**
 * setter emsision texture with creation of it already in method.
 *
 * \param str localisation of texture in files
 * \param i wifth of texutre
 * \param i1 height of texture
 * \param i2 bit depth of texture
 */
	 void set_emission_tex(const char* str, int i, int i1, int i2)
	{
		 set_emission_tex(std::make_shared<Texture>(str, i, i1, i2));

	}
};

