#include "Player.h"
#include "Layer\GameLayer.h"

Player::Player(TankBase* pTank)
	:m_pTank(pTank)
{
	//�����ڴ�صĳ�ʼ����
	m_memPoolState.setCallNum(1);
	m_memPoolState.setNewFunc(PlayerState());

	//ʵ��һ����ʼ״̬
	m_pState = m_memPoolState.allocWithTag(PlayerDefaultState);
}

Player::~Player()
{
	if (m_pTank)
	{
		delete m_pTank;
	}

	m_memPoolState.clear();
}

void Player::hanleInput(const PlayerInputType& type, Layer* layer)
{
	//��ȡ��״̬
	PlayerState* pNewState = m_pState->handleInput(*this, layer, type);

	//�����ȡ����״̬
	if (pNewState)
	{
		//����״̬�����ڴ����
		m_memPoolState.release(m_pState);

		//�л�����״̬
		m_pState = pNewState;

		//����onEnter() ����
		m_pState->onEnter(*this, layer);
	}
}

void Player::update(Layer* layer, float dt)
{
	m_pState->update(*this);
}

SimpleMemPool<PlayerState>& Player::getStateMemPool()
{
	return m_memPoolState;
}

TankBase* Player::getTank()
{
	return m_pTank;
}