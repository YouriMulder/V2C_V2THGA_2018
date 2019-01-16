#include "Platform.hpp"

Platform::Platform(const char * filename, sf::Vector2f position, sf::Vector2f size, sf::IntRect picturepart, bool repeated) {
	EntityBase::mPosition = position;
	EntityBase::mSize = size;
	mTexture.loadFromFile(filename, picturepart);
	mTexture.setRepeated(repeated);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size)));
	mSprite.setPosition(position);
}

Platform::Platform(const char * filename, sf::Vector2f position, sf::Vector2f size, bool repeated) {
	EntityBase::mPosition = position;
	EntityBase::mSize = size;
	mTexture.loadFromFile(filename);
	mTexture.setRepeated(repeated);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size)));
	mSprite.setPosition(position);
}

void Platform::resize(float width, float height) {
	EntityBase::mSize = { width, height };
	mSprite.setScale(width / mSprite.getGlobalBounds().width, height / mSprite.getGlobalBounds().height);
}

void Platform::resizeWidth(float width) {
	EntityBase::mSize = { width, EntityBase::mSize.y };
	mSprite.setScale(width / mSprite.getGlobalBounds().width, 1);
}

void Platform::resizeHeight(float height) {
	EntityBase::mSize = { EntityBase::mSize.x, height };
	mSprite.setScale(1, height / mSprite.getGlobalBounds().height);
}

void Platform::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Platform::update() {
	mSprite.setPosition(EntityBase::mPosition);
}

sf::FloatRect Platform::getGlobalBounds() {
	return mSprite.getGlobalBounds();
}