#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent: public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100, bool loop = false);
	void Update(float deltaTime) override;
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	std::vector<SDL_Texture*> mAnimTextures; // ��������
	float mCurrFrame;  // ��ǰ֡����ʾ������
	float mAnimFPS;  // ֡��
	bool mLoop; // ���ƶ����Ƿ�ѭ��
};