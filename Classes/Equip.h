#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;
class Equip : public Node
{
public:
	Equip(int p,float vt,int type);
	
	void OnDie(float dt);
	void Update(float dt);
	~Equip(void);
public:
	Sprite *sprite;
	float vt;
	int p;
	bool live;
	int type;

};

