#pragma once
#include "SDL.h"
#include<vector>

struct Vector2 {
	float x;
	float y;
};

class Game {
public:
	Game();

	bool Initialize(); // 初始化
	void RunLoop();  // 游戏循环
	void Shutdown();  // 关闭游戏，释放资源
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	std::vector<Vector2> mBallPoses;
	std::vector<Vector2> mBallVels;

	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;

	int mPaddleDir;
	int mBallNums;
	bool mIsRunning;
	Uint32 mTicksCount;
};