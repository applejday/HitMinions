#pragma once
#include "cocos2d.h"
#include "Minion.h"
#include "GameScene.h"

USING_NS_CC;

class YellowMinion : public Minion
{
public:
    static YellowMinion* create(int ray, float vt, int hp, int type);
    bool initWith(const char* fileName, int ray, int velocity, int hp, int type);
	void update(float dt);
    void removeFromParent(Node* node);
	void removeSelf(float dt);
	void changeRay(int p);
	~YellowMinion(void);
};

