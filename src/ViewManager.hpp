#ifndef VIEW_MANAGER_HPP
#define VIEW_MANAGER_HPP

#include <SFML/Graphics.hpp> 
#include <vector>
#include <array>
#include <memory>


struct screen {
	int number;
	sf::View view;
	bool selected = false;
};

class ViewManager{
private:
	/// \brief
	/// a reference to the main window.
	sf::RenderWindow & mMainWindow;

	int mAmountOfScreens;

	sf::Vector2f mOffset = sf::Vector2f(20.f, 20.f);

	/// \brief
	/// A vector that contains all the separate screens.
	/// \details
	/// This vector contains screens on the basis of the screen struct.
	/// The most screens at this point in time is 4.
	std::vector<screen> mScreens;

	std::array<sf::RectangleShape, 4> mBorders;
	
	/// \brief
	/// Function that converts a given sf::Vector2u to a sf::Vector2f.
	sf::Vector2f convertVector2u(const sf::Vector2u & input);
	

public:
	/// \brief
	/// Constructor for the ViewManager.
	/// \details
	/// Contructs the ViewManager on basis of the parameters.
	/// \param mainWindow
	/// The window on which de ViewManager is based.
	/// \param noOffScreens
	/// The number of screens that need to be made. Choices: 1,2,4.
	ViewManager(sf::RenderWindow & mainWindow, const int & noOfScreens);

	/// \brief
	/// Function to select a certain screen for moving.
	/// \details
	/// This function selects a screen note: multiple screens can be selected at once.
	/// \param screenNumber
	/// The number of the screen you want to select.
	void selectMoveScreen(const int & screenNumber);

	/// \brief
	/// Function to select a certain screen for drawing.
	/// \details
	/// Use this function before you draw to select where you want the object to be drawn.\n
	/// Giving 0 as a screen number selects the default view.
	/// \param screenNumber
	/// The number of the screen you want to select.
	void selectDrawingScreen(const int & screenNumber);

	/// \brief
	/// Function to reset the view to the default view.
	void resetDrawingScreen();

	/// \brief
	/// Function to draw an sf::Drawable.
	/// \details
	/// \param drawable
	/// The object that needs to de drawn.
	void draw(const sf::Drawable & drawable);

	/// \brief
	/// Function to draw vertices.
	/// \details
	/// \param vertices
	/// The vertices that need to be draw.
	/// \param vertexCount
	/// The amount of vertices.
	/// \param type
	/// The type of vertices for example sf::Lines.
	void draw(const sf::Vertex * vertices, std::size_t vertexCount, sf::PrimitiveType type);

	/// \brief
	/// Function to draw an sf::VertexBuffer.
	/// \details
	/// \param vertexBuffer
	/// The sf::VertexBuffer that needs to be drawn.
	void draw(const sf::VertexBuffer & vertexBuffer);

	/// \brief
	/// Function to draw a part of an sf::VertexBuffer.
	/// \details
	/// \param vertexBuffer
	/// The sf::VertexBuffer that needs to be drawn.
	/// \param firstVertex
	/// The vertex on which the drawing should start.
	/// \param vetexCount
	/// The amount of vertices.
	void draw(const sf::VertexBuffer &vertexBuffer, std::size_t firstVertex, std::size_t vertexCount);

	/// \brief
	/// Function to move view(s).
	/// \details
	/// This function moves all the selected views.
	/// \param offset
	/// The offset on basis of which the views need to be moved.
	void move(const sf::Vector2f & offset);
	
	/// \brief
	/// Adaptor function to display the window.
	void display();

	/// \brief
	/// Adaptor function to clear the window.
	void clear();

	/// \brief
	/// Adaptor function to close the window.
	void close();

	/// \brief
	/// Adaptor function to check if the window is open.
	/// \details
	/// \return bool
	/// Returns true if window is open.
	bool isOpen();

	/// \brief
	/// Adaptor function to poll events in the window.
	bool pollEvent(sf::Event & e);


	/// \brief
	/// Function to get the current position of the given view.
	/// \details
	/// \param screenNumber
	/// The number of the screen you want to get the position from.
	/// \return Return the position of the view.
	sf::Vector2f getViewPosition(const int & screenNumber) const;

	/// \brief
	/// Function to get the current size of the given view.
	/// \details
	/// \param screenNumber
	/// The number of the screen you want to get the size from.
	/// \return Return the size of the view.
	sf::Vector2f getViewSize(const int & screenNumber) const;

	/// \brief
	/// Function to get the current amount of screens present in ViewManager.
	/// \details
	/// \return Returns the current amount of screens.
	int getAmountOfScreens();

	/// \brief
	/// Function to change the amount of screens.
	/// \details
	/// This function changes the amount of screens dynamically.
	/// \param newAmount
	/// The new amount of screens that need to be created.
	void changeAmountOfScreens(int newAmount);

	/// \brief
	/// Function to create the borders around the screens.
	void createScreenBorders();

	/// \brief
	/// Function to set the bordercolor when selected.
	/// \details
	/// Bordor color is Red when selected.
	/// \param screenNumber
	/// The screen number of the screen the color needs to be set.
	void setBordorColor(int screenNumber);

	/// \brief
	/// Function to set the bordercolor when selected.
	/// \details
	/// Bordor color is White when deselected.
	/// \param screenNumber
	/// The screen number of the screen the color needs to be set.
	void resetBordorColor(int screenNumber);

	virtual ~ViewManager();
};

#endif /*VIEW_MANAGER_HPP*/
