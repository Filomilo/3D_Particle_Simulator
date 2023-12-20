#pragma once
#include "Updatable.h"
class Simulatable :
	public Updatable
{
public:
	Simulatable();
	~Simulatable();

	virtual void reset() = 0;

};

