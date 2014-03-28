#include "PinkMinion.h"
#include "GameMediator.h"

PinkMinion* PinkMinion::create(int ray, float vt, int hp, int type)
{
    PinkMinion* pinkMinion = new PinkMinion;
    if (pinkMinion && pinkMinion->initWith("play/tim1_up.png", ray, vt, hp, type )) {
        pinkMinion->autorelease();
        return pinkMinion;
    }
    CC_SAFE_DELETE(pinkMinion);
    return NULL;
}

bool PinkMinion::initWith(const char* fileName, int ray, int velocity, int hp, int type)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Minion::initWith(fileName, ray, velocity, hp, type));
        Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(PinkMinion::update),this,0.1f,false);
        
        bRet = true;
    } while (0);
    return bRet;
}
void PinkMinion::update(float dt)
{
	sprite->runAction(MoveTo::create(0.0f, Point(sprite->getPositionX()+vt, sprite->getPositionY())));
	if(live == true && ((vt>0 && sprite->getPositionX()> Director::getInstance()->getVisibleSize().width/2 - 60)||
		(vt<0 && sprite->getPositionX()< Director::getInstance()->getVisibleSize().width/2 + 60)))
	{
		live=false;
        GameMediator::shareInstance()->getGameLayer()->updateLives(-1);
		auto scaleMinion = ScaleTo::create(0.5f, 0.4f);
        sprite->runAction(Sequence::create(scaleMinion, CallFuncN::create(CC_CALLBACK_1(PinkMinion::removeFromParent, this)), NULL));
	}
    if (this->type == 2) {
        if (((vt > 0 && sprite->getPositionX() > 300) ||
             (vt < 0 && sprite->getPositionX() < 900)) && !isChangeRay) {
            isChangeRay = true;
            changeRay();
        }
        
    }
	if(GameScene::hit==1&&live==true)
		if(GameScene::hitPos==this->p)
			if(live==true&&((vt>0&&sprite->getPositionX()>Director::getInstance()->getVisibleSize().width/2-202)||
		(vt<0&&sprite->getPositionX()<Director::getInstance()->getVisibleSize().width/2 + 202)))
			{
				if(hp>1)
				{
					hp--;
				}
				else
				{
					live=false;
                    GameMediator::shareInstance()->getGameLayer()->updateScore(100);
					sprite->setTexture("play/tim1_down.png");
					this->vt=0;
					Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(PinkMinion::removeSelf),this, 1.0f,0,1.0f,false);
				}
			}
			
}
void PinkMinion::removeFromParent(cocos2d::Node *node)
{
    removeMinion();
}
void PinkMinion::removeSelf(float dt)
{
    removeMinion();
}
void PinkMinion::changeRay()
{
//    log("call change ray");
    switch (arc4random()%2) {
        case 0:
            p = p + 1;
            if (p == 5) {
                p = 1;
            }
            if (p == 9){
                p = 5;
            }
            break;
        case 1:
            p = p - 1;
            if (p == 0) {
                p = 4;
            }
            if (p == 4){
                p = 8;
            }
            break;
        default:
            break;
    }
    int y;
    if(p==1||p==5)
		y=121;
	else if(p==2||p==6)
		y=272;
	else if(p==3||p==7)
		y=423;
	else if(p==4||p==8)
		y=574;
    sprite->runAction(MoveTo::create(0.5f, Point(sprite->getPositionX(), y)));
}

PinkMinion::~PinkMinion(void)
{
}
