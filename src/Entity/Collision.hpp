#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <vector>
#include "../ViewManager.hpp"
#include "EntityBase.hpp"
#include "Side.hpp"

/// \brief
/// Struct containing information about views
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

/// \brief
/// Struct containing 4 hitboxes 1 for each side
struct CollisionBoxes {
	/// \brief
	/// Left collisionBox
	sf::FloatRect leftBox;

	/// \brief
	/// Right collisionBox
	sf::FloatRect rightBox;

	/// \brief
	/// Bottom collisionBox
	sf::FloatRect bottomBox;

	/// \brief
	/// Top collisionBox
	sf::FloatRect topBox;
};


/// \brief
/// Class to handle collisionchecking.
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
	/// This method updates all the view information, such as position and size.
	void updateViewInfo();

	/// \brief
	/// This method checks if items are in the view.
	/// \details
	/// If a item is out of view it will not be checked for collisions. \n
	/// By checking this first a lot of time is saved in further collision checking.
	void checkScope();
	
	/// \brief
	/// This method checks if the left top corner of a object is in view.
	/// \details
	/// \param currentItem
	/// The collisionBox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeLeftTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// This method checks if the right top corner of an object is in view.
	/// \details
	/// \param currentItem
	/// The collisionBox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeRightTop(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// This method checks if the left bottom corner of a object is in view.
	/// \details
	/// \param currentItem
	/// The collisionbox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeLeftBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// This method checks if the right bottom corner of a object is in view.
	/// \details
	/// \param currentItem
	/// The collisionbox of the current item that needs to be checked.
	/// \param currentViewinfo 
	/// The information of the view the object is in.
	bool checkScopeRightBottom(const sf::FloatRect & currentItem, const ViewInfo & currentViewInfo);

	/// \brief
	/// Method to print the ViewInfo struct.
	/// \details
	/// \param info
	/// The info that needs to be printed.
	void printViewInfo(ViewInfo info);

	/// \brief
	/// This method handles the rest of the collision checking after a collision is found.
	/// \details
	/// When a collision is found on the main collisionBox this function checks where the collision occured.
	/// Possibilities are: Left, Right, Top and Bottom. \n
	/// After checking which side the collision is detected the object is added to the corresponding vector.
	/// The collisionSides struct is updated with a true on the corresponding side.
	/// \param object1
	/// The first object to check the collision width.
	/// \param object2
	/// The second object to check the collision width.
	/// \param top
	/// Vector with top collisioned objects.
	/// \param bottom
	/// Vector with bottom collisioned objects.
	/// \param left
	/// Vector with left collisioned objects.
	/// \param right
	/// Vector with right collisioned objects.
	/// \param collisionSides
	/// The collisionSides struct
	void collisionHandler(
		std::unique_ptr<EntityBase> & object1,
		std::unique_ptr<EntityBase> & object2,
		std::vector<std::unique_ptr<EntityBase>*>& top, 
		std::vector<std::unique_ptr<EntityBase>*>& bottom, 
		std::vector<std::unique_ptr<EntityBase>*>& left, 
		std::vector<std::unique_ptr<EntityBase>*>& right,  
		CollisionSides& collisionSides
	);

	/// \brief
	/// Method to reload all the view information.
	void reloadViewInfo();

	/// \brief
	/// Method to create all the collisionBoxes for each side.
	/// \details
	/// \param mainBox
	/// The box on bases of which the other boxes need to be created.
	CollisionBoxes createCollisionBoxes(const sf::FloatRect & mainBox);

public:

	/// \brief
	/// Constructor for Collision class.
	/// \details
	/// \param viewManager
	/// A reference to the viewManager needed for view information such as position and size.
	/// \param staticItems
	/// A reference to the static objects vector.
	/// \param dynamicItems
	/// A reference to the dynamic objects vector.
	Collision(	ViewManager & viewManager, 
				std::vector<std::unique_ptr<EntityBase>> & staticItems, 
				std::vector<std::unique_ptr<EntityBase>> & dynamicItems);
	virtual ~Collision();

	/// \brief
	/// Method to check collisions for all dynamic items.
	void checkCollisions();
};

#endif /*COLLISION_HPP*/
