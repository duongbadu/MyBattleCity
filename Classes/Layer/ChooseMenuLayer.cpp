#include "ChooseMenuLayer.h"
#include "MenuLayer.h"
#include "GameLayer.h"

Scene* ChooseMenuLayer::createScene()
{
	Scene* scene = Scene::create();

	ChooseMenuLayer* layer = ChooseMenuLayer::create();

	scene->addChild(layer);

	return scene;
}

bool ChooseMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//��ȡ����
	m_vConfig = FileUtils::getInstance()->getValueMapFromFile("Config/ChooseMenuConfig.xml");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//����һ��talbleview ��datasource����Ϊ��ǰ����Ķ��� tableview����ʾ�����СΪ 
	TableView* tableView = TableView::create(this, Size(m_vConfig["TableViewShowWidth"].asInt(),
		m_vConfig["TableViewShowHeight"].asInt()));
	//����tableviewΪˮƽ����  ScrollView::Direction::VERTICAL Ϊ��ֱ,ScrollView::Direction::HORIZONTAL Ϊˮƽ
	tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	//����λ��
	tableView->setPosition(m_vConfig["TableViewPosX"].asInt(), m_vConfig["TableViewPosY"].asInt());
	//���ô������
	tableView->setDelegate(this);
	// ���˳��
	//tableView->setVerticalFillOrder(TableView::VerticalFillOrder::BOTTOM_UP);
	//���tableview����ǰlayer
	this->addChild(tableView);
	//����tableview
	tableView->reloadData();

	//�������ذ�ť
	MenuItemFont* itemBackMenu = MenuItemFont::create("Back", [&](Ref* ref)
	{
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});
	itemBackMenu->setPosition(visibleSize.width - itemBackMenu->getContentSize().width / 2,
		itemBackMenu->getContentSize().height);

	Menu* menu = Menu::create(itemBackMenu, NULL);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);

	//��������
	Label* selectLabel = Label::create();
	selectLabel->setString(m_vConfig["SelectLabel"].asString());
	selectLabel->setSystemFontSize(m_vConfig["FontSize"].asInt());
	selectLabel->setPosition(tableView->getBoundingBox().getMidX() - 10,
		tableView->getBoundingBox().getMaxY() + selectLabel->getContentSize().height + 10);
	this->addChild(selectLabel);

	return true;
}



void ChooseMenuLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	Scene* scene = Scene::create();
	GameLayer* layer = GameLayer::create(cell->getIdx() + 1);
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

Size ChooseMenuLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(m_vConfig["SmallWidth"].asInt(),
		m_vConfig["SmallHeight"].asInt());
}

TableViewCell* ChooseMenuLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	std::string szBuf = CCString::createWithFormat("Round %d", idx + 1)->getCString();
	
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new (std::nothrow) TableViewCell();
		cell->autorelease();

		//��������ͼ
		TMXTiledMap* pMap = TMXTiledMap::create(CCString::createWithFormat("maps/Round%d.tmx", idx + 1)->getCString());
		float rota = static_cast<float>(m_vConfig["SmallHeight"].asInt()) / pMap->getContentSize().width;
		pMap->setScale(rota);
		//pMap->setScale(0.5f);
		pMap->setPosition(Vec2::ZERO);
		pMap->setAnchorPoint(Vec2::ZERO);


		auto label = Label::createWithSystemFont(szBuf, "Helvetica", 25);
		label->setPosition(m_vConfig["SmallWidth"].asInt() / 4 - 10,
			0);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);

		cell->addChild(pMap);
		cell->addChild(label);
	}
	else
	{
		auto label = (Label*)cell->getChildByTag(123);
		label->setString(szBuf);
	}


	return cell;
}

ssize_t ChooseMenuLayer::numberOfCellsInTableView(TableView *table)
{
	return m_vConfig["MaxMapCount"].asInt();
}
