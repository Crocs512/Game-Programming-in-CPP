// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Tower.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AIState.h"

Tower::Tower(class Game* game)
:Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 200);
	sc->SetTexture(game->GetTexture("Assets/Tower.png"));
	
	mMove = new MoveComponent(this);
	//mMove->SetAngularSpeed(Math::Pi);
	
	mNextAttack = AttackTime;

	mAIcomp = new AIComponent(this);
	mAIcomp->RegisterState(new AIPatrol(mAIcomp));
	mAIcomp->RegisterState(new AIAttack(mAIcomp));
	mAIcomp->ChangeState("Patrol");
}

void Tower::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	mNextAttack -= deltaTime;
	if (mNextAttack <= 0.0f)
	{
		Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
		if (e != nullptr) 
		{
			mAIcomp->ChangeState("Attack");
		}
	}
	else if (strcmp(mAIcomp->GetCurrentState(), "Patrol") != 0)
	{
		mAIcomp->ChangeState("Patrol");
	}
	mAIcomp->Update(deltaTime);
}
