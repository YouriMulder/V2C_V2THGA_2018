#ifndef SPIKES_HPP
#define SPIKES_HPP

#include <SFML/Graphics.hpp>

#include "EntityBase.hpp"
#include "LevelObject.hpp"
#include "../ViewManager.hpp"
#include <string>
#include <vector>
#include <cstdint>

class Spikes : public LevelObject {
private:
	uint_least8_t mDamage;
	sf::Time timeBetweenHits = sf::seconds(1);

	std::vector<
		std::pair<uint_fast64_t, sf::Clock>
	> hitClocks = {};

	void addClock(uint_least64_t entityId);
	bool isClocked(uint_least64_t entityId);
	
public:
	Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, uint_least8_t damage, bool repeated = false);
	Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, uint_least8_t damage, bool repeated = false);
	virtual sf::FloatRect getGlobalBounds() const override;
	
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right,  
		CollisionSides hitSides
	) override;
	virtual void update(const sf::Time& deltaTime) override;
	
};

#endif /* SPIKES_HPP */