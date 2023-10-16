#pragma once
#include "FastNoiseLite.h"
#include "Vector3f.h"


class Noise
{


public:
	static Vector3f getNoise(Vector3f pos,int seed , float frequancy=0.1)
	{
		FastNoiseLite fast_noise_lite;
		fast_noise_lite.SetFrequency(frequancy);
		Vector3f values;
		for(int i=0;i<3;i++)
		{
			fast_noise_lite.SetSeed(seed + i);
			values[i] = fast_noise_lite.GetNoise(pos.x, pos.y, pos.z);

		}
		return  values.normalize() ;
	}



};

