#pragma once
#include "EntityBase.hpp"
#include <string> 
class Text : public EntityBase {  
private:
	sf::Text mText;
	sf::Font mFont;

	std::string mFontPath = "../res/Fonts/";

public:
	Text(const sf::Vector2f& position,
		const sf::Vector2f size,
		int screenNumber, std::string s , int fontSize, std::string fontFile);
	virtual ~Text();

	virtual void draw(sf::RenderWindow& window) override;
	void draw(ViewManager& window) override;
	virtual void update(const sf::Time& deltaTime) override;
	void setString(std::string newString);
	void setColor(sf::Color newColor) override;

};

