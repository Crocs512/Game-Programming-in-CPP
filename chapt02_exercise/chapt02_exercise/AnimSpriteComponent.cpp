#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor * owner, int drawOrder, bool loop)
: SpriteComponent(owner, drawOrder)
, mCurrFrame(0.0f)
, mAnimFPS(24.0f)
, mLoop(loop)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	// �ö��������ǻ�������ʱ��deltaTimeѡȡ������������ĳһ��������ʱ�������ʾ���ﵽ������Ч��
	SpriteComponent::Update(deltaTime);
	
	if (mAnimTextures.size() > 0) {
		mCurrFrame += mAnimFPS * deltaTime; // deltaTime ��¼��һ֡����һ֡��ʱ�䣬 mAnimFPS * deltaTime ��ʾ�� mAnimFPS ��֡�ʽ��б仯
		
		if (mLoop == true) {
			// ������������Ŀʱ�����¿�ʼ
			while (mCurrFrame >= mAnimTextures.size()) {
				mCurrFrame -= mAnimTextures.size();
			}
		}
		else {
			mCurrFrame = static_cast<float>(mAnimTextures.size() - 1);
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
