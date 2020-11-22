#pragma once
class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime); // ��������ʱ�����

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// ӵ����
	class Actor* mOwner;
	// ����˳�򣬸���˳��ֵԽС��Խ�����
	int mUpdateOrder;
};
