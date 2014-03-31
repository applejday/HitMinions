#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Equip : public Node
{
public:
	Equip(int p,float vt,int type);
	
	void onDie(float dt);
	void update(float dt);
    void removeFromParent(Node* node);
	void removeSelf(float dt);
    void finishGame(Node* node);
	~Equip(void);
public:
	Sprite *sprite;
	float vt;
	int p;
	bool live;
	int type;

};

