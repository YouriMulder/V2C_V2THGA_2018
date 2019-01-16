#include "Collision.hpp"
#include "Entity/EntityBase.hpp"
#include <iostream>



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

void Collision::updateViewInfo() {
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


void Collision::checkCollisions() {
	checkScope();
	for (const auto & dynamicIndex : mNeedsCheckDynamic) {
		for (const auto & staticIndex : mNeedsCheckStatic) {
			if (mDynamicItems[dynamicIndex]->getGlobalBounds().intersects(mStaticItems[staticIndex]->getGlobalBounds())) {
				mDynamicItems[dynamicIndex]->handleCollision(mStaticItems[staticIndex]);
			}
		}
		for (const auto & dynamicIndex2 : mNeedsCheckDynamic) {
			if (mDynamicItems[dynamicIndex2] != mDynamicItems[dynamicIndex]) {
				if (mDynamicItems[dynamicIndex]->getGlobalBounds().intersects(mDynamicItems[dynamicIndex2]->getGlobalBounds())) {
					mDynamicItems[dynamicIndex]->handleCollision(mDynamicItems[dynamicIndex2]);
				}
			}
		}
	}
}