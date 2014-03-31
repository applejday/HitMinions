//
//  GameScene.h
//  HitMinions
//
//  Created by thang nguyen on 3/27/14.
//
//

#ifndef __HitMinions__GameScene__
#define __HitMinions__GameScene__

#include "cocos2d.h"
#include "MainMinion.h"

USING_NS_CC;

class GameScene: public Layer{
private:
    LabelTTF* scoreLabel;
    LabelTTF* scoreResultLabel;
    LabelTTF* highScoreResultLabel;
    LabelTTF* numOfMinionsIsHited;
    MenuItemImage* resultView;
    Array* liveSprites;
    Vector<Node*> actionManager;
    Vector<Object*> schedulerManager;
    
    int lives;
    int scores;

    CC_SYNTHESIZE(int, numMinionHited, NumMinionHited);
    
    /**
     variable for game logic
     */
    MainMinion *mainMinion;
	Size size;
	Point origin;
	float vt;
    int currentTurn;
    int a,p1,p2,p3;
    bool isFinish;
    
public:
    static Scene* createScene();
    virtual bool init();
    
    void onButtonClick(Object* sender);
    void updateScore(int value);
    void updateLives(int value);
    void showResultView(Node* sender);
    
    /**
     Game logic
     */
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void updateMainMinionLeft(float dt);
	void updateMainMinionRight(float dt);
	void updateScore(float dt);
    void turnManage(float dt);
    int getTimeByTurn(int turn);
    void resumeTurnManage();
    
    static int hit;
	static int hitPos;

    int time;
    
    CREATE_FUNC(GameScene);
};


#endif /* defined(__HitMinions__GameScene__) */
