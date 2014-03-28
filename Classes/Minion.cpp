//
//  Minion.cpp
//  HitMinions
//
//  Created by thang nguyen on 3/28/14.
//
//

#include "Minion.h"

bool Minion::initWith(const char *fileName, int ray, int velocity, int hp, int type)
{
    sprite = Sprite::create(fileName);
	live=true;
	this->vt = velocity;
	this->p= ray;
	this->hp =hp;
    this->type = type;
	int x,y;
	if(p<5)
        x=0;
	else
    {
        x=Director::getInstance()->getVisibleSize().width;
        this->vt*=-1;
    }
    if (type == 3) {
        if (vt > 0) {
            vt += 10;
        }else
            vt -= 10;
    }
	if(p==1||p==5)
		y=121;
	else if(p==2||p==6)
		y=272;
	else if(p==3||p==7)
		y=423;
	else if(p==4||p==8)
		y=574;
	sprite->setPosition(Point(x, y));
	this->addChild(sprite);
    return true;
}

void Minion::removeMinion()
{
    this->unscheduleUpdate();
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
}