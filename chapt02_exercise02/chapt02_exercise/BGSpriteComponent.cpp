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
		// ����xƫ��
		bg.mOffset.x += mScrollSpeed * deltaTime;  // mScrollSpeed Ϊ��

		if (bg.mOffset.x < -mScreenSize.x)  // -mScreenSize.x Ϊ -1024.0f
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
		// ��Ҫ����ƫ�������������x��y����
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
		// count��������ô���������ܹ�ƴ�ӵĳ��Ⱦ�Ϊ count * mScreenSize.x (����ÿ������Ŀ�Ⱥ�mScreenSize.xһ��)
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
