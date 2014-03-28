#include "YellowMinion.h"
#include "GameMediator.h"

YellowMinion* YellowMinion::create(int ray, float vt, int hp, int type)
{
    YellowMinion* yellowMinion = new YellowMinion;
    if (yellowMinion && yellowMinion->initWith("play/vang1_up.png", ray, vt, hp, type)) {
        yellowMinion->autorelease();
        return yellowMinion;
    }
    CC_SAFE_DELETE(yellowMinion);
    return NULL;
}

bool YellowMinion::initWith(const char* fileName, int ray, int velocity, int hp, int type)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Minion::initWith(fileName, ray, velocity, hp, type));
        Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(YellowMinion::update),this,0.1f,false);
        
        bRet = true;
    } while (0);
    return bRet;
}

void YellowMinion::update(float dt)
{
	sprite->setPosition(Point(sprite->getPositionX()+vt, sprite->getPositionY()));
	if(live==true &&
       ((vt>0 && sprite->getPositionX()>Director::getInstance()->getVisibleSize().width/2 - 60)||
		(vt<0 && sprite->getPositionX()<Director::getInstance()->getVisibleSize().width/2 + 60)))
	{
		live=false;
        auto scaleMinion = ScaleTo::create(0.5f, 0.5f);
        sprite->runAction(Sequence::create(scaleMinion, CallFuncN::create(CC_CALLBACK_1(YellowMinion::removeFromParent, this)), NULL));
	}
	if(GameScene::hit == 1 && live == true)
		if(GameScene::hitPos == this->p)
			if(live == true && ((vt>0&&sprite->getPositionX()>Director::getInstance()->getVisibleSize().width/2-202)||
		(vt<0&&sprite->getPositionX()<Director::getInstance()->getVisibleSize().width/2+202)))
			{
				live=false;
                GameMediator::shareInstance()->getGameLayer()->updateLives(-1);
				sprite->setTexture("play/vang1_down.png");
				this->vt=0;
				Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(YellowMinion::removeSelf),this, 1.0f,0,1.0f,false);

			}
}
void YellowMinion::removeFromParent(Node* node)
{
    removeMinion();
}
void YellowMinion::removeSelf(float dt)
{
    removeMinion();
}
YellowMinion::~YellowMinion(void)
{
    
}
