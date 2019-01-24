#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>

class EventManager {
private:
	std::function< bool() > mConditionNoEvent;
	std::function< bool(const sf::Event& event) > mCondition;
	std::function< void() > mWork;
	sf::Event::EventType mEvent;
	bool mCustomEvent;
public:
	bool isEventAndKeyCorrect(
		const sf::Keyboard::Key& key,
		const sf::Event& event,
		const sf::Event::EventType& eventType
	) {
		return (event.type == eventType) && (event.key.code == key);
	}

	/// \brief
	/// Constructor for EventManager.
	/// \param mCondition
	/// This function is a condition to do the next function.
	/// \param mWork
	/// Needs a call for a void function.
	EventManager(std::function< bool(const sf::Event& event) > mCondition, std::function< void() > mWork) :
		mConditionNoEvent([](){return false;}),
		mCondition(mCondition),
		mWork(mWork),
		mEvent(sf::Event::KeyPressed),
		mCustomEvent(false)
	{}

	EventManager(std::function< bool() > mCondition, std::function< void() > mWork) :
		mConditionNoEvent(mCondition),
		mCondition([&](const sf::Event& event)-> bool { return mConditionNoEvent(); }),
		mWork(mWork),
		mEvent(sf::Event::KeyPressed),
		mCustomEvent(false)
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
		mConditionNoEvent([](){return false;}),
		mCondition([mKey](const sf::Event& event)->bool { return sf::Keyboard::isKeyPressed(mKey); }),
		mWork(mWork),
		mEvent(sf::Event::KeyPressed),
		mCustomEvent(false)
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
		mConditionNoEvent([](){return false;}),
		mCondition([mButton](const sf::Event& event)->bool { return sf::Mouse::isButtonPressed(mButton); }),
		mWork(mWork),
		mEvent(sf::Event::KeyPressed),
		mCustomEvent(false)
	{}

	/// \brief
	/// Extra constructor for keyboard key presses.
	/// \details
	/// This constructor returns what key is pressed on the keyboard.
	/// \param mKey
	/// Needs a key of the keyboard.
	/// \param mWork
	/// Needs a call for a void function.
	EventManager(
		sf::Keyboard::Key mKey, 
		std::function< void() > mWork,
		sf::Event::EventType eventType
	):
		mConditionNoEvent([](){return false;}),
		mCondition([=](const sf::Event& event = sf::Event())->bool { 
			return isEventAndKeyCorrect(mKey, event, eventType);
		}),
		mWork(mWork),
		mEvent(eventType),
		mCustomEvent(true)
	{}

	/// \brief
	/// Function for operator ().
	// void operator()() {
	// 	if (mCondition()) {
	// 		mWork();
	// 	}
	// }


	void operator()(const sf::Event& event = sf::Event()) {
		if(mCondition(event)) {
			mWork();
		}
	}
};

#endif
