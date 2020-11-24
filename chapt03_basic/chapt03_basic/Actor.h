#pragma once
#include <vector>
#include"Math.h"
class Actor {
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);

	void ProcessInput(const uint8_t * keyState);

	virtual void ActorInput(const uint8_t * keyState);

	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }

	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	// ×´Ì¬
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	Game* GetGame() { return mGame; }

	// Ìí¼Ó/ÒÆ³ý ×é¼þ
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor×´Ì¬
	State mState;

	// ±ä»»
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};