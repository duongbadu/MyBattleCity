#include "AIPlayer.h"
#include "Layer\GameLayer.h"

AIPlayer::~AIPlayer()
{

}

void AIPlayer::update(Layer* layer)
{
	//�����ϴ��ߵķ���һֱ��
	int rota = m_pTank->getSprite()->getRotation();
	m_pTank->command(static_cast<TankCommandType>(rota / 90 + 1));

	//����
	m_pTank->command(Shot);

	//�����ǰ���򲻿����ߣ���һ������
	if (!m_pTank->isCanMove())
	{

		m_pTank->getSprite()->setRotation(static_cast<int>(CCRANDOM_0_1() * 3.2) * 90);
		//m_pTank->command(static_cast<TankCommandType>(rota / 90 + 1));
	}

	m_pTank->move();
}
