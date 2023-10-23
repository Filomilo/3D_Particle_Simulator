#include "UiSystem.h"
#include "_3DEngine.h"

void UiSystem::update(float timeElpased)
{
	if (_3DEngine::getKeyBoard()->Tab.is_is_clicked()) {
		incrementGroup();
		std::cout << *this<<std::endl;
	}
	if (_3DEngine::getKeyBoard()->arrowUp.is_is_clicked()) {
		groups[activegroup]->icreaseSelection();
		std::cout << *this << std::endl;
	}
	if (_3DEngine::getKeyBoard()->arrowDown.is_is_clicked()) {
		groups[activegroup]->decreaseSelection();
		std::cout << *this << std::endl;
	}


	if (_3DEngine::getKeyBoard()->arrowRight.is_is_clicked()) {
		groups[activegroup]->increaseSelectedParam();
		std::cout << *this << std::endl;
	}
	if (_3DEngine::getKeyBoard()->arrowLeft.is_is_clicked()) {
		groups[activegroup]->decreaseSelectedParam();
		std::cout << *this << std::endl;
	}

}