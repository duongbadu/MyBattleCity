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

	//ȥ����ָ���������λ�ã�����arrPos�е�λ��
	int findMinDisPos(int arrGid[], int iArrSize, int iRota);

public:
	//ȷ����ͼ��layer_0 �� layer_1 ������
	static TankTiledMap* createWithTmxFile(const std::string& fileName);

	bool initWithTmxFile(const std::string& fileName);

	//��ȡ��Ƭ��ͼ����
	TMXTiledMap* getTiledMap();

	/**
	*	@brief : ������ײ���
	*	@param tankBoundingBox : ̹�˵���ײ������
	*	@param offfsetPos : ���ڻش���ƫ���������isUseOffsetΪfalse���򲻻�ش�
	*	@param isUseOffset : �Ƿ�ʹ��ƫ��������
	*	@param iRota : ��ǰ��ת�ķ���
	*	@return : ���������ײ������true, ���δ������ײ������false
	*/
	bool isCollision(const Rect& tankBoundingBox, Vec2& offsetPos, bool isUseOffset, int iRota = 0);
};



#endif
