#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor * owner, int drawOrder)
: SpriteComponent(owner, drawOrder)
, mCurrFrame(0.0f)
, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	// �ö��������ǻ�������ʱ��deltaTimeѡȡ������������ĳһ��������ʱ�������ʾ���ﵽ������Ч��
	SpriteComponent::Update(deltaTime);
	
	if (mAnimTextures.size() > 0) {
		mCurrFrame += mAnimFPS * deltaTime; // deltaTime ��¼��һ֡����һ֡��ʱ�䣬 mAnimFPS * deltaTime ��ʾ�� mAnimFPS ��֡�ʽ��б仯
		
		// ������������Ŀʱ�����¿�ʼ
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
		// ��ʼ����ʾ����Ϊ���������һ��
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
