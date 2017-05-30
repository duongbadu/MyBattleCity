#ifndef _TankFactory_H_
#define _TankFactory_H_

#include "MineTank.h"
#include "EnemyTank.h"

class TankFactory
{
private:
	//��ͼ�������ڴ���
	TankTiledMap* m_pMap;

	//�ٶȶ������ڴ���
	Vec2 m_vInitSpeed;

public:
	TankFactory();

	TankFactory(TankTiledMap* pMap, const Vec2& vSpeed);

	//����Ĭ�ϴ�����ٶȶ���
	void setInitSpeed(const Vec2& vSpeed);

	//����Ĭ�ϵĴ����ͼ����
	void setTankMap(TankTiledMap* pMap);

	//����һ��̹�˶���
	TankBase* create(const TankType& tankType);
};


#endif