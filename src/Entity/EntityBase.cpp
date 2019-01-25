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

bool EntityBase::isVisible() const {
	return mIsVisible;
}

void EntityBase::setIsSolid(bool isSolid) {
	mIsSolid = isSolid;
}

bool EntityBase::isSolid() const {
	return mIsSolid;
}

bool EntityBase::isFinished() const {
	return false;
}

void EntityBase::removeNonSolid(
	std::vector<std::unique_ptr<EntityBase>*>& top, 
	std::vector<std::unique_ptr<EntityBase>*>& bottom, 
	std::vector<std::unique_ptr<EntityBase>*>& left, 
	std::vector<std::unique_ptr<EntityBase>*>& right, 
	CollisionSides& hitSides
) const {
	for(size_t i = 0; i < top.size(); ++i) {
		if(!(*top[i])->isSolid()) {
			top.erase(top.begin() + i);
		}
	}

	for(size_t i = 0; i < bottom.size(); ++i) {
		if(!(*bottom[i])->isSolid()) {	
			bottom.erase(bottom.begin() + i);
		}
	}

	for(size_t i = 0; i < left.size(); ++i) {
		if(!(*left[i])->isSolid()) {
			left.erase(left.begin() + i);
		}
	}

	for(size_t i = 0; i < right.size(); ++i) {
		if(!(*right[i])->isSolid()) {
			right.erase(right.begin() + i);
		}
	}

	hitSides.top 	= top.size();
	hitSides.bottom = bottom.size();
	hitSides.left 	= left.size();
	hitSides.right 	= right.size();

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