#ifndef _EnemyTank_H_
#define _EnemyTank_H_


#include "TankBase.h"

/**
*	@class : EnemyTank
*	@brief : ����TankBase��beAtk����
*/


class EnemyTank : public TankBase
{
private:
	//�Ƿ�����
	bool m_bIsDie;

	//������ʶ��ǰ��̹������
	TankType m_tCurType;

public:
	EnemyTank(Sprite* spTank, const TankType& tankType, TankTiledMap* pMap, const Vec2& speed)
		: TankBase(spTank, tankType, pMap, speed)
		, m_bIsDie(false),
		m_tCurType(tankType)
	{
	}

	virtual ~EnemyTank() override;

	virtual void beAtked() override;

	bool isDie() const
	{
		return m_bIsDie;
	}

	void setIsDie(bool bIsDie)
	{
		m_bIsDie = bIsDie;
	}
};


#endif