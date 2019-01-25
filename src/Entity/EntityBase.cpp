#include "EntityBase.hpp"
#include <iostream>

uint_least64_t EntityBase::nextId = 0;

void EntityBase::increaseNextId() {
	nextId++;
}

EntityBase::EntityBase(
	const sf::Vector2f& position, 
	const sf::Vector2f size, 
	int screenNumber,
	bool isSolid,
	bool isVisible
):
	mPosition(position), 
	mSize(size), 
	mScreenNumber(screenNumber),
	mIsSolid(isSolid),
	mIsVisible(isVisible)
{
	increaseNextId();
}

EntityBase::~EntityBase() {}

uint_least64_t EntityBase::getId() const {
	return id;
}

void EntityBase::backToStartId() {
	nextId = 0;
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

void EntityBase::setIsVisible(bool isVisible) {
	mIsVisible = isVisible;
}

bool EntityBase::getIsVisible() {
	return mIsVisible;
}

void EntityBase::setIsSolid(bool isSolid) {
	mIsSolid = isSolid;
}

bool EntityBase::getIsSolid() {
	return mIsSolid;
}

bool EntityBase::isFinished() {
	return false;
}

void EntityBase::drawIfVisible(sf::RenderWindow& window) {
	if(mIsVisible) {
		draw(window);
	}
}

void EntityBase::drawIfVisible(ViewManager& window) {
	if(mIsVisible) {
		draw(window);
	}
} 	