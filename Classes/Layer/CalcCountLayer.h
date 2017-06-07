#ifndef _CalcCountLayer_H_
#define _CalcCountLayer_H_

#include <cocos2d.h>
#include "yUtils/Helper/yUtils.h"
USING_NS_CC;

/**
*	@class : CalcCountLayer
*	@brief : �������
*/
class CalcCountLayer : public Layer
{
private:
	//������
	int m_iScore;

	//��ǰ�ؿ�
	int m_iCurLevel;

	//���ؿ���Ŀ
	static int m_iMaxLevelCount;

	//�������ò���
	ValueMap m_vConfig;
public:
	static Scene* createScene(int iScore, int iCurLevel);

	bool init(int iScore, int iCurLevel);

	static CalcCountLayer* create(int iScore, int iCurLevel);

	//�������Ĺؿ���Ŀ,�����ж��Ƿ��ܽ�����һ��
	static void setMaxLevelCount(int iCount);

	void nextLayer();
};

#endif