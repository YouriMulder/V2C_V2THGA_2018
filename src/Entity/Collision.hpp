#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <vector>
#include "../ViewManager.hpp"
#include "EntityBase.hpp"
#include "Side.hpp"

struct ViewInfo {
	/// \brief
	/// The number of this view.
	int viewNumber;

	/// \brief
	/// The position of the view.
	sf::Vector2f viewPosition;

	/// \brief
	/// The size of the view.
	sf::Vector2f viewSize;
};

struct CollisionBoxes {
	/// \brief
	/// Left collisionbox.
	sf::FloatRect leftBox;

	/// \brief
	/// Right collisionbox.
	sf::FloatRect rightBox;

	/// \brief
	/// Bottom collisionbox.
	sf::FloatRect bottomBox;

	/// \brief
	/// Top collisionbox.
	sf::FloatRect topBox;
};



class Collision {
private:
	/// \brief
	/// A reference to the viewManager.
	ViewManager & mViewManager;

	/// \brief
	/// A reference to the vector with static items.
	std::vector<std::unique_ptr<EntityBase>> & mStaticItems;

	/// \brief
	/// A reference to the vector with dynamic items.
	std::vector<std::unique_ptr<EntityBase>> & mDynamicItems;

	/// \brief
	/// The amount of screens in the window.
	int mAmountOfScreens;
	
	/// \brief
	/// This vector contains the indexes of the static items that need collision checking.
	std::vector<int> mNeedsCheckStatic;

	/// \brief
	/// This vector contains the indexes of the Dynamic items that need collision checking.
	std::vector<int> mNeedsCheckDynamic;

	/// \brief
	/// This vector contains the information of all the views.
	std::vector<ViewInfo> mViewInfos;

	/// \brief
	/// This function updates all the view information, such as position and size.
	void updateViewInfo();

	/// \brief
	/// This function check if items are in the view.
	/// \details
	/// If a item is out of view it will not be checked for collisions. \n
	/// By checking this first a lot of time is saved in further collision checking.
	void checkScope();
	
	/// \brief
	/// This function checks if the left top corner of a object is in view.
	/// \details
	/// \param currentItem
	/// The collisionbox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeLeftTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// This function checks if the right top corner of a object is in view.
	/// \details
	/// \param currentItem
	/// The collisionbox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeRightTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// This function checks if the left bottom corner of a object is in view.
	/// \details
	/// \param currentItem
	/// The collisionbox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeLeftBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// This function checks if the right bottom corner of a object is in view.
	/// \details
	/// \param currentItem
	/// The collisionbox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeRightBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// Function to print the ViewInfo struct.
	/// \details
	/// \param info
	/// The info that needs to be printed.
	void printViewInfo(ViewInfo info);

	/// \brief
	/// This function handeles the rest of the collision checking after a collision is found.
	/// \details
	/// When a collision is found on the main collision box this function checks where the collision occured.
	/// Possibilitys 
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
