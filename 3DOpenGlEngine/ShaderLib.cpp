#include "ShaderLib.h"
#include "ShaderProgram.h"

ShaderProgram* ShaderLib::phongShader = nullptr;

void ShaderLib::iniitShaderLib()
{
	ShaderLib::phongShader = new ShaderProgram("phongVertexShader.vert", "phongFragmentShader.frag");
	ShaderLib::phongShader->addAttribute("Uv", Attribute::VECTOR2F);
	ShaderLib::phongShader->addAttribute("N", Attribute::VECTOR3F);
	ShaderLib::phongShader->setInt("colorTexture", 0);
	ShaderLib::phongShader->setInt("normalTexture", 1);
	ShaderLib::phongShader->setInt("roughTexture", 2);
	ShaderLib::phongShader->setInt("emissionTexture", 3);
}

