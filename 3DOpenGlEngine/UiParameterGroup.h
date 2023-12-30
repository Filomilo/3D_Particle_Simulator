/**
 * @file UiParameterGroup.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conatinng ui paremter group
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <ostream>

#include "UiParameter.h"
#include <vector>
/**
 * @brief Ui parameter group 
 * 
 * class conating and alowwing for selection and modificatin of flaot parameters
 * 
 */
class UiParameterGroup
{
private:
/**
 * @brief name of parametr group
 * 
 * showing name allowing for better segregating parametrs
 * 
 */
	std::string name;

/**
 * @brief list of paramtes
 * 
 * list of float parametrs that you can switch between and edit
 * 
 */
	std::vector<std::shared_ptr<UiParameter>> parameters_;
/**
 * @brief selcted paremater
 * 
 * currecntly selcted paramter that yo can edit
 * 
 */
	int selectedParamater = 0;


public:
/**
 * @brief Construct a new Ui Parameter Group object
 * 
 * consturct parametr group with provided name
 * 
 * @param name name of paramter group
 */
	explicit UiParameterGroup(const std::string& name)
		: name(name)
	{
	}

/**
 * @brief Get the name object
 * 
 * 
 * @return std::string name of parmeter group 
 */
	std::string get_name() const
	{
		return name;
	}
/**
 * @brief Set the name object
 * 
 * @param name name of paramter group
 */
	void set_name(std::string name)
	{
		this->name = name;
	}
/**
 * @brief increase selction of paramters
 * 
 * incraease selcted paramter nad updated ui based on that, loops if increased too much
 * 
 */
	void icreaseSelection()
	{
		selectedParamater = (selectedParamater + 1) % parameters_.size();
	}
	/**
 * @brief decreases selction of paramters
 * 
 * decreses selcted paramter nad updated ui based on that, loops if decreased too much
 */
	void decreaseSelection()
	{
		selectedParamater = (selectedParamater - 1) % parameters_.size();
	}
/**
 * @brief increse value of selected paramter
 * 
 * increses selcted paramter by its set step value
 * 
 */
	void increaseSelectedParam()
	{
		parameters_[selectedParamater]->increaseVal();
	}
/**
 * @brief decrease value of selected paramter
 * 
 * decreases selcted paramter by its set step value
 * 
 */
	void decreaseSelectedParam()
	{
		parameters_[selectedParamater]->decreaseVal();
	}
/**
 * @brief add pramter
 * 
 * adds editable ui pramter to grou[
 * 
 * @param ui_parameter ponter to paramter
 */
	void addParameter(std::shared_ptr<UiParameter> ui_parameter)
	{
		parameters_.push_back(ui_parameter);
	}
	/**
	 * @brief print fucniton
	 * 
	 * a function helping iwth debuggin by priting ui paramter group in console
	 * 
	 * @param os 
	 * @param obj 
	 * @return std::ostream& 
	 */
	friend std::ostream& operator<<(std::ostream& os, const UiParameterGroup& obj)
	{
		 os << "name: " << obj.name<<": \n";
		int i = 0;
		for (std::shared_ptr<UiParameter> element : obj.parameters_)
		{
			if (obj.selectedParamater == i)
				os << "Selected: ";
			os << *element << std::endl;
				i++;
		}
		os << std::endl;
		return  os;
	}
	/**
	 * @brief Get the Paramters object
	 * 
	 * @return std::vector<std::shared_ptr<UiParameter>> returns list of paramters 
	 */
	std::vector<std::shared_ptr<UiParameter>> getParamters()
	{
		return parameters_;
	}
/**
 * @brief Get the Selected object
 * 
 * @return int  retruns index of selected object
 */
	int getSelected()
	{
		return selectedParamater;
	}
};

