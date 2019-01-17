#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

class EventManager {
private:
	std::function< bool() > mCondition;
	std::function< void() > mWork;
public:
	/// \brief
	/// Constructor for EventManager.
	/// \param mCondition
	/// This function is a condition to do the next function.
	/// \param mWork
	/// Needs a call for a void function.
	EventManager(std::function< bool() > mCondition, std::function< void() > mWork) :
		mCondition(mCondition),
		mWork(mWork)
	{}

	/// \brief
	/// Extra constructor for keyboard key presses.
	/// \details
	/// This constructor returns what key is pressed on the keyboard.
	/// \param mKey
	/// Needs a key of the keyboard.
	/// \param mWork
	/// Needs a call for a void function.
	EventManager(sf::Keyboard::Key mKey, std::function< void() > mWork) :
		mCondition([mKey]()->bool { return sf::Keyboard::isKeyPressed(mKey); }),
		mWork(mWork)
	{}


	/// \brief
	/// Extra constructor for mouse button presses.
	/// \details
	/// This constructor returns what button is pressed.
	/// \param mButton
	/// Needs a button of the mouse.
	/// \param mWork
	/// Needs a call for a void function.
	EventManager(sf::Mouse::Button mButton, std::function< void() > mWork) :
		mCondition([mButton]()->bool { return sf::Mouse::isButtonPressed(mButton); }),
		mWork(mWork)
	{}

	/// \brief
	/// Function for operator ().
	void operator()() {
		if (mCondition()) {
			mWork();
		}
	}
};

#endif
