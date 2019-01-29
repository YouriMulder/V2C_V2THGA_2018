#ifndef EVENTTRIGGEREDOBJECT_HPP
#define EVENTTRIGGEREDOBJECT_HPP

#include "LevelObject.hpp"
#include <functional>
class EventTriggeredObject : public LevelObject {
private:
	std::function<void()> mWork;
	bool mDestroyOnCollision;
public:
	EventTriggeredObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, std::function<void()> work, bool destroyOnCollision, bool repeated = false, bool isVisible = true );
	

	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top,
		std::vector<std::unique_ptr<EntityBase>*> bottom,
		std::vector<std::unique_ptr<EntityBase>*> left,
		std::vector<std::unique_ptr<EntityBase>*> right,
		CollisionSides hitSides
	) override;
	virtual ~EventTriggeredObject();
};
#endif /*EVENTTRIGGEREDOBJECT_HPP*/

