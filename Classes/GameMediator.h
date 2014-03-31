//
//  GameMediator.h
//  CanyonDefense
//
//  Created by thang nguyen on 2/24/14.
//
//

#ifndef __CanyonDefense__GameMediator__
#define __CanyonDefense__GameMediator__

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class GameMediator : Object {
    
public:
    ~GameMediator();
    
    static GameMediator* shareInstance();
    bool init();
    
    CC_SYNTHESIZE_RETAIN(GameScene*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(bool, turnOffSound, TurnOffSound);

};

#endif /* defined(__CanyonDefense__GameMediator__) */
