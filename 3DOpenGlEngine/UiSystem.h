/**
 * @file UiSystem.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg class UiSysytem
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <ostream>

#include "Updatable.h"
#include "_3DEngine.h"
#include "UiParameterGroup.h"
#include "UiText.h"
#include <sstream>

/**
 * @brief class for handling ui interaction
 * 
 * updatable class that print on scren ui text and holds paaramets that 
 * are swithcable and inreacted using keyvoard button allwoing change privided float paramters
 * 
 */
class UiSystem : public Updatable, public UiText
{
private:

/**
 * @brief list of paramtes group 
 * 
 * list of group of paramters that you can siwthc betwen using tab buttons
 * 
 */
	std::vector<std::shared_ptr<UiParameterGroup>> groups;
/**
 * @brief currecly active parameters group
 * 
 * number defing paramters group currecnyl acitive o screen
 */
	int activegroup=0;
/**
 * @brief incremt group method
 * 
 * method allowing to incement active group al loop if parametrs group reach end
 * 
 */
	void incrementGroup()
	{
		activegroup = (activegroup + 1) % groups.size();
		
	}
/**
 * @brief update group text on screen
 * 
 * 
 * updates text on screen based on selected paramters and its values
 */
	void updateGroupText()
	{
		std::stringstream stream;
		stream << groups.at(activegroup)->get_name() << ": "<<"\n\n";
		int i=0;
		for(std::shared_ptr<UiParameter> param : groups.at(activegroup)->getParamters())
		{
			if(groups.at(activegroup)->getSelected() == i)
			{
				stream <<"<<"<< param->getName() << ": " << param->getVal()<<" >>" << '\n';
			}
			else
			stream << param->getName() << ": " << param->getVal()<<'\n';
			i++;
		}
		this->setText(stream.str());
		//std::cout << stream.str() << std::endl;
	}


public:
/**
 * @brief Construct a new Ui System object
 * 
 * basic constructor that set ui text as "-" and size fitted to screen
 */
	UiSystem()
		: UiText("-", 0.008)
	{
	}
/**
 * @brief adds parametr group to list
 * 
 * adds pointer to parameter group to list of pramters gorup to list
 * 
 * @param ui_parameter_group 
 */
	void addParameterGroup( std::shared_ptr<UiParameterGroup> ui_parameter_group)
	{
		groups.push_back(ui_parameter_group);
		updateGroupText();
	}
/**
 * @brief update method
 * 
 * method taht updates paraemter gorup slection and values based on keyboard input in current simulation run
 * 
 * @param timeElpased time since previous simulatin, not used but neccsery in virtual method
 */
	void update(float timeElpased);
/**
 * @brief method to print parametrs on console
 * 
 * method used for debbugin in console operation on paramters group
 * 
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
	friend std::ostream& operator<<(std::ostream& os,  UiSystem& obj)
	{
		return os << *obj.groups[obj.activegroup];
	}
/**
 * @brief not used reset method
 * 
 */
	void reset()
	{

	}
};

