//
//  Minion.h
//  HitMinions
//
//  Created by thang nguyen on 3/28/14.
//
//

#ifndef __HitMinions__Minion__
#define __HitMinions__Minion__

#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class Minion : public Node {
    
    
public:
//    virtual bool initWithRayAndVelocity(const char* fileName, int p, int vt);
    virtual bool initWith(const char* fileName, int ray, int velocity, int hp, int type);
    
    void removeMinion();
    
    Sprite *sprite;
	float vt;
	int p;
	bool live;
	int hp;
    int typeAnimation;
    /**
     kieu cua Minion
     @value:
     type = 1 : loai A
     type = 2 : loai B
     type = 3 : loai C
     */
    int type;
};

#endif /* defined(__HitMinions__Minion__) */
