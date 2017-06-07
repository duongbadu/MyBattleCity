#include "TankTiledMap.h"

TankTiledMap* TankTiledMap::createWithTmxFile(const std::string& fileName)
{
	TankTiledMap* pRet = new TankTiledMap();
	if (pRet && pRet->initWithTmxFile(fileName))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool TankTiledMap::initWithTmxFile(const std::string& fileName)
{
	m_pMap = TMXTiledMap::create(fileName);
	m_pLayer0 = m_pMap->getLayer("layer_0");
	m_pLayer1 = m_pMap->getLayer("layer_1");
	return true;
}

TMXTiledMap* TankTiledMap::getTiledMap()
{
	return m_pMap;
}




bool TankTiledMap::isCollision(const Rect& tankBoundingBox, Vec2& offsetPos)
{
	//log("isCollision");
	int gid = 0;
	//��ͼ��С
	Size mapSize = m_pMap->getContentSize();
	//ÿһƬ��Ƭ�Ĵ�С
	Size tileSize = m_pMap->getTileSize();

	//Խ����
	if (tankBoundingBox.getMinX() < 0.01 || tankBoundingBox.getMaxX() >= mapSize.width ||
		tankBoundingBox.getMinY() < 0.01 || tankBoundingBox.getMaxY() >= mapSize.height)
	{
		return true;
	}

	//��cocos����ϵ��ת��Ϊtiled����ϵ
	int minY = mapSize.height - tankBoundingBox.getMinY();
	int maxY = mapSize.height - tankBoundingBox.getMaxY();
	int midY = mapSize.height - tankBoundingBox.getMidY();

	//��ȡ8�����������
	Vec2 arrVec[] = {
		//���Ͻ�
		Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)),

		//���Ͻ�
		Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)),

		//���½�
		Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)),

		//���½�
		Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)),

		//����
		Vec2(
		static_cast<int>(tankBoundingBox.getMidX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)),

		//����
		Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(midY / tileSize.height)),

		//����
		Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(midY / tileSize.height)),

		//����
		Vec2(
		static_cast<int>(tankBoundingBox.getMidX() / tileSize.width),
		static_cast<int>(minY / tileSize.height))
	};

	//����arrVec
	for (int i = 0; i < 8; i++)
	{
		gid = m_pLayer0->getTileGIDAt(arrVec[i]);
		if (gid != 0)
		{
//			//��������ײ��Rect
//			Rect tiledRect = Rect(
//				arrVec[i].x * tileSize.width,
//				arrVec[i].y * tileSize.height,
//				tileSize.width,
//				tileSize.height
//				);
//			//����һ����λoffset�����ظ������ߣ����õ����ߵ��ٶȽ�������
//
//			offsetPos = Vec2(tankBoundingBox.getMinX() - tiledRect.getMinX(),
//				tankBoundingBox.getMinY() - tiledRect.getMinY());
//
//			offsetPos.normalize();

			//����һ��ƫ�����ļ���
			return true;
		}
	}

	return false;
}