#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>


class EventManager {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	EventManager(
		std::function< bool() > condition,
		std::function< void() > work
	) : condition(condition),
		work(work)
	{}

	EventManager(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[key]()->bool { return sf::Keyboard::isKeyPressed(key); }
		),
		work(work)
	{}

	EventManager(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[button]()->bool { return sf::Mouse::isButtonPressed(button); }
		),
		work(work)
	{}

	void operator()() {
		if (condition()) {
			work();
		}
	}
};

#endif
