#include "GameLayer.h"
#include <SimpleAudioEngine.h>

GameLayer* GameLayer::create(int roundNum)
{
	GameLayer* pRet = new GameLayer();
	if (pRet && pRet->init(roundNum))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool GameLayer::init(int roundNum)
{
	if (!Layer::init())
	{
		return false;
	}

	//����һ����ɫ����
	this->addChild(LayerColor::create(Color4B::GRAY), -100);

	//��ʼ����ͼ
	initMap(String::createWithFormat("maps/Round%d.tmx", roundNum)->getCString());

	//��ʼ��ui��
	m_pHudLayer = HudLayer::create(1, 4, 20);
	this->addChild(m_pHudLayer, 100);

	//��ʼ���˵�
	initMenu();

	//��ʼ�������¼�
	initKeyboardEvent();

	//��ʼ��̹�˹�������
	m_pTankFactory = new TankFactory(m_pMap, Vec2(1, 1));

	//��ʼ�����
	Size mapSize = m_pMap->getTiledMap()->getContentSize();
	Size tileSize = m_pMap->getTiledMap()->getTileSize();
	m_pPlayer = createPlayer(MineTankA, 1, 
		Vec2(mapSize.width / 2 - tileSize.width * 3, tileSize.height));
	m_pMap->getTiledMap()->addChild(m_pPlayer->getTank()->getSprite());


	//��ʼ��ai�������
	m_pAIMgr = new AIPlayerManager();
	m_pAIMgr->setUserTank(m_pPlayer->getTank());

	//����ai���
	m_arrAIPos.push_back(Vec2(tileSize.width, mapSize.height - tileSize.height));
	m_arrAIPos.push_back(Vec2(mapSize.width / 2, mapSize.height - tileSize.height));
	m_arrAIPos.push_back(Vec2(mapSize.width - tileSize.width, 
		mapSize.height - tileSize.height));

	for (int i = 0; i < 3; i++)
	{
		Player* pTmpPlayer = createPlayer(static_cast<TankType>(i), 2, m_arrAIPos[i]);

		m_pMap->getTiledMap()->addChild(pTmpPlayer->getTank()->getSprite());

		m_pAIMgr->addAiPlayer(pTmpPlayer);

		m_pHudLayer->setRemainEnemyNum(m_pHudLayer->getRemainEnemyNum() - 1);
	}

	//����������
	this->scheduleUpdate();

	//����ai������
	//this->schedule(schedule_selector(GameLayer::aiUpdate), 0.5f);

	//����ai������
	this->schedule(schedule_selector(GameLayer::aiCreator), 3.0f, -1, 5.0f);

	//��������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/start.aif", true);
	
	return true;
}

GameLayer::~GameLayer()
{
	m_pMap->release();
	
	CC_SAFE_DELETE(m_pPlayer);

	CC_SAFE_DELETE(m_pTankFactory);

	CC_SAFE_DELETE(m_pAIMgr);

}

void GameLayer::update(float dt)
{
	//�����������
	for (auto it = m_listKeyCode.begin();
		it != m_listKeyCode.end();
		)
	{

		KeyboardCallBack(*it);
		//����Ƿ���
		if (*it == EventKeyboard::KeyCode::KEY_J)
		{
			//ֻ����һ��
			it = m_listKeyCode.erase(it);
		}
		else
		{
			++it;
		}
	}

	m_pAIMgr->aiUpdte(this, dt);
	
	m_pAIMgr->collisionUpdate(this, dt);


}

void GameLayer::aiUpdate(float dt)
{
}

void GameLayer::aiCreator(float dt)
{
	//ֻ�ᴴ��20������
	if (0 >= m_pHudLayer->getRemainEnemyNum())
	{
		this->unschedule(schedule_selector(GameLayer::aiCreator));
	}
	//����������6��ai
	else if (6 <= m_pAIMgr->getAIPlayerNum())
	{
		return;
	}

	Player* pTmpPlayer = createPlayer(static_cast<TankType>(rand() % 4), 2, 
		m_arrAIPos[rand() % 3]);

	m_pMap->getTiledMap()->addChild(pTmpPlayer->getTank()->getSprite());

	m_pAIMgr->addAiPlayer(pTmpPlayer);

	m_pHudLayer->setRemainEnemyNum(m_pHudLayer->getRemainEnemyNum() - 1);

}

Player* GameLayer::createPlayer(const TankType& tankType, int playerType, const Vec2& vInitPos)
{
	Size tileSize = m_pMap->getTiledMap()->getTileSize();
	Player* pRet = nullptr;
	TankBase* pTankBase = m_pTankFactory->create(tankType);
	pTankBase->getSprite()->setPosition(vInitPos);
	pTankBase->setNextMoveRect(pTankBase->getSprite()->getBoundingBox());

	switch (playerType)
	{
	case 1:
		//������ͨ���
		pRet = new UserPlayer(pTankBase);
		break;
	case 2:
		//����ai���
		pRet = new AIPlayer(pTankBase);
		pTankBase->getSprite()->setRotation(180);
		break;
	}

	//��̹�����ŵ����ʴ�С
	Size tankSize = pTankBase->getSprite()->getContentSize();
	pTankBase->getSprite()->setScale((tileSize.height * 2 - 4) / (tankSize.height));

	return pRet;
}

HudLayer* GameLayer::getHudLayer()
{
	return m_pHudLayer;
}

bool GameLayer::initMap(const char* fileName)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//ʵ������ͼ����
	m_pMap = TankTiledMap::createWithTmxFile(fileName);
	m_pMap->retain();
	this->addChild(m_pMap->getTiledMap());

	m_pMap->getTiledMap()->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_pMap->getTiledMap()->setPosition(visibleSize / 2);

	//��ͼ����
	//�Ե�ͼ�������ţ��Դﵽ���¶���
	int mapHeight = m_pMap->getTiledMap()->getContentSize().height / 2;
	float scaleRate = visibleSize.height / 2 / mapHeight;
	m_pMap->getTiledMap()->setScale(scaleRate);

	//����һ����ɫ����

	//Ϊ��ͼ���Ϻ�ɫ����
	Sprite* spMapBg = Sprite::create();
	spMapBg->setTextureRect(Rect(0, 0, m_pMap->getTiledMap()->getContentSize().width * scaleRate,
		m_pMap->getTiledMap()->getContentSize().height * scaleRate));
	spMapBg->setColor(Color3B::BLACK);
	this->addChild(spMapBg, -99);
	spMapBg->setPosition(visibleSize / 2);

	return true;
}

