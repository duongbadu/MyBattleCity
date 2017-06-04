#include "EnemyTank.h"

EnemyTank::~EnemyTank()
{

}

void EnemyTank::beAtked()
{
	//ÿ������һ�Σ�����ı���ɫ��ֱ������
	switch (m_tankType)
	{
	case EnemyTankGreen: 
		//����
		m_bIsDie = true;
		break;
	case EnemyTankYellow:
		m_spTank->setTexture("tank/armor/armor3U.pngg");
		m_tankType = EnemyTankGreen;
		break;
	case EnemyTankWhite: 
		m_spTank->setTexture("tank/armor/armor2U.png");
		m_tankType = EnemyTankYellow;
		break;
	case EnemyTankRed: 
		m_spTank->setTexture("tank/armor/armor1U.png");
		m_tankType = EnemyTankWhite;
		break;
	}
}
