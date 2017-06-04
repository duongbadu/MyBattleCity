#include "ActiveStage.h"
#include "Tank/MineTank.h"

void ActiveStage::update(float dt)
{
	m_fCurTimeCount += dt;

	if (m_fCurTimeCount - m_fMaxTime >= 0.001f)
	{
		//����
		m_bIsOver = true;
	}
}

void ActiveStage::onEnter(Player* pPlayer)
{
	MineTank* pTank = static_cast<MineTank*>(pPlayer->getTank());
	m_iPreLife = pTank->getLife();
	m_pPlayer = pPlayer;

	//���ó�����Ѫ
	pTank->setLife(MY_INT_MAX);

	//�����޵ж���
	//1. ����һ���վ���
	Sprite* spAction = Sprite::create();
	//2. ����Tank���ӽڵ�
	pTank->getSprite()->addChild(spAction, 0, 10086);
	//3. ����λ��
	spAction->setPosition(pTank->getSprite()->getContentSize() / 2);
	//4. ��������
	m_pAnimate = pTank->createBeAtkedAnimate(-1, 0.2f);
	//5. ���½��ľ��鴴������
	spAction->runAction(m_pAnimate);
	//6. �þ����������
	spAction->setScale(2.0f);
}

void ActiveStage::onExit()
{
	MineTank* pTank = static_cast<MineTank*>(m_pPlayer->getTank());

	//���û�֮ǰ��Ѫ��
	pTank->setLife(m_iPreLife);

	//ȥ������
	//1. �ҵ����Ŷ����ľ���
	Sprite* spAction = static_cast<Sprite*>(pTank->getSprite()->getChildByTag(10086));
	//2. ֹͣ����֡
	spAction->stopAllActions();
	//3. �Ƴ�����
	spAction->removeFromParentAndCleanup(true);
}
