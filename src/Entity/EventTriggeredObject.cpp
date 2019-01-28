#include "EventTriggeredObject.hpp"
#include "Player.hpp"


EventTriggeredObject::EventTriggeredObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, std::function<void()> work, bool destroyOnCollision, bool repeated, bool isVisible):
	mWork(work),
	mDestroyOnCollision(destroyOnCollision),
	LevelObject(filename,position,size,screenNumber,repeated)
{
	setIsVisible(isVisible);
	setIsSolid(false);
}


EventTriggeredObject::~EventTriggeredObject()
{
}

void EventTriggeredObject::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top,
	std::vector<std::unique_ptr<EntityBase>*> bottom,
	std::vector<std::unique_ptr<EntityBase>*> left,
	std::vector<std::unique_ptr<EntityBase>*> right,
	CollisionSides hitSides
) {

	std::vector<
		std::vector<std::unique_ptr<EntityBase>*>
	> allObjects = { top, bottom, left, right };

	for (const auto& objectVector : allObjects) {
		for (const auto& object : objectVector) {
			const auto& uniqueObject = (*object);
			if (dynamic_cast<Player*>(uniqueObject.get())) {
				setIsVisible(true);
				if (!EntityBase::shouldDestroy()) {
					mWork();
				}
				if (mDestroyOnCollision) {
					destroy();
				}
			}
		}
	}
}