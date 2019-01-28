#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "LevelObject.hpp"
#include "Timer.hpp"
#include <cstdint>

class Projectile : public LevelObject {
	bool mIsDirectionRight;
	Timer destroyTimer;
	float mMovementPerSecond = 300.0f; 
	uint_least8_t mDamage = 1;

public:
	Projectile(
		const std::string& filename, 
		const sf::Vector2f& position, 
		int screenNumber,
		bool isDirectionRight 
	);
	virtual ~Projectile();

	virtual void update(const sf::Time& deltaTime) override;
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	) override;

};

#endif /* PROJECTILE_HPP */