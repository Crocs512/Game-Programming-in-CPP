#pragma once
#include "Actor.h"
#include "CollisionComponent.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	float mLaserCooldown;
	float mDeathTimer;
	CollisionComponent* mCircle;
};