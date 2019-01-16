#include "Platform.hpp"

Platform::Platform(const char * filename, const sf::Vector2f& position, const sf::Vector2f& size, const sf::IntRect& picturepart, int screenNumber, bool repeated) :
	EntityBase(position, size, screenNumber)
{
	mTexture.loadFromFile(filename, picturepart);
	mTexture.setRepeated(repeated);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size)));
	mSprite.setPosition(position);
}

Platform::Platform(const char * filename, const sf::Vector2f& position, const sf::Vector2f& size, int screenNumber, bool repeated) :
	EntityBase(position, size, screenNumber)
{
	mTexture.loadFromFile(filename);
	mTexture.setRepeated(repeated);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size)));
	mSprite.setPosition(position);
}

void Platform::resize(float width, float height) {
	mSize = { width, height };
	mSprite.setScale(width / mSprite.getGlobalBounds().width, height / mSprite.getGlobalBounds().height);
}

void Platform::resize(const sf::Vector2f& newSize) {
	mSize = newSize;
	mSprite.setScale(newSize.x / mSprite.getGlobalBounds().width, newSize.y / mSprite.getGlobalBounds().height);
}

void Platform::resizeWidth(float width) {
	mSize = { width, mSize.y };
	mSprite.setScale(width / mSprite.getGlobalBounds().width, 1);
}

void Platform::resizeHeight(float height) {
	mSize = { mSize.x, height };
	mSprite.setScale(1, height / mSprite.getGlobalBounds().height);
}

void Platform::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Platform::draw(ViewManager& window) {
	window.selectDrawingScreen(mScreenNumber);
	window.draw(mSprite);
}

void Platform::update() {
	mSprite.setPosition(mPosition);
}

sf::FloatRect Platform::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}