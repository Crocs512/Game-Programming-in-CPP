#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner) // 添加component到Actor中
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this); // 添加精灵到场景中
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer * renderer)
{
	if (mTexture) {
		SDL_Rect r;

		// 放缩后的纹理宽高
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

		// SDL_Rect 的x/y 坐标规定的是左上角，需要把位于角色中心点的 x/y 坐标转换到左上角
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2.0f);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2.0f);

		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			&r,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture * texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
