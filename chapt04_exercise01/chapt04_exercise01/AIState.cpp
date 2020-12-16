// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AIState.h"
#include "AIComponent.h"
#include "Actor.h"
#include "Enemy.h"
#include "Game.h"
#include "Tower.h"
#include "Bullet.h"
#include <iostream>
#include <SDL_log.h>

void AIPatrol::Update(float deltaTime)
{
	//SDL_Log("Updating %s state", GetName());

	mTime += deltaTime;
	if (mTime >= 360.0f) mTime = 0.0f;

	float angle = sin(mTime) * 2.5f;
	mOwner->GetOwner()->SetRotation(angle);
}

void AIPatrol::OnEnter()
{
	mTime = mOwner->GetOwner()->GetRotation();
	//SDL_Log("Entering %s state", GetName());
}

void AIPatrol::OnExit()
{
	//SDL_Log("Exiting %s state", GetName());
}

void AIDeath::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());
}

void AIDeath::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIDeath::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

void AIAttack::Update(float deltaTime)
{
	//SDL_Log("Updating %s state", GetName());
}

void AIAttack::OnEnter()
{
	Enemy* e = mOwner->GetOwner()->GetGame()->GetNearestEnemy(mOwner->GetOwner()->GetPosition());
	if (e != nullptr)
	{
		// Vector from me to enemy
		Vector2 dir = e->GetPosition() - mOwner->GetOwner()->GetPosition();
		float dist = dir.Length();
		if (dist < dynamic_cast<Tower*>(mOwner->GetOwner())->GetAttackRange())
		{
			// Rotate to face enemy
			mOwner->GetOwner()->SetRotation(Math::Atan2(-dir.y, dir.x));
			// Spawn bullet at tower position facing enemy
			Bullet* b = new Bullet(mOwner->GetOwner()->GetGame());
			b->SetPosition(mOwner->GetOwner()->GetPosition());
			b->SetRotation(mOwner->GetOwner()->GetRotation());
		}
	}
	dynamic_cast<Tower*>(mOwner->GetOwner())->AddNextAttack(2.5f);
	//SDL_Log("Entering %s state", GetName());
}

void AIAttack::OnExit()
{
	//SDL_Log("Exiting %s state", GetName());
}
