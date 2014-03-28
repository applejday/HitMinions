//
//  SplashScene.h
//  HitMinions
//
//  Created by thang nguyen on 3/28/14.
//
//

#ifndef __HitMinions__SplashScene__
#define __HitMinions__SplashScene__

#include "cocos2d.h"
USING_NS_CC;

class SplashScene: public Layer{
    
public:
    static Scene* createScene();
    virtual bool init();
    void goToMainMenu(float dt);
    
    CREATE_FUNC(SplashScene);
};

#endif /* defined(__HitMinions__SplashScene__) */
