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
		m_tankType = EnemyTankGreen;
		break;
	case EnemyTankWhite: 
		m_tankType = EnemyTankYellow;
		break;
	case EnemyTankRed: 
		m_tankType = EnemyTankWhite;
		break;
	}
}
