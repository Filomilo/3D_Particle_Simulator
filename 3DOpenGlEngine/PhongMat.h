#pragma 
#include "Material.h"
#include "ShaderLib.h"

class PhongMat:
public Material
{
private:

	Texture* colorTex=nullptr;
	Texture* normalTex = nullptr;
	Texture* emissionTex = nullptr;
	Texture* roughTex = nullptr;


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


	Texture* get_color_tex() const
	{
		return colorTex;
	}

	void set_color_tex(Texture* color_tex)
	{
		colorTex = color_tex;
	}

	Texture* get_normal_tex() const
	{
		return normalTex;
	}

	void set_normal_tex(Texture* normal_tex)
	{
		normalTex = normal_tex;
	}

	Texture* get_emission_tex() const
	{
		return emissionTex;
	}

	void set_emission_tex(Texture* emission_tex)
	{
		emissionTex = emission_tex;
	}


	~PhongMat()
	{
		delete colorTex;
		delete normalTex;
		delete emissionTex;
		delete roughTex;
	}

	void set_color_tex(const char* str, int i, int i1, int i2)
	{
		set_color_tex(new Texture(str, i, i1, i2));
	}

	void set_normal_tex(const char* str, int i, int i1, int i2)
	{
		set_normal_tex(new Texture(str, i, i1, i2));
	}

	void set_rough_tex(Texture* str)
	{
		
	}

	void set_rough_tex(const char* str, int i, int i1, int i2, int fomrat=GL_ALPHA)
	{
		set_rough_tex(new Texture(str, i, i1, i2, fomrat));
	}
};

