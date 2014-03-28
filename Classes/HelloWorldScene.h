#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MainMinion.h"
#include "PinkMinion.h"
#include "YellowMinion.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void UpdateMainMinionLeft(float dt);
	void UpdateMainMinionRight(float dt);
	void UpdateScore(float dt);
    void TurnManage(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	MainMinion *mainMinion;
	Size visibleSize;
	Point origin;
	float vt;
	LabelTTF *scoreLabel;
public:
	static int hit;
	static int hitPos;
	static int score;
	static int life;
    int time;
};

#endif // __HELLOWORLD_SCENE_H__
