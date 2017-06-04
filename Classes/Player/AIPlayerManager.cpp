#include "AIPlayerManager.h"
#include "Layer\GameLayer.h"
#include <Layer/WinLayer.h>
#include <SimpleAudioEngine.h>


AIPlayerManager::AIPlayerManager()
	:m_pUserTank(nullptr)
{

}

AIPlayerManager::~AIPlayerManager()
{

}


void AIPlayerManager::addAiPlayer(Player* pPlayer)
{
	m_listAIPlayer.push_back(pPlayer);
}

void AIPlayerManager::aiUpdte(Layer* layer, float dt)
{
	for (auto it = m_listAIPlayer.begin();
		it != m_listAIPlayer.end(); )
	{
		AIPlayer* pBuf = static_cast<AIPlayer*>(*it);
		pBuf->update(layer, dt);
		++it;
	}
}

void AIPlayerManager::collisionUpdate(Layer* layer, float dt)
{
	static float fDeletTime = 0.0f;

	fDeletTime += dt;

	GameLayer* pLayer = static_cast<GameLayer*>(layer);

	//��ȡ�û��ӵ��������
	BulletManager* pUserBulletMgr = m_pUserTank->getBulletMgr();
	
	//�ҷ��ӵ���ai̹�˵���ײ���
	auto userBulletList = pUserBulletMgr->getActiveList();
	
	for (auto it_bullet = userBulletList.begin();
		it_bullet != userBulletList.end();
		)
	{
		BulletBase* pBullet = *it_bullet;
		bool bIsClearBullet = false;
		//ȡ��ÿһ��ai̹��
		for (auto it = m_listAIPlayer.begin();
			it != m_listAIPlayer.end();
			)
		{
			AIPlayer* pBuf = static_cast<AIPlayer*>(*it);

			if (
				pBullet->getSprite()->isVisible() && 
				pBullet->getSprite()->getBoundingBox().intersectsRect(
				pBuf->getTank()->getNextMoveRect()))
			{
				//������ײ

				//�Ƴ��о�̹��
				pBuf->getTank()->beAtked();

				//�������
				if (static_cast<EnemyTank*>(pBuf->getTank())->isDie())
				{
					//��ӷ���
					pLayer->getHudLayer()->setScore(
						pLayer->getHudLayer()->getScore() + 
						(pBuf->getTank()->getTankType() + 1) * 100);

					//���������Ƴ�ai���
					it = m_listAIPlayer.erase(it);

					auto deleteList = pBuf->getTank()->getBulletMgr()->getActiveList();
					//���������ӵ�
					for (auto it_delete = deleteList.begin();
						it_delete != deleteList.end();
						)
					{
						BulletBase* pDeleteBullet = *it_delete;
						
						//�ӵ�����
						pBuf->getTank()->getBulletMgr()->getMemPool().release(pDeleteBullet);

						//�����ӵ�
						pDeleteBullet->getSprite()->setVisible(false);

						//���������Ƴ�
						it_delete = deleteList.erase(it_delete);
					}

					//�Ӳ����Ƴ�
					pBuf->getTank()->getSprite()->removeFromParentAndCleanup(true);

					//�����ڴ�
					delete pBuf;

					//���ű����ٵ���Ч
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/blast.aif");

					//ʤ���ж�
					if (m_listAIPlayer.empty() && pLayer->getHudLayer()->getRemainEnemyNum() <= 0)
					{
						//ʤ��
						Director::getInstance()->replaceScene(WinLayer::createScene());
					}

					

				}

				//�ӵ�����
				pUserBulletMgr->getMemPool().release(pBullet);

				//�����ӵ�
				pBullet->getSprite()->setVisible(false);

				//���ӵ��Ӽ����б���ȡ��
				it_bullet = userBulletList.erase(it_bullet);

				bIsClearBullet = true;

				break;
			}
			else
			{
				++it;
			}

		}

		if (!bIsClearBullet)
		{
			++it_bullet;
		}

	}



	//ai�ӵ����û�̹����ײ���
	for (auto it = m_listAIPlayer.begin();
		it != m_listAIPlayer.end();)
	{
		AIPlayer* pBuf = static_cast<AIPlayer*>(*it);
		BulletManager* pBufBulletMgr = pBuf->getTank()->getBulletMgr();
		auto bulletList = pBufBulletMgr->getActiveList();


		//ÿһ��ai���ӵ��б�
		for ( auto it_bullet = bulletList.begin();
			it_bullet != bulletList.end(); )
		{
			BulletBase* pBullet = *it_bullet;
			if (
				pBullet->getSprite()->isVisible() && 
				pBullet->getSprite()->getBoundingBox().intersectsRect(
				m_pUserTank->getNextMoveRect()))
			{
				//�û�������
				m_pUserTank->beAtked();

				//�ӵ���ʧ
				pBufBulletMgr->getMemPool().release(pBullet);

				//���ӵ�����
				pBullet->getSprite()->setVisible(false);

				//���ӵ����б����Ƴ�
				it_bullet = bulletList.erase(it_bullet);

				break;
			}
			else
			{
				++it_bullet;
			}
		}

		++it;
	}

	for (auto it : m_listAIPlayer)
	{
		it->getTank()->getBulletMgr()->update(layer);
	}

	//�ƶ�
	pUserBulletMgr->update(layer);
}

void AIPlayerManager::setUserTank(TankBase* pUserTank)
{
	m_pUserTank = pUserTank;
}

size_t AIPlayerManager::getAIPlayerNum() const
{
	return m_listAIPlayer.size();
}
