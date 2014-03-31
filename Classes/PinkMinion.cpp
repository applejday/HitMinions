#include "PinkMinion.h"
#include "GameMediator.h"
#include "SimpleAudioEngine.h"

PinkMinion* PinkMinion::create(int ray, float vt, int hp, int type)
{
    PinkMinion* pinkMinion = new PinkMinion;
    if (pinkMinion && pinkMinion->initWith("icon/tim1.png", ray, vt, hp, type )) {
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
		const char* s="";
		const char* s1="";
		if(this->type==1)
		{
			if(this->hp>1)
			{
				s="icon/boss1.png";
				s1="icon/boss2.png";
				this->typeAnimation=5;
				this->sprite->setAnchorPoint(Point(0.5f,0.21f));
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/boss.mp3");
			}
			else
			{
				this->typeAnimation = arc4random()%3;
                
				if(this->typeAnimation==0)
				{
					s="icon/tim1.png";
					s1="icon/tim2.png";
				}
				else if(this->typeAnimation==1)
				{
					s="icon/tim4.png";
					s1="icon/tim5.png";
				}
				else
				{
					s="icon/tim7.png";
					s1="icon/tim8.png";
				}
			}
		
		}
		else if(this->type==2)
		{
			this->typeAnimation=3;
			s="icon/tim10.png";
			s1="icon/tim11.png";
		}
		else
		{
			this->typeAnimation=4;
			s="icon/tim13.png";
			s1="icon/tim14.png";
		}
        
        float w,h;
		if(this->hp>1)
		{
			w = 189; h = 300;
		}
		else
		{
            w = 110; h = 130;
		}
		Vector<SpriteFrame*> animFrames(2);
		auto spriteFrame = SpriteFrame::create(s, Rect(0, 0, w, h));
		animFrames.pushBack(spriteFrame);
		auto spriteFrame1 = SpriteFrame::create(s1, Rect(0, 0, w, h));
		animFrames.pushBack(spriteFrame1);  
		auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f);
		this->sprite->runAction(RepeatForever::create(Animate::create(animation)));
        schedule(schedule_selector(PinkMinion::update), 0.1f);
        
        bRet = true;
    } while (0);
    return bRet;
}
void PinkMinion::update(float dt)
{
	sprite->setPosition(Point(sprite->getPositionX()+vt, sprite->getPositionY()));
	if(live == true && ((vt>0 && sprite->getPositionX()> Director::getInstance()->getVisibleSize().width/2 - 60)||
		(vt<0 && sprite->getPositionX()< Director::getInstance()->getVisibleSize().width/2 + 60)))
	{
		live=false;
        GameMediator::shareInstance()->getGameLayer()->updateLives(-1);
		auto scaleMinion = ScaleTo::create(0.5f, 0.4f);
        sprite->runAction(Sequence::create(scaleMinion, CallFuncN::create(CC_CALLBACK_1(PinkMinion::removeFromParent, this)), NULL));
        if (this->typeAnimation == 5){
            GameMediator::shareInstance()->getGameLayer()->resumeTurnManage();
        }
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
                    GameMediator::shareInstance()->getGameLayer()->updateScore(1);
                    GameMediator::shareInstance()->getGameLayer()->setNumMinionHited(GameMediator::shareInstance()->getGameLayer()->getNumMinionHited()+1);
                    if(this->typeAnimation==0)
                    {
                         sprite->setTexture("icon/tim3.png");
                    }
                    else if(this->typeAnimation==1)
                    {
                        sprite->setTexture("icon/tim6.png");
                    }
                    else if(this->typeAnimation==2)
                    {
                        sprite->setTexture("icon/tim9.png");
                    }
                    else if(this->typeAnimation==3)
                    {
                        sprite->setTexture("icon/tim12.png");
                    }
                    else if(this->typeAnimation==4)
                    {
                        sprite->setTexture("icon/tim15.png");
                    }
                    else if(this->typeAnimation==5)
                    {
                        sprite->setTexture("icon/boss3.png");
                        GameMediator::shareInstance()->getGameLayer()->updateScore(9);
                        GameMediator::shareInstance()->getGameLayer()->resumeTurnManage();
                    }
                    this->sprite->stopAllActions();
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
		y= 94;
	else if(p==2||p==6)
		y=248;
	else if(p==3||p==7)
		y=393;
	else if(p==4||p==8)
		y=544;
    sprite->runAction(MoveTo::create(0.5f, Point(sprite->getPositionX(), y)));
}

PinkMinion::~PinkMinion(void)
{
}
