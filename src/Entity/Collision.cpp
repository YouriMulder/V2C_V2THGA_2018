#include "Collision.hpp"
#include "EntityBase.hpp"
#include <iostream>
#include <memory>



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
		printViewInfo(newViewInfo);
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
	return ((currentItem.left >= currentViewInfo.viewPosition.x) &&
			(currentItem.top >= currentViewInfo.viewPosition.y) &&
			(currentItem.left <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) &&
			(currentItem.top <= (currentViewInfo.viewPosition.y + currentViewInfo.viewSize.y)));
	
}

bool Collision::checkScopeRightTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo) {
	return ((currentItem.left + currentItem.width >= currentViewInfo.viewPosition.x )&&
			(currentItem.top >= currentViewInfo.viewPosition.y )&&
			((currentItem.left + currentItem.width) <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) &&
			(currentItem.top <= (currentViewInfo.viewPosition.y + currentViewInfo.viewSize.y)));
}

bool Collision::checkScopeLeftBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo) {
	return ((currentItem.left >= currentViewInfo.viewPosition.x )&&
			((currentItem.top + currentItem.height) >= currentViewInfo.viewPosition.y) &&
			(currentItem.left <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) &&
			((currentItem.top + currentItem.height) <= (currentViewInfo.viewPosition.y + currentViewInfo.viewSize.y)));
}

bool Collision::checkScopeRightBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo) {
	return (((currentItem.left + currentItem.left) >= currentViewInfo.viewPosition.x) &&
			((currentItem.top + currentItem.height) >= currentViewInfo.viewPosition.y )&&
			((currentItem.left + currentItem.width) <= (currentViewInfo.viewPosition.x + currentViewInfo.viewSize.x)) &&
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

CollisionBoxes Collision::createCollisionBoxes(const sf::FloatRect & mainBox) {
	return CollisionBoxes{	sf::FloatRect(mainBox.left,mainBox.top -1 , 1, mainBox.height -2), //Left
							sf::FloatRect(mainBox.left + mainBox.width, mainBox.top -1, 1, mainBox.height -2), //Right
							sf::FloatRect(mainBox.left, mainBox.top, mainBox.width, 1),//Top
							sf::FloatRect(mainBox.left, mainBox.top + mainBox.height, mainBox.width, 1) }; //Bottom
}

void Collision::collisionDetected(std::unique_ptr<EntityBase> & object1, std::unique_ptr<EntityBase> & object2) {
	CollisionBoxes boxes1 = createCollisionBoxes(object1->getGlobalBounds());
	sf::FloatRect box2 = object2->getGlobalBounds();
	Side output;
	if (boxes1.leftBox.intersects(box2)) {
		output = Side::Left;
	} else if (boxes1.rightBox.intersects(box2)) {
		output = Side::Right;
	} else if (boxes1.topBox.intersects(box2)) {
		output = Side::Top;
	} else if (boxes1.bottomBox.intersects(box2)) {
		output = Side::Bottom;
	} else {
		output = Side::NoSideDetected;
	}

	object1->handleCollision(object2,output);
}


void Collision::checkCollisions() {
	checkScope();
	for (const auto & dynamicIndex : mNeedsCheckDynamic) {
		std::unique_ptr<EntityBase> & currentDynamicItem = mDynamicItems[dynamicIndex];
		for (const auto & staticIndex : mNeedsCheckStatic) {
			std::unique_ptr<EntityBase> & currentStaticItem = mStaticItems[staticIndex];
			if (currentDynamicItem->getGlobalBounds().intersects(currentStaticItem->getGlobalBounds())) { //collision detected
				collisionDetected(currentDynamicItem, currentStaticItem);
			}
		}
		for (const auto & dynamicIndex2 : mNeedsCheckDynamic) {
			std::unique_ptr<EntityBase> & currentDynamicItem2 = mDynamicItems[dynamicIndex2];
			if (currentDynamicItem != currentDynamicItem2) {
				if (currentDynamicItem->getGlobalBounds().intersects(currentDynamicItem2->getGlobalBounds())) {//collision detected
					collisionDetected(currentDynamicItem, currentDynamicItem2);
				}
			}
		}
	}
}