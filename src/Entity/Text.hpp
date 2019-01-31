#ifndef TEXT_HPP 
#define TEXT_HPP
#include <string> 

#include "EntityBase.hpp"
#include "../ViewManager.hpp"

/// \brief
/// Class for displaying text in a renderwindow.
class Text : public EntityBase {  
private:

	/// \brief
	/// The text object.
	sf::Text mText;
	
	/// \brief
	/// The font for the text.
	sf::Font mFont;

	/// \brief
	/// The path to all the fonts.
	std::string mFontPath = "../res/Fonts/";

public:
	/// \brief
	/// Constructor for Text object.
	/// \param position
	/// The wanted position of the text.
	/// \param size
	/// The size of the text object. (usualy 0,0)
	/// \param screenNumber
	/// The screen on which the Text is drawn.
	/// \param s
	/// The string of the text.
	/// \param fontSize
	/// The font size in px.
	/// \param fontFile
	/// The name of the ttf file for the font.
	Text(const sf::Vector2f& position,
		const sf::Vector2f size,
		int screenNumber, std::string s , int fontSize, std::string fontFile);
	virtual ~Text();

	/// \brief
	/// Method to draw the text to a render window.
	virtual void draw(sf::RenderWindow& window) override;
	
	/// \brief
	/// Method to draw the text to a ViewManager.
	virtual void draw(ViewManager& window) override;
	
	/// \brief
	/// Empty method. But needs to be overwritten.
	virtual void update(const sf::Time& deltaTime) override;
	
	/// \brief
	/// Method to set a new string for the text.
	/// \details
	/// \param newString
	/// The string you want to set to the text.
	void setString(const std::string& newString);
	
	/// \brief
	/// Method to change the color of the text.
	/// \param newColor
	/// The color you want 
	virtual void setColor(const sf::Color& newColor) override;
	
	/// \brief
	/// Method to get the global bound of the text object.
	sf::FloatRect getGlobalBounds() const override;

};

#endif /*TEXT_HPP */

