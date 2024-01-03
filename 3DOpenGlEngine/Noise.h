/**
 * @file Noise.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaiing noise class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include "FastNoiseLite.h"
#include "Vector3f.h"

/**
 * class for andling noise values from fast noise.
 */
class Noise
{


public:
	/**
	 * main method taht returns vectro3f noise from fast noise liste with sepcifed seed and frequency at specifedpo siton.
	 * 
	 * \param pos postion to get noise in
	 * \param seed seed of noise
	 * \param frequancy frequency of noise
	 * \return nosie value
	 */
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

