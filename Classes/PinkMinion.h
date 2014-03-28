#pragma once
#include "cocos2d.h"
#include "Minion.h"

USING_NS_CC;
class PinkMinion : public Minion
{
private:
    bool isChangeRay;
public:
    static PinkMinion* create(int ray, float vt, int hp, int type);
    bool initWith(const char* fileName, int ray, int velocity, int hp, int type);
	void update(float dt);
    void removeFromParent(Node* node);
	void removeSelf(float dt);
	void changeRay();
	~PinkMinion(void);
    
};

