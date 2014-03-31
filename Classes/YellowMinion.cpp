#include "YellowMinion.h"
#include "GameMediator.h"
#include "SimpleAudioEngine.h"

YellowMinion* YellowMinion::create(int ray, float vt, int hp, int type)
{
    YellowMinion* yellowMinion = new YellowMinion;
    if (yellowMinion && yellowMinion->initWith("icon/vang1.png", ray, vt, hp, type)) {
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
		this->typeAnimation = arc4random()%5;
		const char* s="";
		const char* s1="";
		if(this->typeAnimation==0)
		{		
			s="icon/vang1.png";
			s1="icon/vang2.png";
		}
		else if(this->typeAnimation==1)
		{
			s="icon/vang4.png";
			s1="icon/vang5.png";
		}
		else if(this->typeAnimation==2)
		{
			s="icon/vang7.png";
			s1="icon/vang8.png";
		}
		else if(this->typeAnimation==3)
		{
			s="icon/vang10.png";
			s1="icon/vang11.png";
		}
		else if(this->typeAnimation==4)
		{
			
			s="icon/vang13.png";
			s1="icon/vang14.png";
		}
		Vector<SpriteFrame*> animFrames(2);
		auto spriteFrame = SpriteFrame::create(s, Rect(0, 0, 110, 130));
		animFrames.pushBack(spriteFrame);
		auto spriteFrame1 = SpriteFrame::create(s1, Rect(0, 0, 110, 130));
		animFrames.pushBack(spriteFrame1);  
		auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f);
		this->sprite->runAction(RepeatForever::create(Animate::create(animation)));
        //Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(YellowMinion::update),this,0.1f,false);
        
        schedule(schedule_selector(YellowMinion::update), 0.1f);
        
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
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/no.mp3");
				const char* s="";
				if(this->typeAnimation==0)
				{		
					s="icon/vang3.png";
				}
				else if(this->typeAnimation==1)
				{
					s="icon/vang6.png";
				}
				else if(this->typeAnimation==2)
				{
					s="icon/vang9.png";
				}
				else if(this->typeAnimation==3)
				{
					s="icon/vang12.png";
				}
				else if(this->typeAnimation==4)
				{		
					s="icon/vang15.png";
				}
				this->sprite->stopAllActions();
				sprite->setTexture(s);
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
