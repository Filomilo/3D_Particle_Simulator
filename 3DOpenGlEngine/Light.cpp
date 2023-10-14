#include "Light.h"





  ;



	Light::Light()
	{
		if (light_data.lightCounter >>= MAXLIGHTS)
			throw std::runtime_error("Exceeded maximum amount of lights");
		lightNum = light_data.lightCounter;
		light_data.lightCounter++;
		Light::light_data.lightTypeData[lightNum].color = Vector3f(1, 1, 1);
		Light::light_data.lightTypeData[lightNum].intensity = 1;

	}



	 Float Light::getAmbientIntensity()
	{
		return light_data.ambientIntensity;
	}

	 void Light::setAmbientIntensity(float val)
	{
		light_data.ambientIntensity = val;
	}

	 Vector3f Light::getAmbientColor()
	{
		return light_data.ambientColor;
	}
	 void Light::setAmbientColor(Vector3f col)
	{
		light_data.ambientColor = col;
	}

	void Light::setLightColor(Vector3f color)
	{
		light_data.lightTypeData[lightNum].color = color;
	}

	Vector3f Light::getLightColor()
	{
		return light_data.lightTypeData[lightNum].color;
	}

	void Light::setLightIntensity(float intensity)
	{
		light_data.lightTypeData[lightNum].intensity = intensity;
	}
	Float Light::getLightIntensity()
	{
		return light_data.lightTypeData[lightNum].intensity;
	}

	void Light::setLightType(LIGHTYTYPE type)
	{
		light_data.lightTypeData[lightNum].type = type;
	}

	Light::LIGHTYTYPE Light::getLightType()
	{
		return 	light_data.lightTypeData[lightNum].type;
	}

	void Light::applyLight(ShaderProgram* shader)
	{

	}

	Light::lightData Light::light_data;