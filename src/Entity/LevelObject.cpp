#include "LevelObject.hpp"
#include <iostream>
LevelObject::LevelObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, bool repeated) :

	EntityBase(position, size, screenNumber)
{
	mTexture.loadFromFile(filename, picturepart);
	mTexture.setRepeated(repeated);
	mSprite.setTexture(mTexture);
	if(size.x > 0.0f && size.y > 0.0f) {
		mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size)));
	} else {
		matchSizeWithSprite();
	}
	mSprite.setPosition(position);
}

LevelObject::LevelObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, bool repeated) :

	EntityBase(position, size, screenNumber)
{
	mTexture.loadFromFile(filename);
	mTexture.setRepeated(repeated);
	mSprite.setTexture(mTexture);
	if(size.x > 0.0f && size.y > 0.0f) {
		mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size)));
	} else {
		matchSizeWithSprite();
	}
	mSprite.setPosition(position);
}

LevelObject::~LevelObject() {}

void LevelObject::matchSizeWithSprite() {
	EntityBase::setSize(
		sf::Vector2f(
			mSprite.getGlobalBounds().width,
			mSprite.getGlobalBounds().height
		)
	);
}

void LevelObject::resize(float width, float height) {
	mSize = { width, height };
	mSprite.setScale(width / mSprite.getGlobalBounds().width, height / mSprite.getGlobalBounds().height);
}

void LevelObject::resize(const sf::Vector2f& newSize) {
	mSize = newSize;
	mSprite.setScale(newSize.x / mSprite.getGlobalBounds().width, newSize.y / mSprite.getGlobalBounds().height);
}

void LevelObject::resizeWidth(float width) {
	mSize = { width, mSize.y };
	mSprite.setScale(width / mSprite.getGlobalBounds().width, 1);
}

void LevelObject::resizeHeight(float height) {
	mSize = { mSize.x, height };
	mSprite.setScale(1, height / mSprite.getGlobalBounds().height);
}

void LevelObject::setPosition(const sf::Vector2f& newPosition) {
	mSprite.setPosition(newPosition);
	EntityBase::setPosition(newPosition);
}


void LevelObject::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void LevelObject::draw(ViewManager& window) {
	window.selectDrawingScreen(mScreenNumber);
	window.draw(mSprite);
}

void LevelObject::update(const sf::Time& deltaTime) {
	mSprite.setPosition(mPosition);
}

sf::Vector2f LevelObject::getPosition() const {
	return mSprite.getPosition();
}

sf::FloatRect LevelObject::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}
