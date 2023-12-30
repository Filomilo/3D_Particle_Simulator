/**
 * @file Renderable.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file containg renderable class file
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
/**
 * @brief virtual rendreabble class
 * 
 * virutal class used to hold all renderable object in one place
 * 
 */
class Renderable
{
private:

/**
 * @brief virtual method implement by object to old proces of rendering
 * 
 */
	virtual void renderProc()
	{

	}
/**
 * @brief state wheter or not this object should be rendered
 * 
 */
	bool shouldRender=true;
public:
/**
 * @brief retunrs wheter or object should be rendered
 * 
 * @return true 
 * @return false 
 */
	bool is_should_render() const
	{
		return shouldRender;
	}
/**
 * @brief Set the should render object
 * 
 * @param should_render 
 */
	void set_should_render(bool should_render)
	{
		shouldRender = should_render;
	}
/**
 * @brief activate render procorces of object
 * 
 * main method of virutal class activating on object in engine
 */
	void render()
	{
		if (shouldRender)
			this->renderProc();
	}
};

