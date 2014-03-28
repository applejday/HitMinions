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
USING_NS_CC;

class GameScene: public Layer{
private:
    LabelTTF* scoreLabel;
    Array* liveSprites;
    int lives;
    int scores;
    
public:
    static Scene* createScene();
    virtual bool init();
    
    void onButtonClick(Object* sender);
    void updateScore(int value);
    void updateLives(int value);
    
    CREATE_FUNC(GameScene);
};


#endif /* defined(__HitMinions__GameScene__) */
