#ifndef _ActiveStage_H_
#define _ActiveStage_H_

#include "StageBase.h"

/**
*	@class : ActiveStage
*	@brief : �޵е�����
*/
class ActiveStage : public StageBase
{
private:
	//���ڼ�¼����֮ǰ������ֵ
	int m_iPreLife;

	//��¼ʹ����
	Player* m_pPlayer;

	//̹�����е��޵ж���
	Animate* m_pAnimate;

	//����ʱ��
	float m_fMaxTime;

	//�Ѿ�������ʱ��
	float m_fCurTimeCount;

public:
	ActiveStage(Sprite* spSprite, TankTiledMap* pMap, float fDelayTime)
		: StageBase(spSprite, StageActive, pMap),
		m_fMaxTime(fDelayTime),
		m_fCurTimeCount(0),
		m_iPreLife(0)
	{

	}

	virtual void update(float dt) override;

	virtual void onEnter(Player* pPlayer) override;

	virtual void onExit() override;
};


#endif