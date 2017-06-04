#include "SteelStage.h"

SteelStage::SteelStage(Sprite* spSprite, TankTiledMap* pMap, float fMaxTime)
	:StageBase(spSprite, StageSteel, pMap),
	m_fMaxTime(fMaxTime),
	m_fCurTimeCount(0)
{
	initSteelPosFromMap();
}

SteelStage::~SteelStage()
{
	
}

bool SteelStage::initSteelPosFromMap()
{
	assert(nullptr != m_pMap);

	TMXObjectGroup* pObjects = m_pMap->getTiledMap()->getObjectGroup("objects");


	//��ȡ��ͼ��ش�С
	Size mapSize = m_pMap->getTiledMap()->getContentSize();
	Size tiledSize = m_pMap->getTiledMap()->getTileSize();

	//��ȡ��Ӧ�Ĳ�������
	ValueMap homePos = pObjects->getObject("mapLeftDownBegin");

	//��ȡ�����tiledMap������x,y
	int x = homePos["x"].asInt() / tiledSize.width;
	int y = (mapSize.height - homePos["y"].asInt()) / tiledSize.height;

	//���뵽������

	//���ǽ
	m_arrHomeWallPos.push_back(Vec2(x, y));
	m_arrHomeWallPos.push_back(Vec2(x, y - 1));

	//�ҵ��ݶ�
	m_arrHomeWallPos.push_back(Vec2(x, y - 2));
	m_arrHomeWallPos.push_back(Vec2(x + 1, y - 2));
	m_arrHomeWallPos.push_back(Vec2(x + 2, y - 2));
	m_arrHomeWallPos.push_back(Vec2(x + 3, y - 2));

	//�ұ�ǽ
	m_arrHomeWallPos.push_back(Vec2(x + 3, y - 1));
	m_arrHomeWallPos.push_back(Vec2(x + 3, y));

	return true;
}

bool SteelStage::setHomeOtherGid(int gid)
{
	TMXLayer* pLayer = m_pMap->getTiledMap()->getLayer("layer_0");
	for (auto it : m_arrHomeWallPos)
	{
		pLayer->setTileGID(gid, it);
	}
	return true;
}

void SteelStage::update( float dt)
{
	if (m_bIsOver)
	{
		return;
	}

	m_fCurTimeCount += dt;
	//�������ʱ�����
	if (m_fCurTimeCount - m_fMaxTime >= 0.001f)
	{
		m_bIsOver = true;
		return;
	}
	else if (m_fMaxTime - m_fCurTimeCount > 0.001f &&
		m_fMaxTime - m_fCurTimeCount < m_fMaxTime / 2)
	{
		//���ʣ��ʱ����2s����
		//��ʼ��˸
		static float fFadeTime = 0;
		if (fFadeTime >= -0.001f && 
			fFadeTime < 0.001f)
		{
			//������
			setHomeOtherGid(MAP_STEEL);
		}
		else if (fFadeTime >= 0.4f)
		{
			fFadeTime = 0;
			//����ǽ��
			setHomeOtherGid(MAP_WALL);
			return;
		}

		fFadeTime += dt;
	}
	
}

void SteelStage::onExit()
{
	//���û�ǽ��
	setHomeOtherGid(MAP_WALL);
}

void SteelStage::onEnter(Player* pPlayer)
{
	//���ó���
	setHomeOtherGid(MAP_STEEL);
}
