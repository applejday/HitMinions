//
//  SplashScene.cpp
//  HitMinions
//
//  Created by thang nguyen on 3/28/14.
//
//

#include "SplashScene.h"
#include "MainMenuScene.h"

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("start/splash.jpg");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg);
    
    schedule(schedule_selector(SplashScene::goToMainMenu), 3);
    
    return true;
}

void SplashScene::goToMainMenu(float dt)
{
    Scene* mainMenu = MainMenuScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5, mainMenu));
}