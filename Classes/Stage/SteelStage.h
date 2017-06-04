#ifndef _StellStage_H_
#define _StellStage_H_

#include "StageBase.h"
#include "Map\TankTiledMap.h"
#include "Common\Common.h"
USING_NS_CC;


/**
*	@class : SteelStage
*	@brief : ���ڽ��������ܱ���� 
*/
class SteelStage : public StageBase
{
private:
	//�ܹ�������ʱ��
	float m_fMaxTime;

	//��ǰ�Ѿ�������ʱ��
	float m_fCurTimeCount;

	//���ڴ洢�������ܵķ���λ��(�����tiledmap��������ͼ)
	std::vector<Vec2> m_arrHomeWallPos;

public:
	SteelStage(Sprite* spSprite,  TankTiledMap* pMap, float fMaxTime);

	virtual ~SteelStage();

	//�ӵ�ͼ�л�ȡ����
	bool initSteelPosFromMap();

	//���õ�ͼ��gid
	bool setHomeOtherGid(int gid);

	//����
	virtual void update(float dt) override;

	virtual void onExit() override;

	virtual void onEnter(Player* pPlayer) override;
};

#endif