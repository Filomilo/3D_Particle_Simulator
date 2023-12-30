/**
 * @file ShaderLib.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief filr contaign class shader lib
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "ShaderProgram.h"


/**
 * @brief static shader lib
 * 
 * sahder library class ocnating basci global shader program used in openg
 * 
 */
class ShaderLib
{
public:
/**
 * @brief basic phong sahder
 * 
 */
	static ShaderProgram* phongShader;
	/**
	 * @brief basic guide shader
	 * 
	 * sahder used bu object like lines of ground plane taht is not ffecte by light
	 * 
	 */
	static ShaderProgram* guideShader;
	/**
	 * @brief basic  particel sahder
	 * 
	 * bsic partice lsahder for renderign gl points
	 * 
	 */
	static ShaderProgram* particleShader;
	/**
	 * @brief basci paritlce isnatnece
	 * 
	 * currently the only insnaces shade used in simulation to instnace sphere in points
	 */
	static ShaderProgram* particleShaderInstanced;
	/**
	 * @brief baisc ui shader
	 * 
	 * simple ui shader not affect by light and camera perspecive
	 * 
	 */
	static ShaderProgram* UiShader;
/**
 * @brief method sued to inlil;ize shader programs at start of 3d engine
 * 
 */
	static void iniitShaderLib();
/**
 * @brief method used to remove all sahder form library from opengl
 * 
 */
	static void uninnit()
	{
		delete phongShader;
		delete guideShader;
		delete particleShader;
		delete UiShader;
		delete particleShaderInstanced;
	}

};

