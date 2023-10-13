#pragma once
#include <vector>

#include "ShaderProgram.h"
#include "Vector3f.h"

#define  MAXLIGHTS 9

class Light
{
protected:

	enum LIGHTYTYPE
	{
		POINYLIGHT,
		DIRECTIONALLIGHT,
		SPOTLIHGT
	};




	struct LightStructType
	{
		LIGHTYTYPE type;
		float intensity;
		Vector3f color;
		Vector3f position;
		Vector3f  direction;
		float angle;
		
	};



	char lightNum;

	struct lightData
	{
		int lightCounter;
		float ambientIntensity;
		Vector3f ambientColor;
		LightStructType lightTypeData[MAXLIGHTS];
	};

	
	

public:
	static lightData light_data;

	Light();

	static Float getAmbientIntensity();

	static void setAmbientIntensity(float val);

	static Vector3f getAmbientColor();
	static void setAmbientColor(Vector3f col);

	void setLightColor(Vector3f color);

	Vector3f getLightColor();

	void setLightIntensity(float intensity);
	Float getLightIntensity();

	void setLightType(LIGHTYTYPE type);

	LIGHTYTYPE getLightType();

	void applyLight(ShaderProgram* shader);

};

