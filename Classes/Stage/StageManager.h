#ifndef _StageManager_H_
#define _StageManager_H_


#include "StageBase.h"
#include "NullStage.h"
#include "SteelStage.h"
#include "ActiveStage.h"
#include "Player\Player.h"

/**
*	@class : StageManager
*	@brief : ���ڵ��߹���
*/
class StageManager
{
private:
	//���߻���ָ��
	StageBase* m_pStageBase;

	//�������������λ�ü���
	std::vector<Vec2> m_arrRandomPos;

	//�Ƿ���Բ�����һ������
	bool m_bIsCanCreate;

	//�Ƿ������ײ
	bool m_bIsCollision;

public:
	StageManager();

	~StageManager();

	//���ڸ��µ���Ч��
	void update(Player* pPlayer, float dt);

	//��ȡλ�ü���
	std::vector<Vec2>& getRandomPosArr();

	//����һ��λ�õ�λ�ü�����
	void pushPos(const Vec2& randomPos);

	//������һ������
	void createStage(TankTiledMap* pMap);

	//�����Ƿ���ײ
	void CollisionTest(Player* pPlayer);
};

#endif