//
//  MainMenuScene.h
//  HitMinions
//
//  Created by thang nguyen on 3/27/14.
//
//

#ifndef __HitMinions__MainMenuScene__
#define __HitMinions__MainMenuScene__

#include "cocos2d.h"

USING_NS_CC;

class MainMenuScene : public Layer {
private:
    MenuItemImage* helpDialog;
    MenuItemImage* infoDialog;
    Sprite* minionSpr;
    
public:
    static Scene* createScene();
    virtual bool init();
    void onButtonClick(Object* sender);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    void resumeActionMinion(float dt);
    
    CREATE_FUNC(MainMenuScene);
};

#endif /* defined(__HitMinions__MainMenuScene__) */
