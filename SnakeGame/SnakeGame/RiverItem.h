#pragma once
#include "Shape.h"
#include <list>

enum class ERiverItemType
{
	eLog,
	eTurtle,
};

class RiverItem : public Shape
{
private:
	float speed;
	ERiverItemType riverItemType;

public:
	RiverItem(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const float& argSpeed, const ERiverItemType& argRiverItemType);
	~RiverItem();
	virtual void Render(sf::RenderWindow& argWindow) override;
	void Move();
	void Update(const sf::Vector2f& argScreenPos);
	ERiverItemType GetRiverItemType();
	float GetSpeed();
	void Spawn(const std::list<RiverItem*>& argRiverItemList, const float& argSpawnDistance);
};

