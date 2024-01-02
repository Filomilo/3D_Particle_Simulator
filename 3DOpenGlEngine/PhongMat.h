#pragma 
#include "Material.h"
#include "ShaderLib.h"

class PhongMat:
public Material
{
private:

	 std::shared_ptr<Texture> colorTex=nullptr;
	 std::shared_ptr<Texture> normalTex = nullptr;
	 std::shared_ptr<Texture> emissionTex = nullptr;
	 std::shared_ptr<Texture> roughTex = nullptr;


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


	 std::shared_ptr<Texture> get_color_tex() const
	{
		return colorTex;
	}

	void set_color_tex( std::shared_ptr<Texture> color_tex)
	{
		colorTex = color_tex;
	}

	 std::shared_ptr<Texture> get_normal_tex() const
	{
		return normalTex;
	}

	void set_normal_tex( std::shared_ptr<Texture> normal_tex)
	{
		normalTex = normal_tex;
	}

	 std::shared_ptr<Texture> get_emission_tex() const
	{
		return emissionTex;
	}

	void set_emission_tex( std::shared_ptr<Texture> emission_tex)
	{
		emissionTex = emission_tex;
	}

	void set_rough_tex( std::shared_ptr<Texture> tex)
	{
		roughTex = tex;
	}


	~PhongMat()
	{
	
	}

	void set_color_tex(const char* str, int i, int i1, int i2)
	{
		set_color_tex(std::make_shared<Texture>(str, i, i1, i2));
	}

	void set_normal_tex(const char* str, int i, int i1, int i2)
	{
		set_normal_tex(std::make_shared<Texture>(str, i, i1, i2));
	}
	void set_rough_tex(const char* str, int i, int i1, int i2, int type=GL_RED)
	{
		set_rough_tex(std::make_shared<Texture>(str, i, i1, i2, type));
	}

	 void set_emission_tex(const char* str, int i, int i1, int i2)
	{
		 set_emission_tex(std::make_shared<Texture>(str, i, i1, i2));

	}
};

