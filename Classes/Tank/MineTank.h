#ifndef _MineTank_H_
#define _MineTank_H_

#include "TankBase.h"

/**
*	@class : MineTank
*	@brief : �����ҷ�̹�˱�����ʱ�����Ϊ
*/

class MineTank : public TankBase
{
protected:
	//�ҷ�̹�˵�����ֵ
	int m_iLife; 


public:
	MineTank(Sprite* spTank, const TankType& tankType, TankTiledMap* pMap, const Vec2& speed, int iLife)
		: TankBase(spTank, tankType, pMap, speed),
		m_iLife(iLife)
	{
	}

	virtual ~MineTank() override;

	virtual void beAtked() override;

	//����������ʱ�Ķ���,ȷ���ú��������ڼ����꾫��֡�����
	Animate* createBeAtkedAnimate(unsigned int loops, float delayTime);

	//�����ҷ�̹�˵�����ֵ
	void setLife(int iLife)
	{
		m_iLife = iLife;
	}

	//��ȡ�ҷ�̹�˵�����ֵ
	int getLife() const
	{
		return m_iLife;
	}
	
};

#endif