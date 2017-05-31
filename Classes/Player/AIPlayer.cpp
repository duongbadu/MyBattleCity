#include "AIPlayer.h"
#include "Layer\GameLayer.h"

AIPlayer::~AIPlayer()
{

}

void AIPlayer::update(Layer* layer, float dt)
{
	m_fAllDelayTime += dt;

	//�����ϴ��ߵķ���һֱ��
	int rota = m_pTank->getSprite()->getRotation();
	m_pTank->command(static_cast<TankCommandType>(rota / 90 + 1));

	//1s��һ�ο���
	if (m_fAllDelayTime - 1.0f >= -0.0001f)
	{
		m_pTank->command(Shot);
		m_fAllDelayTime = 0.0f;
	}

	//�����ǰ���򲻿����ߣ���һ������
	if (!m_pTank->isCanMove())
	{
		m_pTank->getSprite()->setRotation(static_cast<int>(rand() % 4) * 90);
	}

	m_pTank->move();
}
