#ifndef _TankBase_H_
#define _TankBase_H_

#include <cocos2d.h>
#include "Map\TankTiledMap.h"
#include "Bullet\BulletManager.h"
USING_NS_CC;

/**
*	@brief : ̹�˻���
*	@class : TankBase
*/

/*
	�о�̹�˵ȼ� : ��ɫ -> ��ɫ -> ��ɫ -> ��ɫ
	�ҷ�̹�˵ȼ� : a -> b -> c 
*/
typedef enum
{
	//�з�̹��
	EnemyTankGreen,
	EnemyTankYellow,
	EnemyTankWhite,
	EnemyTankRed,

	//�ҷ�
	MineTankA,
	MineTankB,
	MineTankC
}TankType;

/**
*	��̹�˽��в�������
*/
typedef enum
{
	MoveUp = 1,
	MoveRight,
	MoveDown,
	MoveLeft,
	Shot
}TankCommandType;


class TankBase
{
protected:
	//̹�˾���
	Sprite* m_spTank;

	//̹�˵�����
	TankType m_tankType;

	//�Ƿ�����ƶ�������ײ�����ƶ��ֿ�
	//Ϊ��ai��move
	bool m_bIsCanMoved;

	//��һ���ƶ���λ��
	Rect m_rNextMoveRect;

	//̹�����ߵĵ�ͼ
	TankTiledMap* m_pMap;

	//̹�����ߵ��ٶȣ�
	//����ƶ� �� * tiledSize
	//���Ը���Ϊ��λ
	Vec2 m_vSpeed;


	//�ӵ��������
	BulletManager* m_pBulletMgr;

public:
	//�������һ�����飬Ϊ������ʹ��createWithSpriteFrame();

	TankBase(Sprite* spTank, const TankType& tankType, TankTiledMap* pMap, const Vec2& speed);

	virtual ~TankBase();

	//̹�˱�����ʱ�Ķ���
	virtual void beAtked() = 0;

	//��̹�˽��в���
	void command(const TankCommandType& type);

	//�����ƶ������õ�NextMoveRectλ��)
	void move();

	//��ȡ����
	Sprite* getSprite();

	//��ȡ̹������
	TankType getTankType() const;

	//����̹������
	void setTankType(const TankType& tankType);

	//�Ƿ�����ƶ�
	bool isCanMove() const;

	//�����Ƿ��ƶ�
	void setCanMove(bool bIsCanMove);

	//��ȡ��һ���ƶ��ĺ���
	Rect getNextMoveRect() const;

	//������һ���ƶ��ĺ���
	void setNextMoveRect(const Rect& rect);

	//�������ߵĵ�ͼ
	void setMap(TankTiledMap* pMap);

	//��ȡ���ߵĵ�ͼ
	TankTiledMap* getMap();

	//�����ƶ����ٶ�
	void setSpeed(const Vec2& speed);

	//��ȡ�ƶ����ٶ�
	Vec2 getSpeed() const;

	//��ȡ�ӵ��������
	BulletManager* getBulletMgr();
};

#endif