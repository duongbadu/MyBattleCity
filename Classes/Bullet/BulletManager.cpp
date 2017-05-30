#include "BulletManager.h"
#include "BulletBase.h"

BulletManager::BulletManager()
{

}

BulletManager::bulletListType& BulletManager::getActiveList()
{
	return m_listActiveBullet;
}

SimpleMemPool<BulletBase>& BulletManager::getMemPool()
{
	return m_memPoolBullet;
}

void BulletManager::update(Layer* layer)
{
	for (auto it = m_listActiveBullet.begin();
		it != m_listActiveBullet.end();
		)
	{
		BulletBase* pBullet = *it;
		
		//���������ײ���߳���
		if (pBullet->bulletCollision())
		{
			//���ýڵ��������
			m_memPoolBullet.release(pBullet);

			//���ýڵ�����
			pBullet->getSprite()->setVisible(false);

			//���ýڵ�Ӽ���������ȡ��
			it = m_listActiveBullet.erase(it);
		}
		else
		{
			//û�з�����ײ

			//����λ��
			pBullet->move();

			//������һ���ڵ�
			++it;
		}
	}
}

bool BulletManager::fire(const Vec2& vInitPos, const Vec2& vSpeed, TankBase* pTank)
{
	//������������û�У��򴴽�һ�����ӵ�s
	BulletBase* pBullet = m_memPoolBullet.allocWithTag(0);
	if (!pBullet)
	{
		//�½�һ���ӵ�
		pBullet = new BulletBase(Sprite::create("tank/bullet.png"),
			pTank->getMap(), pTank, vSpeed);

		if (!pBullet)
		{
			return false;
		}
		
		//����λ��
		pBullet->getSprite()->setPosition(vInitPos);
		
		//����ӵ�����ͼ��
		pTank->getMap()->getTiledMap()->addChild(pBullet->getSprite());

		//����ӵ�������ص���ʹ��������
		m_memPoolBullet.addNewNodeToUsedList(SimpleMemPool<BulletBase>::MemTagNode(pBullet,0));
	}
	else
	{
		//�еĻ�ֱ������λ��
		pBullet->getSprite()->setPosition(vInitPos);

		//���ÿɼ�
		pBullet->getSprite()->setVisible(true);

		//�����ٶ�
		pBullet->setSpeed(vSpeed);
	}

	//���뵽����������
	m_listActiveBullet.push_back(pBullet);

	return true;
}