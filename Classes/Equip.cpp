#include "Equip.h"


Equip::Equip(int p, float vt,int type)
{
	if(type==1)
		sprite = Sprite::create("tim1_up.png");
	else if(type==2)
		sprite = Sprite::create("tim1_up.png");
	if(type==3)
		sprite = Sprite::create("tim1_up.png");
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
		y=121;
	else if(p==2||p==6)
		y=272;
	else if(p==3||p==7)
		y=423;
	else if(p==4||p==8)
		y=574;
	sprite->setPosition(Point(x, y));
	Director::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(PinkMinion::update),this,0.1f,false);
}

void Equip::Update(float dt)
{
//	sprite->setPosition(Point(sprite->getPositionX()+vt, sprite->getPositionY()));
//	if(live==true&&(vt>0&&sprite->getPositionX()>Director::getInstance()->getVisibleSize().width/2||
//		vt<0&&sprite->getPositionX()<Director::getInstance()->getVisibleSize().width/2))
//	{
//		live=false;
//	}
//	if(HelloWorld::hit==1&&live==true)
//		if(HelloWorld::hitPos==this->p)
//			{
//				live=false;
//				if(this->type==1)
//					HelloWorld::life+=1;
//				else if(this->type==2)
//					HelloWorld::score+=500;
//				else if(this->type==3)
//					HelloWorld::life=0;
//			}
}
    

void Equip::OnDie(float dt)
{
}

Equip::~Equip(void)
{
}
