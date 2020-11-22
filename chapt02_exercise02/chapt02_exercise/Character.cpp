#include "Character.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Character::Character(Game * game, Type type, bool loop) 
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	std::vector<SDL_Texture*> anims;
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, 100, loop);
	switch (type)
	{
	case Character::Walking:
		anims = {
			game->GetTexture("Assets/Character01.png"),
			game->GetTexture("Assets/Character02.png"),
			game->GetTexture("Assets/Character03.png"),
			game->GetTexture("Assets/Character04.png"),
			game->GetTexture("Assets/Character05.png"),
			game->GetTexture("Assets/Character06.png"),
		};
		break;
	case Character::Jumping:
		anims = {
			game->GetTexture("Assets/Character07.png"),
			game->GetTexture("Assets/Character08.png"),
			game->GetTexture("Assets/Character09.png"),
			game->GetTexture("Assets/Character10.png"),
			game->GetTexture("Assets/Character11.png"),
			game->GetTexture("Assets/Character12.png"),
			game->GetTexture("Assets/Character13.png"),
			game->GetTexture("Assets/Character14.png"),
			game->GetTexture("Assets/Character15.png"),
		};
		break;
	case Character::Punch:
		anims = {
			game->GetTexture("Assets/Character16.png"),
			game->GetTexture("Assets/Character17.png"),
			game->GetTexture("Assets/Character18.png"),
		};
		break;
	}
	asc->SetAnimTextures(anims);
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// 通过速度更新位置
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	// 限制位置
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	SetPosition(pos);
}

void Character::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
}
