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

	//�����ײ��trueΪ��ײ��falseΪ����ײ������һ��Vec&�� ���ԶԵ�ǰλ�ý����������Ż��û�����
	bool isCollision(const Rect& tankBoundingBox, Vec2& offsetPos);
};



#endif
