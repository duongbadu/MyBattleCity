#ifndef _AIPlayerManager_H_
#define _AIPlayerManager_H_

#include "AIPlayer.h"
#include "Bullet\BulletBase.h"
#include "Tank\EnemyTank.h"


class AIPlayerManager
{
private:
	//ai�������
	std::list<Player*> m_listAIPlayer;

	//�û�������̹��
	TankBase* m_pUserTank;

public:
	AIPlayerManager();

	~AIPlayerManager();

	//���һ��ai��ҵ���������
	void addAiPlayer(Player* pPlayer);

	//ai����
	void aiUpdte(Layer* layer, float dt);

	//��ײ������
	void collisionUpdate(Layer* layer, float dt);

	//�����û�������̹��
	void setUserTank(TankBase* pUserTank);

	//��ȡai�����Ŀ
	size_t getAIPlayerNum() const;

};

#endif