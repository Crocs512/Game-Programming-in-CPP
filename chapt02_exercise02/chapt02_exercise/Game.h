#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// ��Ľ�ɫ�б�
	std::vector<class Actor*> mActors;
	// ����Ľ�ɫ�б�
	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	
	// �жϵ�ǰ�Ƿ����ڸ������н�ɫ
	bool mUpdatingActors;

	class Character* mCharacter;
	class Character* mCharacter2;
	class Character* mCharacter3;
};