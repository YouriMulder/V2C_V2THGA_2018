#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <cstdint>

#include "../ViewManager.hpp"
#include "Side.hpp"

class EntityBase {
private: 
	static void increaseNextId();

	sf::Clock mHurtClock = sf::Clock();
	sf::Time mHurtingDuration = sf::seconds(1);
	sf::Time timeSinceLastHurt = mHurtingDuration/8.0f;
	bool mIsHurting = false;

protected:
	static uint_least64_t nextId;
	
	uint_least64_t id;
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
	int mScreenNumber;
	bool mIsVisible;
	bool mIsSolid;
	bool mShouldDestroyed;

public:
	static void backToStartId();

	EntityBase(
		const sf::Vector2f& mPosition, 
		const sf::Vector2f mSize, 
		int mScreenNumber,
		bool mIsSolid = true,
		bool mIsVisible = true
	);
	
	uint_least64_t getId() const;
	void move(float deltaX, float deltaY);
	void move(const sf::Vector2f& deltaPosition);

	void setScreenNumber(int newScreenNumber);
	int getScreenNumber() const;
	void setIsVisible(bool isVisible);
	bool isVisible() const;
	void setIsSolid(bool isSolid);
	bool isSolid() const;
	void destroy();
	bool shouldDestroy() const;

	virtual void hurt(uint_least8_t damage) {};

	void setPosition(float x, float y);
	virtual void setPosition(const sf::Vector2f& newPosition);
	void setSize(const sf::Vector2f& newSize);

	virtual sf::Vector2f getSize() const;
	virtual sf::Vector2f getPosition() const;
	virtual sf::Vector2f getNextPosition() const;
	virtual sf::FloatRect getGlobalBounds() const;
	virtual bool isFinished() const;
	
	virtual void update(const sf::Time& deltaTime) = 0;
	
	/// \param top
	/// This contains all the objects that the Character collides with on the top.
	/// \param bottom
	/// This contains all the objects that the Character collides with on the bottom.	
	/// \param left
	/// This contains all the objects that the Character collides with on the left.
	/// \param right
	/// This contains all the objects that the Character collides with on the right.
	/// \param hitSides
	/// This contains booleans of all sides which are true 
	/// when something collided on that side.
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	) {};
	virtual void handleNoCollision() {};
	void removeNonSolid(
		std::vector<std::unique_ptr<EntityBase>*>& top, 
		std::vector<std::unique_ptr<EntityBase>*>& bottom, 
		std::vector<std::unique_ptr<EntityBase>*>& left, 
		std::vector<std::unique_ptr<EntityBase>*>& right, 
		CollisionSides& hitSides
	) const;

	virtual void setColor(const sf::Color& newColor) {};
	
	void drawIfVisible(sf::RenderWindow& window); 
	void drawIfVisible(ViewManager& window); 	
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void draw(ViewManager& window) = 0;
	virtual ~EntityBase();
};

#endif /* ENTITY_BASE_HPP */