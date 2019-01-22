#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <vector>
#include "../ViewManager.hpp"
#include "EntityBase.hpp"
#include "Side.hpp"

struct ViewInfo {
	int viewNumber;
	sf::Vector2f viewPosition;
	sf::Vector2f viewSize;
};

struct CollisionBoxes {
	sf::FloatRect leftBox;
	sf::FloatRect rightBox;
	sf::FloatRect bottomBox;
	sf::FloatRect topBox;
};



class Collision {
private:
	
	ViewManager & mViewManager;

	std::vector<std::unique_ptr<EntityBase>> & mStaticItems;
	std::vector<std::unique_ptr<EntityBase>> & mDynamicItems;

	int mAmountOfScreens;
	
	std::vector<int> mNeedsCheckStatic;
	std::vector<int> mNeedsCheckDynamic;

	std::vector<ViewInfo> mViewInfos;

	void updateViewInfo();

	void checkScope();
	
	bool checkScopeLeftTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);
	bool checkScopeRightTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);
	bool checkScopeLeftBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);
	bool checkScopeRightBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);
	void printViewInfo(ViewInfo info);

	void collisionHandler(
		std::unique_ptr<EntityBase> & object1,
		std::unique_ptr<EntityBase> & object2,
		std::vector<std::unique_ptr<EntityBase>*>& top, 
		std::vector<std::unique_ptr<EntityBase>*>& bottom, 
		std::vector<std::unique_ptr<EntityBase>*>& left, 
		std::vector<std::unique_ptr<EntityBase>*>& right,  
		CollisionSides& collisionSides
	);
	void reloadViewInfo();
	CollisionBoxes createCollisionBoxes(const sf::FloatRect & mainBox);

public:
	Collision(	ViewManager & viewManager, 
				std::vector<std::unique_ptr<EntityBase>> & staticItems, 
				std::vector<std::unique_ptr<EntityBase>> & dynamicItems);
	virtual ~Collision();
	void checkCollisions();
};

#endif /*COLLISION_HPP*/
