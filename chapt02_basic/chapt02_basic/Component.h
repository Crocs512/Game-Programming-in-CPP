#pragma once
class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime); // 根据增量时间更新

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// 拥有者
	class Actor* mOwner;
	// 更新顺序，更新顺序值越小，越早更新
	int mUpdateOrder;
};
