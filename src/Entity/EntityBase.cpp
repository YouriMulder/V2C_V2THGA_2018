#include "EntityBase.hpp"

EntityBase::EntityBase(
	const sf::Vector2f& position, 
	const sf::Vector2f size, 
	int screenNumber 
):
	mPosition(position), mSize(size), mScreenNumber(screenNumber)
{}

EntityBase::~EntityBase() {

}

void EntityBase::move(float deltaX, float deltaY) {
	mPosition.x += deltaX;
	mPosition.y += deltaY;
}

void EntityBase::move(const sf::Vector2f& deltaPosition) {
	mPosition += deltaPosition;
}

void EntityBase::setPosition(float newX, float newY) {
	mPosition.x = newX;
	mPosition.y = newY;
}

void EntityBase::setPosition(const sf::Vector2f& newPosition) {
	mPosition = newPosition;
}

sf::Vector2f EntityBase::getPosition() const {
	return mPosition;
}

sf::Vector2f EntityBase::getNextPosition() const {
	return mPosition;
}

sf::Vector2f EntityBase::getSize() const {
	return mSize;
}

sf::FloatRect EntityBase::getGlobalBounds() const {
	return sf::FloatRect(mPosition, mSize);
}

void EntityBase::setScreenNumber(int newScreenNumber) {
	mScreenNumber = newScreenNumber;
}

int EntityBase::getScreenNumber() const {
	return mScreenNumber;
}
