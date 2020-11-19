#include "Game.h"
const int thickness = 15;
const float paddleH = 100.0f;

Game::Game():mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true), mPaddleDir(0), mPaddleDir2(0) {}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1 exercise 1)", // Window title
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

	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;

	mPaddlePos2.x = 1024.0f - 10.0f;
	mPaddlePos2.y = 768.0f / 2.0f;

	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

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

	// 更新player1 W,S键位
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}

	// 更新player2 I,K键位
	mPaddleDir2 = 0;
	if (state[SDL_SCANCODE_I])
	{
		mPaddleDir2 -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		mPaddleDir2 += 1;
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

	if (mPaddleDir2 != 0) {
		mPaddlePos2.y += mPaddleDir2 * 300.0f * deltaTime;
		if (mPaddlePos2.y < (paddleH / 2.0f + thickness)) {
			// 减去thickness 是为了不让paddle进入墙
			mPaddlePos2.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos2.y > (768.0f - paddleH / 2.0f - thickness)) {
			mPaddlePos2.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// player1
	// 球拍和球在y轴上的绝对距离
	float diff = mPaddlePos.y - mBallPos.y;
	diff = (diff > 0.0f) ? diff : -diff;

	// 如果该距离小于球拍宽的一半
	//     且在球拍范围内
	//     且小球速度是朝向球拍的
	if (
		diff <= (paddleH / 2.0f) &&
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x <= 0.0f) {
		mIsRunning = false;
	}

	// player2
	diff = mPaddlePos2.y - mBallPos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		diff <= (paddleH / 2.0f) &&
		mBallPos.x >= (1024.0f - 25.0f) && mBallPos.x <= (1024.0f - 20.0f) &&
		mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x >= 1024.0f) {
		mIsRunning = false;
	}

	if (mBallPos.y >= (768.0f - 1.5f * thickness) && mBallVel.y > 0) {
		mBallVel.y *= -1;
	}
	else if (mBallPos.y <= (1.5f * thickness) && mBallVel.y < 0) {
		mBallVel.y *= -1;
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
		255,
		255,
		255,
		255 
	);

	SDL_Rect wall{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);


	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x ),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_Rect paddle2{
		static_cast<int>(mPaddlePos2.x),
		static_cast<int>(mPaddlePos2.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

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