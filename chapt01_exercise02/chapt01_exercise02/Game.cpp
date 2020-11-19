#include "Game.h"
const int thickness = 15;
const float paddleH = 100.0f;

Game::Game():mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true), mPaddleDir(0){}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1 exercise 02)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	// 小球数量随机1~10之间
	srand((unsigned)time(0));
	mBallNums = rand() % 10;

	for (int i = 0; i < mBallNums; i++) {
		// 小球初始位置不变
		Vector2 mBallPos;
		mBallPos.x = 1024.0f / 2.0f;
		mBallPos.y = 768.0f / 2.0f;
		mBallPoses.push_back(mBallPos);

		// 小球初始速度随机变化
		Vector2 mBallVel;
		mBallVel.x = rand() % 100 - 200.0f;
		mBallVel.y = rand() % 100 + 200.0f;
		mBallVels.push_back(mBallVel);
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;

	return true;
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type){
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	// 更新W,S 和Up,Down 键位
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	// 使得当前帧和上一帧始终保持16ms 的差距，限制帧
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// 增量时间计算
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// 防止增量时间过大
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 更新上一帧
	mTicksCount = SDL_GetTicks();

	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
			// 减去thickness 是为了不让paddle进入墙
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	// 每一个小球进行碰撞检测，用flag标志数组标志哪一个小球已经出界
	std::vector<int> flag(mBallNums, 0);
	for (int i = 0; i < mBallNums; i++) {
		auto& mBallPos = mBallPoses[i];
		auto& mBallVel = mBallVels[i];

		mBallPos.x += mBallVel.x * deltaTime;
		mBallPos.y += mBallVel.y * deltaTime;

		float diff = mPaddlePos.y - mBallPos.y;
		diff = (diff > 0.0f) ? diff : -diff;

		if (
			diff <= (paddleH / 2.0f) &&
			mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
			mBallVel.x < 0.0f)
		{
			mBallVel.x *= -1.0f;
		}
		else if (mBallPos.x <= 0.0f && mBallNums <= 0) {
			mIsRunning = false;
		}
		else if (mBallPos.x <= 0.0f && mBallNums > 0) {
			flag[i] = 1;
		}
		else if (mBallPos.x >= (1024.0f - 1.5f * thickness) && mBallVel.x > 0) {
			mBallVel.x *= -1;
		}

		if (mBallPos.y >= (768.0f - 1.5f * thickness) && mBallVel.y > 0) {
			mBallVel.y *= -1;
		}
		else if (mBallPos.y <= (1.5f * thickness) && mBallVel.y < 0) {
			mBallVel.y *= -1;
		}
	}

	// 如果小球出界，则删除该小球
	// 如果所有小球都出界，那么游戏结束
	for (int i = 0; i < mBallNums; i++) {
		if (flag[i] == 1) {
			mBallPoses.erase(mBallPoses.begin() + i);
			mBallVels.erase(mBallVels.begin() + i);
			mBallNums--;
		}
		if (mBallNums <= 0) mIsRunning = false;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		255,
		255
	);
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(
		mRenderer,
		255, // R
		255, // G
		255, // B
		255  // A
	);
	// Top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	for (int i = 0; i < mBallNums; i++) {
		auto& mBallPos = mBallPoses[i];
		auto& mBallVel = mBallVels[i];

		SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
		};
		SDL_RenderFillRect(mRenderer, &ball);
	}

	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x ),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_RenderPresent(mRenderer);
}

void Game::RunLoop()
{
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}