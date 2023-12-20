#include "ShaderLib.h"
#include "ShaderProgram.h"

ShaderProgram* ShaderLib::phongShader = nullptr;
ShaderProgram* ShaderLib::guideShader = nullptr;
ShaderProgram* ShaderLib::particleShader = nullptr;
ShaderProgram* ShaderLib::UiShader = nullptr;
ShaderProgram* ShaderLib::particleShaderInstanced = nullptr;

void ShaderLib::iniitShaderLib()
{
	ShaderLib::phongShader = new ShaderProgram("phongVertexShader.vert", "phongFragmentShader.frag");
	ShaderLib::phongShader->addAttribute("Uv", Attribute::VECTOR2F);
	ShaderLib::phongShader->addAttribute("N", Attribute::VECTOR3F);
	ShaderLib::phongShader->setInt("colorTexture", 0);
	ShaderLib::phongShader->setInt("normalTexture", 1);
	ShaderLib::phongShader->setInt("roughTexture", 2);
	ShaderLib::phongShader->setInt("emissionTexture", 3);


	ShaderLib::guideShader = new ShaderProgram("guideVertexShader.vert","guideFragmentShader.frag");


	ShaderLib::particleShader = new ShaderProgram("particleVertexShader.vert", "particleFragmentShader.frag");
	ShaderLib::particleShader->addAttribute("Cd", Attribute::VECTOR3F);
	ShaderLib::particleShader->addAttribute("pscale", Attribute::FLOAT);

	ShaderLib::UiShader = new ShaderProgram("UiVertexShader.vert", "UiFragmentShader.frag");
	ShaderLib::UiShader->addAttribute("Uv", Attribute::VECTOR2F);
	ShaderLib::UiShader->setInt("colorTexture", 0);


	ShaderLib::particleShaderInstanced= new ShaderProgram("particleInstnacedVertexShader.vert", "particleInstnacedFragmentShader.frag");

}

