#include "Equip.h"
#include "SimpleAudioEngine.h"
#include "GameMediator.h"

Equip::Equip(int p, float vt,int type)
{
	if(type==1){
		sprite = Sprite::create("icon/banana.png");
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/banana.mp3");
    }else if(type==2){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/cream.mp3");
		sprite = Sprite::create("icon/cream.png");
    }
    
	if(type==3)
		sprite = Sprite::create("icon/poison.png");
	live=true;
	this->vt = vt;
	this->p=p;
	this->type =type;
	int x,y;
	if(p<5)
			x=0;
	else
		{
			x=Director::getInstance()->getVisibleSize().width;
			this->vt*=-1;
		}
	if(p==1||p==5)
		y= 94;
	else if(p==2||p==6)
		y=248;
	else if(p==3||p==7)
		y=393;
	else if(p==4||p==8)
		y=544;
	sprite->setPosition(Point(x, y));
    this->addChild(sprite);
	Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(Equip::update),this,0.1f,false);
}

void Equip::update(float dt)
{
    sprite->setPosition(Point(sprite->getPositionX()+vt, sprite->getPositionY()));
	if(live==true &&
       ((vt>0 && sprite->getPositionX()>Director::getInstance()->getVisibleSize().width/2 - 60)||
		(vt<0 && sprite->getPositionX()<Director::getInstance()->getVisibleSize().width/2 + 60)))
	{
		live=false;
        auto scaleMinion = ScaleTo::create(0.5f, 0.5f);
        sprite->runAction(Sequence::create(scaleMinion, CallFuncN::create(CC_CALLBACK_1(Equip::removeFromParent, this)), NULL));
	}
	if(GameScene::hit == 1 && live == true)
		if(GameScene::hitPos == this->p)
			if(live == true && ((vt>0&&sprite->getPositionX()>Director::getInstance()->getVisibleSize().width/2-202)||
                                (vt<0&&sprite->getPositionX()<Director::getInstance()->getVisibleSize().width/2+202)))
			{
				live=false;
				this->vt=0;
                if(this->type==1){
                    sprite->setTexture("icon/banana2.png");
					GameMediator::shareInstance()->getGameLayer()->updateLives(1);
                    Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(Equip::removeSelf),this, 2.0f,0,1.0f,false);
                }else if(this->type==2){
                    sprite->setTexture("icon/cream2.png");
					GameMediator::shareInstance()->getGameLayer()->updateScore(5);
                    Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(Equip::removeSelf),this, 2.0f,0,1.0f,false);
				}else if(this->type==3){
                    sprite->setTexture("icon/poison2.png");
                    sprite->runAction(Sequence::create(ScaleTo::create(3.0f, 1.5), CallFuncN::create(CC_CALLBACK_1(Equip::finishGame, this)), NULL));
                    
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/poison.mp3");
                }
			}
}
void Equip::finishGame(Node* node)
{
    GameMediator::shareInstance()->getGameLayer()->updateLives(-10);
    Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(Equip::removeSelf),this, 1.0f,0,1.0f,false);
    log("call finish game"); 
}
void Equip::removeFromParent(Node* node)
{
    this->unscheduleUpdate();
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
    log("call remove from parent ");
}
void Equip::removeSelf(float dt)
{
    this->removeFromParent(NULL);
}

void Equip::onDie(float dt)
{
    
}

Equip::~Equip(void)
{
}
