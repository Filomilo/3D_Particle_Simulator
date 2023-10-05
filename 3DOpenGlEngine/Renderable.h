#pragma once
class Renderable
{
private:


	virtual void renderProc()
	{

	}

	bool shouldRender=true;
public:
	bool is_should_render() const
	{
		return shouldRender;
	}

	void set_should_render(bool should_render)
	{
		shouldRender = should_render;
	}

	void render()
	{
		if (shouldRender)
			this->renderProc();
	}
};

