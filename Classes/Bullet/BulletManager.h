#ifndef _BulletManager_H_
#define _BulletManager_H_

#include <cocos2d.h>
#include "yUtils\MemPool\SimpleMemPool.h"

USING_NS_CC;

class BulletBase;
class TankBase;


class BulletManager
{
private:
	typedef std::list<BulletBase*> bulletListType;

	//�����ڳ��з�����ӵ�
	bulletListType m_listActiveBullet;

	//�����
	SimpleMemPool<BulletBase> m_memPoolBullet;
public:
	BulletManager();

	//��ȡ�����б�
	bulletListType& getActiveList();
	
	//��ȡ�ڴ�ض���
	SimpleMemPool<BulletBase>& getMemPool();

	//ÿһ֡����
	void update(Layer* layer);

	//����
	bool fire(const Vec2& vInitPos, const Vec2& vSpeed, TankBase* pTank);

};

#endif