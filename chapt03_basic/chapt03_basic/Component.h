#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime); // ��������ʱ�����
	virtual void ProcessInput(const uint8_t * keyState);

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// ӵ����
	class Actor* mOwner;
	// ����˳�򣬸���˳��ֵԽС��Խ�����
	int mUpdateOrder;
};
