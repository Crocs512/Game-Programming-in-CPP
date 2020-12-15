#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "Asteroid.h"

Ship::Ship(Game* game)
	:Actor(game)
	, mLaserCooldown(0.0f)
	, mDeathTimer(0.0f)
{
	// 创建飞船的动画精灵, 其拥有者为Ship
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship.png"),
	};
	asc->SetAnimTextures(anims);

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	mCircle = new CollisionComponent(this);
	mCircle->SetRadius(20.0f);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	mLaserCooldown -= deltaTime;

	if (mDeathTimer < 0.0f) {
		SetPosition(Vector2{ 512.0f, 384.0f });
		SetRotation(0.0f);
		mDeathTimer = 0.0f;
	}

	if (mDeathTimer > 0.0f) {
		SetPosition(Vector2{ -100.0f, -100.0f });
		mDeathTimer -= deltaTime;

		if (mDeathTimer == 0.0f)
		{
			mDeathTimer -= 1.0f;
		}
	}
	else {
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				mDeathTimer = 2.0f;
				break;
			}
		}
	}
}

void Ship::ActorInput(const uint8_t * keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		mLaserCooldown = 0.5f;
	}
}
