
#version 330 core
#define MAXLIGHTS 9

out vec4 FragColor;
in vec2 Uv;
in vec3 N;
in vec3 P;
uniform vec3 eyeP;
uniform sampler2D colorTexture;
uniform sampler2D normalTexture;
uniform sampler2D roughTexture;
uniform sampler2D emissionTexture;













	struct LightStructType
	{
		int type;
		float intensity;
		vec3 color;
		vec3 position;
		vec3  direction;
		float angle;
		
	};


	


	struct lightData
	{
		int amtofLight;
		float ambientIntensity;
		vec3 ambientColor;
		LightStructType lightTypeData[MAXLIGHTS];
	};

	uniform lightData light_data;
	







void main()
{
    
	
	vec3 objectColor =vec3( texture(colorTexture, Uv));
	vec3 objectNormal =vec3( texture(normalTexture, Uv).xyz*2-1);
	vec3 objectRough =normalize(vec3( texture(roughTexture, Uv)));
	vec3 ambientLight=light_data.ambientColor*light_data.ambientIntensity;

	vec3 norm = normalize(N);

	vec3 lightDiff=vec3(0);
	
	vec3 lightDir = normalize(light_data.lightTypeData[0].position - P);  
	float lightVal=max(dot(norm,lightDir),0);
	vec3 diffuse=lightVal*light_data.lightTypeData[0].color;
	lightDiff+=diffuse;
	
	vec3 viewDir = normalize(eyeP-P);
	vec3 reflectDir=reflect(-lightDir,norm);
	float spec=pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular=light_data.lightTypeData[0].color*(spec);
	vec3 finalColor=vec3((ambientLight+lightDiff)*objectColor+objectRough.r*specular);
    FragColor=vec4(finalColor,1);
	// FragColor=vec4(objectColor ,1);

} 