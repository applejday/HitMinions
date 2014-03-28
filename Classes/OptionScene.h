//
//  OptionScene.h
//  HitMinions
//
//  Created by thang nguyen on 3/27/14.
//
//

#ifndef __HitMinions__OptionScene__
#define __HitMinions__OptionScene__

#include "cocos2d.h"
USING_NS_CC;

class OptionScene: public Layer{
    
private:
    MenuItemImage* soundItem;
    
public:
    static Scene* createScene();
    virtual bool init();
    
    void onButtonClick(Object* sender);
    
    CREATE_FUNC(OptionScene);
};

#endif /* defined(__HitMinions__OptionScene__) */
