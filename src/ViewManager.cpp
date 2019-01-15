#include "ViewManager.hpp"
#include <iostream>


sf::Vector2f ViewManager::convertVector2u(sf::Vector2u & input) {
	return sf::Vector2f((float)input.x, (float)input.y);
}


ViewManager::ViewManager(sf::RenderWindow & mainWindow, const int & noOffScreens):
	mMainWindow(mainWindow)
{
	mMainWindow.setFramerateLimit(60);
	mScreens.reserve(4);
	sf::Vector2f mainWindowSize = convertVector2u(mainWindow.getSize());

	if (noOffScreens == 1) {
		screen newScreen;
		newScreen.number = 1;
		newScreen.view = mainWindow.getDefaultView();
		mScreens.push_back(newScreen);
		resetDrawingScreen();
	} else if (noOffScreens == 2) {
		screen newScreen1;
		screen newScreen2;
		newScreen1.number = 1;
		newScreen2.number = 2;

		sf::View view1 = sf::View(sf::FloatRect(0.0,0.0,mainWindowSize.x,mainWindowSize.y/2));
		view1.setViewport(sf::FloatRect(0, 0, 1, 0.5));
		sf::View view2 = sf::View(sf::FloatRect(0.0, 0.0, mainWindowSize.x, mainWindowSize.y));
		view2.setViewport(sf::FloatRect(0, 0.5, 1, 1));
		newScreen1.view = view1;
		newScreen2.view = view2;
		mScreens.push_back(newScreen1);
		mScreens.push_back(newScreen2);

		mLines[0].position = sf::Vector2f(0.0, mainWindowSize.y / 2);
		mLines[1].position = sf::Vector2f(mainWindowSize.x, mainWindowSize.y / 2);
	} else if (noOffScreens == 4) {
		screen newScreen1;
		screen newScreen2;
		screen newScreen3;
		screen newScreen4;
		newScreen1.number = 1;
		newScreen2.number = 2;
		newScreen3.number = 3;
		newScreen4.number = 4;

		sf::View view1 = sf::View(sf::FloatRect(0.0, 0.0, mainWindowSize.x/2, mainWindowSize.y / 2));
		view1.setViewport(sf::FloatRect(0, 0, 0.5, 0.5));
		sf::View view2 = sf::View(sf::FloatRect(0.0, 0.0, mainWindowSize.x, mainWindowSize.y / 2));
		view2.setViewport(sf::FloatRect(0.5,0, 1, 0.5));
		sf::View view3 = sf::View(sf::FloatRect(0.0, 0.0, mainWindowSize.x/2, mainWindowSize.y ));
		view3.setViewport(sf::FloatRect(0, 0.5, 0.5, 1));
		sf::View view4 = sf::View(sf::FloatRect(0.0, 0.0, mainWindowSize.x, mainWindowSize.y));
		view4.setViewport(sf::FloatRect(0.5, 0.5, 1, 1));

		newScreen1.view = view1;
		newScreen2.view = view2;
		newScreen3.view = view3;
		newScreen4.view = view4;

		mScreens.push_back(newScreen1);
		mScreens.push_back(newScreen2);
		mScreens.push_back(newScreen3);
		mScreens.push_back(newScreen4);

		mLines[0].position = sf::Vector2f(mainWindowSize.x / 2, 0.0);
		mLines[1].position = sf::Vector2f(mainWindowSize.x / 2, mainWindowSize.y);
		mLines[2].position = sf::Vector2f(0.0, mainWindowSize.y / 2);
		mLines[3].position = sf::Vector2f(mainWindowSize.x, mainWindowSize.y / 2);
	} else {
		std::cout << "not a correct amount of screens" << noOffScreens << std::endl;
	}
}


ViewManager::~ViewManager()
{
}

void ViewManager::selectMoveScreen(const int & screenNumber) {
	for (auto & s : mScreens) {
		if (s.number == screenNumber) {
			s.selected = !s.selected;
		}
	}
}


void ViewManager::selectDrawingScreen(const int & screenNumber) {
	for (auto & s : mScreens) {
		if (s.number == screenNumber) {
			mMainWindow.setView(s.view);
		}
	}
}

void ViewManager::resetDrawingScreen() {
	mMainWindow.setView(mMainWindow.getDefaultView());
}

void ViewManager::draw(const sf::Drawable & drawable) {
	mMainWindow.draw(drawable);
}

void ViewManager::draw(const sf::Vertex * vertices, std::size_t vertexCount, sf::PrimitiveType type) {
	mMainWindow.draw(vertices, vertexCount, type);
}

void ViewManager::draw(const sf::VertexBuffer & vertexBuffer) {
	mMainWindow.draw(vertexBuffer);
}

void ViewManager::draw(const sf::VertexBuffer &vertexBuffer, std::size_t firstVertex, std::size_t vertexCount) {
	mMainWindow.draw(vertexBuffer, firstVertex, vertexCount);
}

void ViewManager::move(const sf::Vector2f & offset) {
	for (auto & s : mScreens) {
		if (s.selected == true) {
			s.view.move(offset);
		}
	}
}

void ViewManager::display() {
	resetDrawingScreen();
	mMainWindow.draw(mLines, 4, sf::Lines);
	mMainWindow.display();
}

void ViewManager::clear() {
	mMainWindow.clear();
}

void ViewManager::close() {
	mMainWindow.close(); 
}

bool ViewManager::isOpen() {
	return mMainWindow.isOpen();
}

bool ViewManager::pollEvent(sf::Event & e) {
	return mMainWindow.pollEvent(e);
}

void ViewManager::changeLineColor(const sf::Color & newColor) {
	for (auto & line : mLines) {
		line.color = newColor;
	}
}