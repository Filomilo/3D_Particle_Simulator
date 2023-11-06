#pragma once
#include <list>
#include <vector>

#include "Object.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Material : public Object
{

protected:
	ShaderProgram* shader;
	std::vector< std::shared_ptr<Texture>> textures;


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
	explicit Material(ShaderProgram* shader)
		: shader(shader)
	{
		if (shader == nullptr)
		{
			throw std::runtime_error("cannot create materal with null shader");
		}
	}

	void addTex(std::string name, std::shared_ptr<Texture> tex)
	{
		shader->use();
		shader->setInt("colorTexture", textures.size());
		textures.push_back(tex);

		shader->unuse();
	}



	void apply(glm::mat4 model)
	{
		
		shader->use();
		shader->setMatrix4("model", model);
		bindTex();
	}



	void unapply()
	{
		unBindTex();
		shader->unuse();
	}

	std::list<std::string> getAttributeList()
	{
		return shader->getAttributeList();
	}

	std::map<std::string, Attribute::Types> getAttributeMap()
	{
		return shader->getAttributeMap();
	}

	int getVertexSizeRequired()
		{
		return shader->getVertexSizeRequired();
		};
};

