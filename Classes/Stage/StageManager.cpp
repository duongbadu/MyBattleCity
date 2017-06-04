#include "StageManager.h"

StageManager::StageManager()
	:m_bIsCanCreate(true),
	m_bIsCollision(false)
{
	m_pStageBase = new NullStage();
}

StageManager::~StageManager()
{

	CC_SAFE_DELETE(m_pStageBase);
}

void StageManager::update(Player* pPlayer, float dt)
{
	//����Ѿ���ײ�ˣ�����Ҫ��ײ�����
	if (m_bIsCollision)
	{
		m_pStageBase->getSprite()->setVisible(false);
		if (!m_pStageBase->isOver())
		{
			m_pStageBase->update(dt);
		}
		else
		{
			m_bIsCanCreate = true;
		}
	}
	//���������ײ���
	else
	{
		CollisionTest(pPlayer);
	}
	
}

std::vector<Vec2>& StageManager::getRandomPosArr()
{
	return m_arrRandomPos;
}

void StageManager::pushPos(const Vec2& randomPos)
{
	m_arrRandomPos.push_back(randomPos);
}

void StageManager::createStage(TankTiledMap* pMap)
{
	if (!m_bIsCanCreate)
	{
		return;
	}
	//�����˳�����
	m_pStageBase->onExit();
	//�����ڴ�
	delete m_pStageBase;
	m_pStageBase = nullptr;

	int iRandNum = rand() % 2 + 1;

	//��ʱֻ����StageStell
	switch (iRandNum)
	{
	case StageSteel: 
		m_pStageBase = new SteelStage(Sprite::create("item/steel.png"), pMap, 10.0f);
		break;
	case StageActive:
		m_pStageBase = new ActiveStage(Sprite::create("item/active.png"), pMap, 10.0f);
		break;
	case StageStar:
		break;
	case StageTimer: 
		break;
	case StageBomb: 
		break;
	}


	//��ʼ������
	m_bIsCanCreate = false;
	m_bIsCollision = false;

	//����λ��
	pMap->getTiledMap()->addChild(m_pStageBase->getSprite());

	//���ȡһ��λ��
	m_pStageBase->getSprite()->setPosition(m_arrRandomPos[rand() % m_arrRandomPos.size()]);
}

void StageManager::CollisionTest(Player* pPlayer)
{
	//�����ײ
	if (StageNull != m_pStageBase->getStageType() &&
		pPlayer->getTank()->getSprite()->getBoundingBox().intersectsRect(
		m_pStageBase->getSprite()->getBoundingBox()))
	{
		m_bIsCollision = true;
		//���н������
		m_pStageBase->onEnter(pPlayer);
	}
}
