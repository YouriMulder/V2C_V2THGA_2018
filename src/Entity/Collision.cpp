#include "Collision.hpp"
#include "EntityBase.hpp"
#include <iostream>
#include <memory>
#include <vector>



Collision::Collision(	ViewManager & viewManager,
						std::vector<std::unique_ptr<EntityBase>> & staticItems,
						std::vector<std::unique_ptr<EntityBase>> & dynamicItems):
	mViewManager(viewManager),
	mStaticItems(staticItems),
	mDynamicItems(dynamicItems){
	mAmountOfScreens = mViewManager.getAmountOfScreens();
	for (int i = 1;i <= mAmountOfScreens;i++) {
		ViewInfo newViewInfo{ i, mViewManager.getViewPosition(i), mViewManager.getViewSize(i) };
		mViewInfos.push_back(newViewInfo);
	}
}

Collision::~Collision()
{
}


void Collision::printViewInfo(ViewInfo info) {

	std::cout	<< "viewnumber: " << info.viewNumber << std::endl
				<< "position: (" << info.viewPosition.x << "," << info.viewPosition.y << ")" << std::endl
				<< "size: (" << info.viewSize.x << "," << info.viewSize.y << ")" << std::endl;

}

void Collision::reloadViewInfo() {
	mViewInfos.clear();
	for (int i = 1;i <= mAmountOfScreens;i++) {
		ViewInfo newViewInfo{ i, mViewManager.getViewPosition(i), mViewManager.getViewSize(i) };
		mViewInfos.push_back(newViewInfo);
	}
}

void Collision::updateViewInfo() {
	mAmountOfScreens = mViewManager.getAmountOfScreens();
	if (static_cast<unsigned int>(mAmountOfScreens) > mViewInfos.size()) {
		reloadViewInfo();
	}
	for (auto & info : mViewInfos) {
		info.viewPosition = mViewManager.getViewPosition(info.viewNumber);
	}
}

bool Collision::checkScopeLeftTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo) {
	return ((currentItem.left >= currentViewInfo.viewPosition.x) ||
			(currentItem.top >= currentViewInfo.viewPosition.y) ||
			(currentItem.left <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) ||
			(currentItem.top <= (currentViewInfo.viewPosition.y + currentViewInfo.viewSize.y)));
	
}

bool Collision::checkScopeRightTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo) {
	return ((currentItem.left + currentItem.width >= currentViewInfo.viewPosition.x )||
			(currentItem.top >= currentViewInfo.viewPosition.y )||
			((currentItem.left + currentItem.width) <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) ||
			(currentItem.top <= (currentViewInfo.viewPosition.y + currentViewInfo.viewSize.y)));
}

bool Collision::checkScopeLeftBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo) {
	return ((currentItem.left >= currentViewInfo.viewPosition.x )||
			((currentItem.top + currentItem.height) >= currentViewInfo.viewPosition.y) ||
			(currentItem.left <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) ||
			((currentItem.top + currentItem.height) <= (currentViewInfo.viewPosition.y + currentViewInfo.viewSize.y)));
}

bool Collision::checkScopeRightBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo) {
	return (((currentItem.left + currentItem.left) >= currentViewInfo.viewPosition.x) ||
			((currentItem.top + currentItem.height) >= currentViewInfo.viewPosition.y )||
			((currentItem.left + currentItem.width) <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) ||
			((currentItem.top + currentItem.height) <= (currentViewInfo.viewPosition.y + currentViewInfo.viewSize.y)));
}



void Collision::checkScope() {
	updateViewInfo();
	mNeedsCheckStatic.clear();
	mNeedsCheckDynamic.clear();

	for (unsigned int i = 0; i < mStaticItems.size(); i++){
		sf::FloatRect currentItem = mStaticItems[i]->getGlobalBounds();
		ViewInfo currentViewInfo = mViewInfos[mStaticItems[i]->getScreenNumber() - 1];

		if (checkScopeLeftBottom(currentItem, currentViewInfo) ||
			checkScopeLeftTop(currentItem, currentViewInfo) ||
			checkScopeRightBottom(currentItem, currentViewInfo) ||
			checkScopeRightTop(currentItem, currentViewInfo)) {
			mNeedsCheckStatic.push_back(static_cast<int>(i));
		}
	}

	for (unsigned int i = 0; i < mDynamicItems.size(); i++) {
		sf::FloatRect currentItem = mDynamicItems[i]->getGlobalBounds();
		ViewInfo currentViewInfo = mViewInfos[mDynamicItems[i]->getScreenNumber() - 1];

		if (checkScopeLeftBottom(currentItem, currentViewInfo) ||
			checkScopeLeftTop(currentItem, currentViewInfo) ||
			checkScopeRightBottom(currentItem, currentViewInfo) ||
			checkScopeRightTop(currentItem, currentViewInfo)) {
			mNeedsCheckDynamic.push_back(static_cast<int>(i));
		}
	}
}

