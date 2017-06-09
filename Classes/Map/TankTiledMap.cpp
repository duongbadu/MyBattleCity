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



int TankTiledMap::findMinDisPos( int arrGid[], int iArrSize, int iRota)
{
	/**
	0 1
	2 3
	**/

	int iFirst = 0;
	int iSecond = 0;


	switch (iRota)
	{
	case 0:
		iFirst = 0;
		iSecond = 1;
		break;
	case 90:
		iFirst = 1;
		iSecond = 3;
		break;
	case 180:
		iFirst = 2;
		iSecond = 3;
		break;
	case 270:
		iFirst = 0;
		iSecond = 2;
		break;

	}

	if ((arrGid[iFirst] == 0 && arrGid[iSecond] == 0) ||
		(arrGid[iFirst] != 0 && arrGid[iSecond] != 0))
	{
		//ȫΪ��ͬ
		return -1;
	}
	else if (arrGid[iFirst] != 0 && arrGid[iSecond] == 0)
	{
		return iFirst;
	}
	else if (arrGid[iFirst] == 0 && arrGid[iSecond] != 0)
	{
		return iSecond;
	}

	return -1;
}


bool TankTiledMap::isCollision(const Rect& tankBoundingBox, Vec2& offsetPos, bool isUseOffset, int iRota)
{
	//log("isCollision");
	int gid = 0;
	//��ͼ��С
	Size mapSize = m_pMap->getContentSize();
	//ÿһƬ��Ƭ�Ĵ�С
	Size tileSize = m_pMap->getTileSize();
	//��������ײ������û�аѶԽǵ��ĸ����ж���
	bool bIsCollAndNotFinal = false;

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

	int arrGid[8] = {};

	//����arrVec
	for (int i = 0; i < 8; i++)
	{
		gid = m_pLayer0->getTileGIDAt(arrVec[i]);
		arrGid[i] = gid;
		if (gid != 0 || bIsCollAndNotFinal)
		{
			//�������������
			if (!isUseOffset)
			{
				//ֱ�ӷ���
				return true;
			}
			else if (3 > i)
			{
				//���û���ж����������ң��򲻽�������
				bIsCollAndNotFinal = true;
				continue;
			}

			//��ȡ̹���е�λ��
			Vec2 vecMidPos = Vec2(
				static_cast<int>(tankBoundingBox.getMidX() / tileSize.width),
				static_cast<int>(midY / tileSize.height));

			//��ȡ��ײ�����ײ��
			int iBuf = findMinDisPos(arrGid, 4, iRota);

			//������
			if (iBuf < 0)
			{
				return true;
			}

			//log("index : %d", iBuf);
			
			offsetPos = Vec2(
				vecMidPos.x- arrVec[iBuf].x,
				arrVec[iBuf].y - vecMidPos.y
				);

			//�������y����
			if (0 == iRota || 180 == iRota)
			{
				offsetPos.y = 0;
			} 
			else if (90 == iRota || 270 == iRota)
			{
				//x����
				offsetPos.x = 0;
			}

			//log("before normalize : offsetPos : %0.2f , %0.2f", offsetPos.x, offsetPos.y);

			//����һ��ƫ�����ļ���
			return true;
		}
	}

	return false;
}