#pragma once
#include "SDL.h"

// ������
struct Vector2 {
	float x;
	float y;
};

class Game {
public:
	Game();

	bool Initialize(); // ��ʼ��
	void RunLoop();  // ��Ϸѭ��
	void Shutdown();  // �ر���Ϸ���ͷ���Դ
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	Vector2 mPaddlePos;
	Vector2 mPaddlePos2;
	Vector2 mBallPos;
	Vector2 mBallVel;

	int mPaddleDir;
	int mPaddleDir2;
	bool mIsRunning;
	Uint32 mTicksCount;
};