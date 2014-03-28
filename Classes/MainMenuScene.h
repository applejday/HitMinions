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
    
public:
    static Scene* createScene();
    virtual bool init();
    void onButtonClick(Object* sender);

    CREATE_FUNC(MainMenuScene);
};

#endif /* defined(__HitMinions__MainMenuScene__) */
