#pragma once
#include "cocos2d.h"

USING_NS_CC;
class MainMinion : public Node
{
public:
	MainMinion(int posX,int posY);
	void Left();
	void Right();
	void LeftDown(int posY);
	void RightDown(int posY);
	~MainMinion(void);
public:
	Sprite *sprite;
};

