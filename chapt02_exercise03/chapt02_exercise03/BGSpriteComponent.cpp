#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor * owner, int drawOrder)
	:SpriteComponent(owner,drawOrder)
	, mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		// 更新x偏移
		bg.mOffset.x += mScrollSpeed * deltaTime;  // mScrollSpeed 为负

		if (bg.mOffset.x < -mScreenSize.x)  // -mScreenSize.x 为 -1024.0f
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer * renderer)
{
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;

		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		// 需要加上偏移来计算纹理的x和y坐标
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.mTexture,
			nullptr,
			&r
		);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// count张纹理，那么所有纹理能够拼接的长度就为 count * mScreenSize.x (假设每张纹理的宽度和mScreenSize.x一致)
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
