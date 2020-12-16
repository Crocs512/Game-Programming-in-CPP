// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "AIComponent.h"

class Tower : public Actor
{
public:
	Tower(class Game* game);
	void UpdateActor(float deltaTime) override;
	float GetAttackRange() const { return AttackRange; }
	float GetAttackTime() const { return AttackTime; }
	void AddNextAttack(float attack) { mNextAttack += attack; }
private:
	class MoveComponent* mMove;
	class AIComponent* mAIcomp;
	float mNextAttack;
	const float AttackTime = 2.5f;
	const float AttackRange = 100.0f;
};
