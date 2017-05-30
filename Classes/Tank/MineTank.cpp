#include "MineTank.h"
#include "Layer\GameOverLayer.h"
#include <SimpleAudioEngine.h>

MineTank::~MineTank()
{

}

void MineTank::beAtked()
{
	this->m_spTank->stopAllActions();

	if (--m_iLife <= 0)
	{
		//��Ϸ����
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(GameOverLayer::createScene());
		return;
	}

	//��Ӷ����¼�
	Animate* ani = createBeAtkedAnimate(5, 0.5f);
	
	//���иö����¼�
	this->m_spTank->runAction(ani);
}

Animate* MineTank::createBeAtkedAnimate(unsigned loops, float delayTime)
{
	Animation* animation = Animation::create();

	animation->addSpriteFrameWithFile("tank/born/shield1.png");
	animation->addSpriteFrameWithFile("tank/born/shield2.png");

	animation->setLoops(loops);
	animation->setDelayPerUnit(delayTime);

	Animate* ani = Animate::create(animation);

	return ani;
}

