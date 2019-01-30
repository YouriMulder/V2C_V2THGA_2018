#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/System/Clock.hpp>

/// \brief
/// This is the timer class.
/// \details
/// This class is used to keep track of time between events.
class Timer {
private:
	/// /brief
	/// This is the clock to keep track. 
	/// This clock starts when Timer is set.
	sf::Clock mTimer;
	
	/// \brief
	/// The amount of time the Timer will last.
	sf::Time mMaxTime;

	/// \brief
	/// Whether or not the Timer is set.
	bool mIsSet;

public:
	/// \brief
	/// The constructor of the Timer class.
	Timer();
	virtual ~Timer();

	/// \brief
	/// This method is used to set the timer to a default value.
	void init();
	/// \brief
	/// This method sets the timer and start counting down.
	/// \param countDownTime
	/// The amount of time the timer should last.
	void set(const sf::Time& countDownTime);

	/// \brief
	/// This method returns whether the Timer is set or not.
	/// \return
	/// A bool containing whether the Timer is set or not.
	bool isSet() const;

	/// \brief
	/// This method retuns whether the Timer is expired or not.
	/// \return
	/// A bool containing whether the Timer is expired or not.
	bool isExpired();
};

#endif /* TIMER_HPP */