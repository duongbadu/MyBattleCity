#ifndef _Player_H_
#define _Player_H_

#include "Tank\TankBase.h"
#include "PlayerState.h"
#include "Map\TankTiledMap.h"
#include "yUtils\MemPool\SimpleMemPool.h"

/**
*	@class : player
*	@brief : ������ƽӿ�, ��������ҿ����࣬��ai������
*/
class  Player
{
protected:
	//������̹��ʵ��
	TankBase* m_pTank;

	//״̬ģʽָ��
	PlayerState* m_pState;

	//״̬ģʽ�ڴ��
	SimpleMemPool<PlayerState> m_memPoolState;

public:
	Player(TankBase* pTank);

	//����������
	virtual ~Player();

	//�ַ�������Ϣ
	virtual void hanleInput(const PlayerInputType& type, Layer* layer);

	//ÿһ֡���߼�����������
	virtual void update(Layer* layer, float dt);

	//��ȡ״̬�ڴ��
	SimpleMemPool<PlayerState>& getStateMemPool();

	//��ȡ̹��ʵ��
	TankBase* getTank();
};
#endif