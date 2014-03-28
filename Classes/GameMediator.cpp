//
//  GameMediator.cpp
//  CanyonDefense
//
//  Created by thang nguyen on 2/24/14.
//
//

#include "GameMediator.h"

static GameMediator _sharedContext;

GameMediator* GameMediator::shareInstance()
{
    static bool s_bFirstUse = true;
	if(s_bFirstUse){
		_sharedContext.init();
		s_bFirstUse = false;
	}
	return &_sharedContext;
}
GameMediator::~GameMediator(){
	CC_SAFE_RELEASE_NULL(_gameLayer);
}


bool GameMediator::init()
{
    bool bRet = false;
    do {
        _gameLayer = NULL;

        bRet = true;
    } while (0);
    return bRet;
}
