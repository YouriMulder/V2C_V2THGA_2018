#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>

/// \brief
/// This class manages the keyboard/mouse events.
class EventManager {
private:

	/// \brief
	/// The contion on which the event needs to be triggered.
	std::function< bool(const sf::Event& event) > mCondition;

	/// \brief
	/// The work that needs to be done when the condition is met.
	std::function< void() > mWork;

	/// \brief
	/// The Event used to trigger on a specific event.
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
	/// \param condition
	/// This function is a condition to do the next function.
	/// \param work
	/// Needs a call for a void function.
	EventManager(std::function< bool(const sf::Event& event) > condition, std::function< void() > work) :
		mCondition(Condition),
		mWork(work),
		mEvent(sf::Event::KeyPressed)
	{}

	/// \brief
	/// Constructor to use when no event is given in condition.
	/// \details
	/// Uses default event for lambda
	/// \param condition
	/// This function is a condition to do the next function.
	/// \param work
	/// Needs a call for a void function.
	EventManager(std::function< bool() > condition, std::function< void() > work) :
		mCondition([condition](const sf::Event& event = sf::Event())->bool { 
			return condition();
		}),
		mWork(work),
		mEvent(sf::Event::KeyPressed)
	{}

	/// \brief
	/// Extra constructor for keyboard key presses.
	/// \details
	/// This constructor returns what key is pressed on the keyboard.
	/// \param key
	/// Needs a key of the keyboard.
	/// \param work
	/// Needs a call for a void function.
	EventManager(sf::Keyboard::Key key, std::function< void() > work) :
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
	/// \param work
	/// Needs a call for a void function.
	EventManager(sf::Mouse::Button mButton, std::function< void() > work) :
		mCondition([mButton](const sf::Event& event)->bool { return sf::Mouse::isButtonPressed(mButton); }),
		mWork(work),
		mEvent(sf::Event::KeyPressed)
	{}

	/// \brief
	/// Extra constructor for keyboard key presses.
	/// \details
	/// This constructor returns what key is pressed on the keyboard.
	/// \param key
	/// Needs a key of the keyboard.
	/// \param work
	/// Needs a call for a void function.
	/// \param eventType
	/// The event type that is needed.
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
	void operator()(const sf::Event& event = sf::Event()) {
		if(mCondition(event)) {
			mWork();
		}
	}
};

#endif
