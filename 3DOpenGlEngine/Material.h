/**
 * @file Material.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg material class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <list>
#include <vector>

#include "Object.h"
#include "ShaderProgram.h"
#include "Texture.h"
/**
 * @brief matrial calss
 * 
 * class for handlign material made out of apremts for and shaders for texutre
 * 
 */
class Material : public Object
{

protected:
/**
 * @brief shader used by this metrial
 * 
 */
	ShaderProgram* shader;
	/**
	 * @brief list of texture conatined in this matariela
	 * 
	 */
	std::vector< std::shared_ptr<Texture>> textures;

/**
 * @brief bind textures in correct order
 * 
 */
	virtual void bindTex()
	{
		int i = 0;
		for ( std::shared_ptr<Texture> tex : textures)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			tex->bind();
			i++;
		}
	}
	/**
	 * @brief unbinds all the textures
	 * 
	 */
	void unBindTex()
	{
		int i = 0;
		for ( std::shared_ptr<Texture> tex : textures)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			Texture::unbind();
			i++;
		}
	}

public:
/**
 * @brief Construct a new Material object
 * 
 * @param shader sahder used by this materail
 */
	explicit Material(ShaderProgram* shader)
		: shader(shader)
	{
		if (shader == nullptr)
		{
			throw std::runtime_error("cannot create materal with null shader");
		}
	}
/**
 * @brief add texture to matrail
 * 
 * @param name name of exute
 * @param tex texture
 */
	void addTex(std::string name, std::shared_ptr<Texture> tex)
	{
		shader->use();
		shader->setInt("colorTexture", textures.size());
		textures.push_back(tex);

		shader->unuse();
	}


/**
 * @brief appply matrix object transofrmaiton ot sahder and vind textures 
 * 
 * @param model 
 */
	void apply(glm::mat4 model)
	{
		
		shader->use();
		shader->setMatrix4("model", model);
		bindTex();
	}


/**
 * @brief unaplly textures and stops using shader
 * 
 */
	void unapply()
	{
		unBindTex();
		shader->unuse();
	}
/**
 * @brief Get the Attribute List object
 * 
 * @return std::list<std::string> 
 */
	std::list<std::string> getAttributeList()
	{
		return shader->getAttributeList();
	}
/**
 * @brief Get the Attribute Map object
 * 
 * @return std::map<std::string, Attribute::Types> 
 */
	std::map<std::string, Attribute::Types> getAttributeMap()
	{
		return shader->getAttributeMap();
	}
/**
 * @brief Get the Vertex Size Required object
 * 
 * @return int 
 */
	int getVertexSizeRequired()
		{
		return shader->getVertexSizeRequired();
		};
};

