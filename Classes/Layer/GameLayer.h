#ifndef _GameLayer_H_
#define _GameLayer_H_

#include <cocos2d.h>
#include "Map/TankTiledMap.h"
#include "HudLayer.h"
#include "yUtils/Helper/yUtils.h"
#include "Player\UserPlayer.h"
#include "Tank\MineTank.h"
#include "Bullet\BulletBase.h"
#include "Player\AIPlayer.h"
#include "Tank\TankFactory.h"
#include "Player\AIPlayerManager.h"
USING_NS_CC;

class GameLayer : public Layer
{
private:
	//��ǰ�ؿ����
	int m_iCurRoundNum;

	//��ͼ����
	TankTiledMap* m_pMap;

	//ui��
	HudLayer* m_pHudLayer;

	//̹�˹�������
	TankFactory* m_pTankFactory;

	//��Ҷ���
	Player* m_pPlayer;

	//ai��ҹ������
	AIPlayerManager* m_pAIMgr;

	//�о����ֵ�λ������
	std::vector<Vec2> m_arrAIPos;
public:
	//roundNum : �ؿ���Ŀ��1~n
	static GameLayer* create(int roundNum);

	bool init(int roundNum);

	virtual ~GameLayer() override;

	virtual void update(float dt) override;

	//ai���£�1��1��
	void aiUpdate(float dt);

	//���ai����
	void aiCreator(float dt);

	//��ʼ����ͼ����
	bool initMap(const char* fileName);
	
	//��ʼ���˵�
	bool initMenu();

	//��ʼ�������¼�
	bool initKeyboardEvent();

	//�������,1������ң�2����ai���
	Player* createPlayer(const TankType& tankType, int playerType, const Vec2& vInitPos);

	//��ȡhud��
	HudLayer* getHudLayer();

	//��ť�ص�����
	void LeftCallBack(Ref* ref);

	void RightCallBack(Ref* ref);

	void UpCallBack(Ref* ref);

	void DownCallBack(Ref* ref);

	void ShotCallBack(Ref* ref);
};

#endif