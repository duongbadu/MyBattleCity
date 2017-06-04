#ifndef _StageBase_H_
#define _StageBase_H_

#include <cocos2d.h>
#include "Map\TankTiledMap.h"
#include "Player\Player.h"
USING_NS_CC;

//��������ö��
typedef enum
{
	StageNull,
	StageSteel,
	StageActive,
	StageStar,
	StageTimer,
	StageBomb
}StageType;

/**
*	@class : StageBase
*	@brief : ���߻���
*/
class StageBase
{
protected:
	//���߾���
	Sprite* m_spStage;

	//��������
	StageType m_eStageType;

	//��ǰ�������ĵ�ͼ
	TankTiledMap* m_pMap;

	//��ǰ����Ч���Ƿ����
	bool m_bIsOver;

public: 
	
	StageBase(Sprite* spSprite, const StageType& type, TankTiledMap* pMap);

	virtual ~StageBase();

	//��ȡ���߾���
	Sprite* getSprite();

	//���õ�������
	void setStageType(const StageType& type);

	//��ȡ��������
	StageType getStageType() const;

	//ÿһ֡����
	virtual void update(float dt) = 0; 

	//������Ч������ʱ���еĲ���
	virtual void onExit();

	//������Ч����ʼʱ���еĲ���
	virtual void onEnter(Player* pPlayer);

	//����Ч���Ƿ����
	bool isOver() const;

};
#endif