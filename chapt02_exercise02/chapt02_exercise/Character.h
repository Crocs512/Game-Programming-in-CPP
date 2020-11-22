#pragma once
#include "Actor.h"
class Character: public Actor {
public:
	enum Type
	{
		Walking,
		Jumping,
		Punch
	};
	Character(class Game* game, Type type = Type::Walking, bool loop = false);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
private:
	float mRightSpeed;
	float mDownSpeed;
};
