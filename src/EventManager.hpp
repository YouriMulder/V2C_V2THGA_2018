#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>

class EventManager {
private:
	std::function< bool(const sf::Event& event) > mCondition;
	std::function< void() > mWork;
	sf::Event::EventType mEvent;
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
	EventManager(std::function< bool(const sf::Event& event) > Condition, std::function< void() > Work) :
		mCondition(Condition),
		mWork(Work),
		mEvent(sf::Event::KeyPressed)
	{}

	EventManager(std::function< bool() > condition, std::function< void() > Work) :
		mCondition([condition](const sf::Event& event = sf::Event())->bool { 
			return condition();
		}),
		mWork(Work),
		mEvent(sf::Event::KeyPressed)
	{}

	/// \brief
	/// Extra constructor for keyboard key presses.
	/// \details
	/// This constructor returns what key is pressed on the keyboard.
	/// \param mKey
	/// Needs a key of the keyboard.
	/// \param mWork
	/// Needs a call for a void function.
	EventManager(sf::Keyboard::Key key, std::function< void() > Work) :
		mCondition([key](const sf::Event& event)->bool { return sf::Keyboard::isKeyPressed(key); }),
		mWork(Work),
		mEvent(sf::Event::KeyPressed)
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
		mCondition([mButton](const sf::Event& event)->bool { return sf::Mouse::isButtonPressed(mButton); }),
		mWork(mWork),
		mEvent(sf::Event::KeyPressed)
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
		sf::Keyboard::Key key, 
		std::function< void() > work,
		sf::Event::EventType eventType
	):
		mCondition([key, eventType, this](const sf::Event& event = sf::Event())->bool { 
			return isEventAndKeyCorrect(key, event, eventType);
		}),
		mWork(work),
		mEvent(eventType)
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
