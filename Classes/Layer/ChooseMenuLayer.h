#ifndef _ChooseMenuLayer_H_
#define _ChooseMenuLayer_H_

#include <cocos2d.h>
#include <cocos-ext.h>
USING_NS_CC;
USING_NS_CC_EXT;

/**
*	@class : ChooseMenuLayer
*	@brief : ����ѡ���ͼ
*/
class ChooseMenuLayer : public Layer,
	public TableViewDataSource,
	public TableViewDelegate
{
private:
	//��������ö���
	ValueMap m_vConfig;

	std::vector<TMXTiledMap*> m_arrMap;

public:
	static Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(ChooseMenuLayer);


	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) override;

	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override{}
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) override{}
};


#endif