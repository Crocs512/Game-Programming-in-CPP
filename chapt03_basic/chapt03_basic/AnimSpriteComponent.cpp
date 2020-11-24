#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor * owner, int drawOrder)
: SpriteComponent(owner, drawOrder)
, mCurrFrame(0.0f)
, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	// 该动画更新是基于增量时间deltaTime选取纹理数组里面某一幅纹理随时间进行显示，达到动画的效果
	SpriteComponent::Update(deltaTime);
	
	if (mAnimTextures.size() > 0) {
		mCurrFrame += mAnimFPS * deltaTime; // deltaTime 记录上一帧到这一帧的时间， mAnimFPS * deltaTime 表示以 mAnimFPS 的帧率进行变化
		
		// 当超出纹理数目时，重新开始
		while (mCurrFrame >= mAnimTextures.size()) {
			mCurrFrame -= mAnimTextures.size();
		}

		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// 初始化显示纹理为纹理数组第一张
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
