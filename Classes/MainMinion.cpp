#include "MainMinion.h"
#include "HelloWorldScene.h"
MainMinion::MainMinion(int posX,int posY)
{
	sprite = Sprite::create("play/left_up.png");
	sprite->setPosition(Point(posX, posY));
	
}

void MainMinion::Left()
{
	sprite->setTexture("play/left_up.png");
}

void MainMinion::Right()
{
	//sprite->setTexture(TextureCache::sharedTextureCache()->addImage("right.png"));	
	sprite->setTexture("play/right_up.png");
}
void MainMinion::LeftDown(int posY)
{
	int y;
	sprite->setTexture("play/left_down.png");
	if(posY>16&&posY<=167)
		{
			y=131;
			GameScene::hitPos=1;
		}
	else if(posY>167&&posY<=318)
		{
			y=282;
			GameScene::hitPos=2;
		}
	else if(posY>318&&posY<=469)
		{
			y=433;
			GameScene::hitPos=3;
		}
	else if(posY>469&&posY<=628)
		{
			y=584;
			GameScene::hitPos=4;
		}
	sprite->setPosition(Point(sprite->getPositionX(),y));

}
void MainMinion::RightDown(int posY)
{
	int y;
	sprite->setTexture("play/right_down.png");
	if(posY>16&&posY<=167)
		{
			y=131;
			GameScene::hitPos=5;
		}
	else if(posY>167&&posY<=318)
		{
			y=282;
			GameScene::hitPos=6;
		}
	else if(posY>318&&posY<=469)
		{
			y=433;
			GameScene::hitPos=7;
		}
	else if(posY>469&&posY<=628)
		{
			y=584;
			GameScene::hitPos=8;
		}
	sprite->setPosition(Point(sprite->getPositionX(),y));
	
}

MainMinion::~MainMinion(void)
{
}
