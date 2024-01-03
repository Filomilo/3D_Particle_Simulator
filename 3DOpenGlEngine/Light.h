/**
 * @file Light.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conating class light
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <vector>

#include "ShaderProgram.h"
#include "Vector3f.h"
/**
 * @brief max amount of lights in shaders
 * 
 */
#define  MAXLIGHTS 9
/**
 * @brief class light 
 * 
 * calss for handlig light in scene
 * 
 */
class Light
{
protected:
/**
 * @brief type of light
 * 
 * type of light that could bes used by scene, curennyl only point light is handled
 * 
 */
	enum LIGHTYTYPE
	{
		POINYLIGHT,
		DIRECTIONALLIGHT,
		SPOTLIHGT
	};



/**
 * @brief structure of light apramters passed to sahder
 * 
 */
	struct LightStructType
	{
		LIGHTYTYPE type;
		float intensity;
		Vector3f color;
		Vector3f position;
		Vector3f  direction;
		float angle;
		
	};


/**
 * @brief number of light
 * 
 */
	char lightNum;
/**
 * @brief arrat of ally light and data bout to it to be apsed by shader
 * 
 */
	struct lightData
	{
		int lightCounter;
		float ambientIntensity;
		Vector3f ambientColor;
		LightStructType lightTypeData[MAXLIGHTS];
	};

	
	

public:
/**
 * @brief light data conaitng lal parameters
 * 
 */
	static lightData light_data;
/**
 * @brief Construct a new Light object
 * 
 */
	Light();
/**
 * @brief Get the Ambient Intensity object
 * 
 * @return Float 
 */
	static Float getAmbientIntensity();
/**
 * @brief Set the Ambient Intensity object
 * 
 * @param val aambient inesity of lifgr
 */
	static void setAmbientIntensity(float val);
/**
 * @brief Get the Ambient Color object
 * 
 * @return Vector3f 
 */
	static Vector3f getAmbientColor();
	/**
	 * @brief Set the Ambient Color object
	 * 
	 * @param col 
	 */
	static void setAmbientColor(Vector3f col);
/**
 * @brief Set the Light Color object
 * 
 * @param color 
 */
	void setLightColor(Vector3f color);
/**
 * @brief Get the Light Color object
 * 
 * @return Vector3f 
 */
	Vector3f getLightColor();
/**
 * @brief Set the Light Intensity object
 * 
 * @param intensity 
 */
	void setLightIntensity(float intensity);
	/**
	 * @brief Get the Light Intensity object
	 * 
	 * @return Float 
	 */
	Float getLightIntensity();
/**
 * @brief Set the Light Type object
 * 
 * @param type 
 */
	void setLightType(LIGHTYTYPE type);
/**
 * @brief Get the Light Type object
 * 
 * @return LIGHTYTYPE 
 */
	LIGHTYTYPE getLightType();
/**
 * @brief apply light to sahder
 * 
 * @param shader 
 */
	void applyLight(ShaderProgram* shader);


};