// -1 and -2 to fix the bottom collision otherwise the left and right will be detected first.
CollisionBoxes Collision::createCollisionBoxes(const sf::FloatRect & mainBox) {
	int pixelOffset = 2;
	return CollisionBoxes{	sf::FloatRect(mainBox.left,mainBox.top - pixelOffset , 1, mainBox.height -pixelOffset), //Left
							sf::FloatRect(mainBox.left + mainBox.width, mainBox.top - pixelOffset, 1, mainBox.height -pixelOffset), //Right
							sf::FloatRect(mainBox.left + pixelOffset, mainBox.top, mainBox.width-pixelOffset, 1),//Top
							sf::FloatRect(mainBox.left+ pixelOffset, mainBox.top + mainBox.height, mainBox.width-pixelOffset, 1) }; //Bottom
}

void Collision::collisionHandler(std::unique_ptr<EntityBase> & object1, 
	std::unique_ptr<EntityBase> & object2, 
	std::vector<std::unique_ptr<EntityBase>*>& top, 
	std::vector<std::unique_ptr<EntityBase>*>& bottom, 
	std::vector<std::unique_ptr<EntityBase>*>& left, 
	std::vector<std::unique_ptr<EntityBase>*>& right, 
	CollisionSides& collisionSides
	
) {
	CollisionBoxes boxes1 = createCollisionBoxes(object1->getGlobalBounds());
	sf::FloatRect box2 = object2->getGlobalBounds();
	if (boxes1.topBox.intersects(box2)) {
		collisionSides.top = true;
		top.push_back(&object2);
	}
	if (boxes1.bottomBox.intersects(box2)) {
		collisionSides.bottom = true;
		bottom.push_back(&object2);
	} 
	if (boxes1.leftBox.intersects(box2)) {
		collisionSides.left = true;
		left.push_back(&object2);
	} 
	if (boxes1.rightBox.intersects(box2)) {
		collisionSides.right = true;
		right.push_back(&object2);	
	} 
}


void Collision::checkCollisions() {
	checkScope();
	for (const auto & dynamicIndex : mNeedsCheckDynamic) {
		bool collisionFound = false;		
		std::vector<std::unique_ptr<EntityBase>*> top;
		std::vector<std::unique_ptr<EntityBase>*> bottom;
		std::vector<std::unique_ptr<EntityBase>*> left;
		std::vector<std::unique_ptr<EntityBase>*> right;
		
		CollisionSides collisionSides;
		

		std::unique_ptr<EntityBase> & currentDynamicItem = mDynamicItems[dynamicIndex];
		for (const auto & staticIndex : mNeedsCheckStatic) {
			std::unique_ptr<EntityBase> & currentStaticItem = mStaticItems[staticIndex];
			if (currentDynamicItem->getScreenNumber() == currentStaticItem->getScreenNumber()) {
				if (currentDynamicItem->getGlobalBounds().intersects(currentStaticItem->getGlobalBounds())) { //collision detected
					collisionHandler(currentDynamicItem, currentStaticItem, top, bottom, left, right, collisionSides);
					collisionFound = true;
				}
			}
		}

		for (const auto & dynamicIndex2 : mNeedsCheckDynamic) {
			std::unique_ptr<EntityBase> & currentDynamicItem2 = mDynamicItems[dynamicIndex2];
			if (currentDynamicItem->getScreenNumber() == currentDynamicItem2->getScreenNumber()){
				if (currentDynamicItem != currentDynamicItem2) {
					if (currentDynamicItem->getGlobalBounds().intersects(currentDynamicItem2->getGlobalBounds())) {//collision detected
						collisionHandler(currentDynamicItem, currentDynamicItem2, top, bottom, left, right, collisionSides);
						collisionFound = true;
					}
				}
			}
		}

		if(collisionFound) {
			currentDynamicItem->handleCollision(top, bottom, left, right, collisionSides);
		} else {
			currentDynamicItem->handleNoCollision();
		}
	}
}