#ifndef _BulletBase_H_
#define _BulletBase_H_

#include <cocos2d.h>
#include "Map/TankTiledMap.h"
#include "Tank/TankBase.h"
#include "Layer\GameOverLayer.h"
USING_NS_CC;

/**
*	@brief : �ӵ�����
*	@class : BulletBase
*/
class BulletBase
{
protected:
	//�ӵ�����
	Sprite* m_spBullet;

	//�ӵ��ٶ�
	Vec2 m_vSpeed;

	//��ͼ����
	TankTiledMap* m_pMap;

	//������̹�˶���
	TankBase* m_pTank;
public:
	BulletBase(Sprite* spBullet, TankTiledMap* pMap, TankBase* pTank, const Vec2& vSpeed);

	virtual ~BulletBase();

	//�ӵ��ƶ�����
	virtual void move();

	//�ӵ���ײ��⺯��
	bool bulletCollision();

	//��ȡ�ӵ�����
	Sprite* getSprite();

	//�����ӵ��ٶ�
	void setSpeed(const Vec2& vSpeed);

	//��ȡ�ӵ��ٶ�
	Vec2 getSpeed() const;

	//��������̹��
	void setTank(TankBase* pTank);

	//����������ͼ
	void setTiledMap(TankTiledMap* pMap);
};

#endif