bool GameLayer::initMenu()
{
	//������ť

	MenuItemFont* itemRight =
		MenuItemFont::create("Ri", this, menu_selector(GameLayer::RightCallBack));
	itemRight->setPosition(Vec2(130, 100));

	MenuItemFont* itemLeft =
		MenuItemFont::create("Le", this, menu_selector(GameLayer::LeftCallBack));
	itemLeft->setPosition(Vec2(50, 100));

	MenuItemFont* itemUp =
		MenuItemFont::create("Up", this, menu_selector(GameLayer::UpCallBack));
	itemUp->setPosition(Vec2(90, 150));

	MenuItemFont* itemDown =
		MenuItemFont::create("Do", this, menu_selector(GameLayer::DownCallBack));
	itemDown->setPosition(Vec2(90, 100));

//	MenuItemFont* itemRight =
//		MenuItemFont::create(yUtils::GBK2UTF("��").c_str(), this, menu_selector(GameLayer::RightCallBack));
//	itemRight->setPosition(Vec2(130, 100));
//
//	MenuItemFont* itemLeft =
//		MenuItemFont::create(yUtils::GBK2UTF("��").c_str(), this, menu_selector(GameLayer::LeftCallBack));
//	itemLeft->setPosition(Vec2(50, 100));
//
//	MenuItemFont* itemUp =
//		MenuItemFont::create(yUtils::GBK2UTF("��").c_str(), this, menu_selector(GameLayer::UpCallBack));
//	itemUp->setPosition(Vec2(90, 150));
//
//	MenuItemFont* itemDown =
//		MenuItemFont::create(yUtils::GBK2UTF("��").c_str(), this, menu_selector(GameLayer::DownCallBack));
//	itemDown->setPosition(Vec2(90, 100));

//	MenuItemFont* itemExit =
//		MenuItemFont::create(yUtils::GBK2UTF("�˳���Ϸ").c_str(),  
	MenuItemFont* itemExit =
		MenuItemFont::create("back",
		[&](Ref* ref)
	{
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif

	});
	itemExit->setPosition(Vec2(90, 400));


	MenuItemImage* fireBtn =
		MenuItemImage::create("res/fire_button_default.png",
		"res/fire_button_press.png",
		CC_CALLBACK_1(GameLayer::ShotCallBack, this));
	fireBtn->setPosition(Vec2(Director::getInstance()->getWinSize().width - fireBtn->getContentSize().width / 2 - 20, 100));

	Menu* menu = Menu::create(itemRight, itemLeft, itemUp, itemDown, itemExit, fireBtn, NULL);
	menu->setPosition(0, 0);
	menu->setAnchorPoint(Vec2(0, 0));

	this->addChild(menu);

	return true;
}

bool GameLayer::initKeyboardEvent()
{
	//��win32��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto myKeyListener = EventListenerKeyboard::create(); //�����¼����������������¼�
	//���̰�������ʱ����Ӧ
	myKeyListener->onKeyPressed = [&](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		m_listKeyCode.push_back(keycode);
	};

	myKeyListener->onKeyReleased = [&](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		m_listKeyCode.remove(keycode);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
#endif
	return true;
}

void GameLayer::LeftCallBack(Ref* ref)
{
	log("GameLayer::LeftCallBack");
	m_pPlayer->hanleInput(PlayerLeft, this);
	m_pPlayer->getTank()->move();
}

void GameLayer::RightCallBack(Ref* ref)
{
	log("GameLayer::RightCallBack");
	m_pPlayer->hanleInput(PlayerRight, this);
	m_pPlayer->getTank()->move();

}

void GameLayer::UpCallBack(Ref* ref)
{
	log("GameLayer::UpCallBack");
	m_pPlayer->hanleInput(PlayerUp, this);
	m_pPlayer->getTank()->move();
}

void GameLayer::DownCallBack(Ref* ref)
{
	log("GameLayer::DownCallBack");
	m_pPlayer->hanleInput(PlayerDown, this);
	m_pPlayer->getTank()->move();
}

void GameLayer::ShotCallBack(Ref* ref)
{
	log("GameLayer::ShotCallBack");
	m_pPlayer->hanleInput(PlayerShot, this);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/bullet.aif");
}

void GameLayer::KeyboardCallBack(EventKeyboard::KeyCode keyCode)
{
	//��onKeyPress��new���ڱ����ͷ�
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		//left
		LeftCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		//right
		RightCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		//up
		UpCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		//down
		DownCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_J:
		//shot
		ShotCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_K:
		break;
	}

}
