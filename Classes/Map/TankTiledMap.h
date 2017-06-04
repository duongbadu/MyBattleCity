#ifndef _TankTiledMap_H_
#define _TankTiledMap_H_

#include <cocos2d.h>
#include "Common\Common.h"
USING_NS_CC;

/**
*	@class : TankTiledMap
*	@brief : Ϊ̹�˴�ս�ĵ�ͼ���Ƶĵ�ͼ�࣬����̹�˵���ײ���
*/

class TankTiledMap : public Ref
{
private:
	//��Ƭ��ͼ����
	TMXTiledMap* m_pMap;

	//��ͼ��0
	TMXLayer* m_pLayer0;

	//��ͼ��1
	TMXLayer* m_pLayer1;

public:
	//ȷ����ͼ��layer_0 �� layer_1 ������
	static TankTiledMap* createWithTmxFile(const std::string& fileName);

	bool initWithTmxFile(const std::string& fileName);

	//��ȡ��Ƭ��ͼ����
	TMXTiledMap* getTiledMap();

	//�����ײ��trueΪ��ײ��falseΪ����ײ, ����ָ����ײ����
	template <typename CollisionFunc>
	bool isCollision(const Rect& tankBoundingBox, CollisionFunc func = [=](int gid){return gid != 0; });
};



template <typename CollisionFunc>
bool TankTiledMap::isCollision(const Rect& tankBoundingBox, CollisionFunc func)
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

	//̹��ֻռ��4������
	//����ֻ�ý���4���������ײ���

	//1.1 ��ȡ���Ͻ�tileMapGid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)));

	//log("collision1 gid : %d", gid); 

	//1.2 �ж�gid�Ƿ�Ϊ�գ���������ֵ
	if (func(gid))
	{
		return true;
	}

	//2.1 ��ȡ���Ͻǵ�gid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)));
	//log("collision2 gid : %d", gid);

	//2.2 
	if (func(gid))
	{
		return true;
	}

	//3.1 ��ȡ���½�gid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)));
	//log("collision3 gid : %d", gid);

	//3.2
	if (func(gid))
	{
		return true;
	}

	//4.1 ��ȡ���½�gid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)));
	//log("collision4 gid : %d", gid);

	//4.2
	if (func(gid))
	{
		return true;
	}

	return false;
}

#endif
