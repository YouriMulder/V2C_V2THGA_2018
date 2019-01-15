#include <SFML/Graphics.hpp> 
#include <vector>

struct screen {
	int number;
	bool selected = false;
	sf::View view;
};

class ViewManager
{
private:
	///
	/// \brief
	/// a reference to the main window
	sf::RenderWindow & mMainWindow;

	/// \brief
	/// A vector that contains all the separate screens
	/// \details
	/// This vector contains screens on the basis of the screen struct.
	/// The most screens at this point in time is 4
	std::vector<screen> mScreens;

	/// \brief
	/// A vertex that is used for lines between the screens
	sf::Vertex mLines[4];
	
	/// \brief
	/// Function that converts a given sf::Vector2u to a Vector2f
	sf::Vector2f convertVector2u(sf::Vector2u & input);

public:
	/// \brief
	/// Constructor for the ViewManager
	/// \details
	/// contructs the ViewManager on basis of the parameters
	/// \param mainWindow
	/// The window on wich de ViewManager is based
	/// \param noOffScreens
	/// The number of screens that need to be made choices: 1,2,4
	ViewManager(sf::RenderWindow & mainWindow, const int & noOffScreens);

	/// \brief
	/// Function to select a certain screen for moving
	/// \details
	/// This function selects a scren note: multiple screens can be selected at once
	/// \param screenNumber
	/// The number of the screen you want to select.
	void selectMoveScreen(const int & screenNumber);

	/// \brief
	/// Function to select a certain screen for drawing
	/// \details
	/// Use this function before you draw to select where you want the object to be draw.\n
	/// Giving 0 as a screen number selects the default view.
	/// \param screenNumber
	/// The number of the screen you want to select.
	void selectDrawingScreen(const int & screenNumber);

	/// \brief
	/// Fucntion to reset the view to the default view
	void resetDrawingScreen();

	/// \brief
	/// Function to draw an sf::Drawable
	/// \details
	/// \param drawable
	/// The object that needs to de drawn
	void draw(const sf::Drawable & drawable);

	/// \brief
	/// Function to draw vertices
	/// \details
	/// \param vertices
	/// The vertices that needs to be draw
	/// \param vetexCount
	/// The amount of vertices 
	/// \param type
	/// The type of vertices for example sf::Lines
	void draw(const sf::Vertex * vertices, std::size_t vertexCount, sf::PrimitiveType type);

	/// \brief
	/// Function to draw an sf::VertexBuffer
	/// \details
	/// \param vertexBuffer
	/// The sf::VertexBuffer that needs to be drawn
	void draw(const sf::VertexBuffer & vertexBuffer);

	/// \brief
	/// Function to draw a part of an sf::VertexBuffer
	/// \details
	/// \param vertexBuffer
	/// The sf::VertexBuffer that needs to be drawn
	/// \param firstVertex
	/// The vertex on wich the drawing should start
	/// \param vetexCount
	/// The amount of vertices 
	void draw(const sf::VertexBuffer &vertexBuffer, std::size_t firstVertex, std::size_t vertexCount);

	/// \brief
	/// Function to move view(s)
	/// \details
	/// This function moves all the selected views
	/// \param offset
	/// The offset on basis of which the views need to be moved
	void move(const sf::Vector2f & offset);
	
	/// \brief
	/// Adaptor function to display the window
	void display();

	/// \brief
	/// Adaptor function to clear the window
	void clear();

	/// \brief
	/// Adaptor function to close the window
	void close();

	/// \brief
	/// Adaptor function to check if the window isOpen
	/// \details
	/// \return bool
	/// returns true if window is open
	bool isOpen();

	/// \brief
	/// Adaptor function to poll events in the window
	bool pollEvent(sf::Event & e);

	/// \brief
	/// Function to change the color of the lines that seperate the screens
	/// \details
	/// This function changes the color of the lines to the new color
	/// \param newColor
	/// The new color the lines need to become
	void changeLineColor(const sf::Color & newColor);

	virtual ~ViewManager();
};

