#include "Text.hpp"



Text::Text(	const sf::Vector2f& position,
			const sf::Vector2f size,
			int screenNumber, std::string s, int fontSize, std::string fontFile) :
			EntityBase(position, size, screenNumber)
{
	mFont.loadFromFile(mFontPath + fontFile);
	mText.setFont(mFont);
	mText.setCharacterSize(fontSize);
	mText.setPosition(position);
	mText.setString(s);
}


Text::~Text() 
{
}

void Text::draw(ViewManager & window) {
	mText.setPosition(mPosition);
	window.selectDrawingScreen(mScreenNumber);
	window.draw(mText);
}

void Text::draw(sf::RenderWindow& window) {
	window.draw(mText);
}

void Text::update(const sf::Time& deltaTime) {

}

void Text::setString(std::string newString) {
	mText.setString(newString);
}

void Text::setColor(sf::Color newColor) {
	mText.setColor(newColor);
}

sf::FloatRect Text::getGlobalBounds() const {
	return mText.getGlobalBounds();
}