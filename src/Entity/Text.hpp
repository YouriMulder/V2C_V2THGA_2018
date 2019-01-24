#ifndef TEXT_HPP 
#define TEXT_HPP
#include <string> 

#include "EntityBase.hpp"
#include "../ViewManager.hpp"

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
	virtual void draw(ViewManager& window) override;
	virtual void update(const sf::Time& deltaTime) override;
	void setString(const std::string& newString);
	virtual void setColor(const sf::Color& newColor) override;
	sf::FloatRect getGlobalBounds() const override;

};

#endif /*TEXT_HPP */

