#pragma once
#include "ShaderProgram.h"



class ShaderLib
{
public:
	static ShaderProgram* phongShader;
	static ShaderProgram* guideShader;

	static void iniitShaderLib();

	static void uninnit()
	{
		delete phongShader;
		delete guideShader;
	}

};

