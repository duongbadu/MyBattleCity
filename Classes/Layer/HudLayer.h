#ifndef _HudLayer_H_
#define _HudLayer_H_

#include <cocos2d.h>
USING_NS_CC;

class HudLayer : public Layer
{
private:
	//��δ�����ĵо�����Ŀ���̶�����
	int m_iEnemyNum;

	//��ǰ��δ�����ĵо���Ŀ
	int m_iCurEnemyNum;

	//δ�����о��б�ĵ�һ����ʾ��λ��
	Vec2 m_vFirstEnemyPos;

	//������ʾδ�����ĵо�
	std::vector<Sprite*> m_arrEnemySp;


	//��ǰ��ҵĵ÷�
	int m_iScore;

	//��ǰ��ҵ÷�Label,������ʾ
	Label* m_pScoreLabel;

	//��ǰ�Ĺؿ��ȼ�
	int m_iCurLevel;

	//��ǰ�Ĺؿ��ȼ���������ʾ
	Label* m_pCurLevel;

	//���ʣ�µ�������Ŀ
	int m_iLife;

	//��ǰ���ʣ���������������ʾ
	Label* m_pLifeLabel;

	//�Ƿ����������
	bool m_bIsUpdata;


	//ˢ�µ�ǰ����ʾ������
	void flushShow();

public:
	static HudLayer* create(int iCurLevel, int iLife, int iEnemyNum);

	bool init(int iCurLevel, int iLife, int iEnemyNum);

	virtual void update(float dt) override;

	//��ȡʣ�µĵо���Ŀ
	int getRemainEnemyNum() const
	{
		return m_iCurEnemyNum;
	}

	//����ʣ�µĵо���Ŀ
	void setRemainEnemyNum(int iEnemyNum)
	{
		m_iCurEnemyNum = iEnemyNum;
		m_bIsUpdata = true;
	}

	//��ȡ��ǰ��ҵĵ÷�
	int getScore() const
	{
		return m_iScore;
	}

	//���õ�ǰ��ҵĵ÷�
	void setScore(int iScore)
	{
		m_iScore = iScore;
		m_bIsUpdata = true;
	}

	//��ȡ��ǰ�ؿ��ȼ�
	int getCurLevel() const
	{
		return m_iCurLevel;
	}

	//���õ�ǰ�ؿ��ȼ�
	void setCurLevel(int iCurLevel)
	{
		m_iCurLevel = iCurLevel;
		m_bIsUpdata = true;
	}

	//������ҵ�������
	int getLifeNum() const
	{
		return m_iLife;
	}

	//��ȡ��ҵ�������Ŀ
	void setLifeNum(int iLife)
	{
		m_iLife = iLife;
		m_bIsUpdata = true;
	}

	//��ȡδ�����о��б�ĵ�һ����ʾ��λ��
	Vec2 getFirstEnemyPos() const
	{
		return m_vFirstEnemyPos;
	}

	void setFirstEnemyPos(const Vec2& pos)
	{
		m_vFirstEnemyPos = pos;
		m_bIsUpdata = true;
	}


};

#endif