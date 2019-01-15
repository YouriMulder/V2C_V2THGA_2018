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
	sf::RenderWindow & mMainWindow;
	std::vector<screen> mScreens;
	sf::Vertex mLines[4];
	
	sf::Vector2f convertVector2u(sf::Vector2u & input);

public:
	ViewManager(sf::RenderWindow & mainWindow, const int & noOffScreens);

	void selectMoveScreen(const int & screenNumber);

	void selectDrawingScreen(const int & screenNumber);
	void resetDrawingScreen();

	void draw(const sf::Drawable & drawable);
	void draw(const sf::Vertex * vertices, std::size_t vertexCount, sf::PrimitiveType type);
	void draw(const sf::VertexBuffer & vertexBuffer);
	void draw(const sf::VertexBuffer &vertexBuffer, std::size_t firstVertex, std::size_t vertexCount);

	void move(const sf::Vector2f & offset);
	
	void display();
	void clear();
	void close();
	bool isOpen();
	bool pollEvent(sf::Event & e);

	void changeLineColor(const sf::Color & newColor);

	virtual ~ViewManager();
};

