#ifndef _PlayerState_H_
#define _PlayerState_H_

#include <cocos2d.h>

class Player;
class GameLayer;

//player��������
typedef enum
{
	PlayerDefaultState,
	PlayerDown,
	PlayerUp,
	PlayerLeft,
	PlayerRight,
	PlayerShot
}PlayerInputType;

class PlayerStateDown;
class PlayerStateUp;
class PlayerStateLeft;
class PlayerStateRight;
class PlayerStateShot;

/**
*	@class : PlayerState
*	@brief : ���״̬����
*	@warnning : ʹ��������Ϊ�˱�֤���Էǿ�
*/
class PlayerState
{
public:
	//��������, ������״̬
	virtual PlayerState* handleInput(Player& player, cocos2d::Layer* layer, const PlayerInputType& type);

	//ÿһ֡���߹̶�ʱ�����
	virtual void update(Player& player);

	//ÿ���л�״̬ʱ����
	virtual void onEnter(Player& player, cocos2d::Layer* layer);

	//����������
	virtual ~PlayerState();

	//״̬��ļ򵥹���,�����ڴ�ص��½��ڴ�
	PlayerState* operator()(size_t type) const;
};

/**
*	@class : PlayerStateDown
*	@brief : ����������µ�״̬
*/
class PlayerStateDown : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateUp
*	@brief : ����������ϵ�״̬
*/
class PlayerStateUp : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateLeft
*	@brief : ������������״̬
*/
class PlayerStateLeft : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateRight
*	@brief : ����������ҵ�״̬
*/
class PlayerStateRight : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateShot
*	@brief : ������������״̬
*/
class PlayerStateShot : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};



#endif