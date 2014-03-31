//
//  OptionScene.cpp
//  HitMinions
//
//  Created by thang nguyen on 3/27/14.
//
//

#include "OptionScene.h"
#include "GameMediator.h"
#include "SimpleAudioEngine.h"

Scene* OptionScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OptionScene::create();
    scene->addChild(layer);
    return scene;
}

bool OptionScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("option/option.jpg");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg);
    
    soundItem = MenuItemImage::create("option/vol1.png","option/vol1.png", CC_CALLBACK_1(OptionScene::onButtonClick, this));
    soundItem->setTag(1);
    auto soundMenu = Menu::create(soundItem, NULL);
    soundMenu->setPosition(Point(400, 300));
    this->addChild(soundMenu);
    
    auto backItem = MenuItemImage::create("play/undo1.png", "play/undo2.png", CC_CALLBACK_1(OptionScene::onButtonClick, this));
    backItem->setTag(2);
    auto backMenu = Menu::create(backItem, NULL);
    backMenu->setPosition(Point(backItem->getContentSize().width, size.height - backItem->getContentSize().height));
    this->addChild(backMenu);
    
    return true;
}

void OptionScene::onButtonClick(Object* sender){
    MenuItemImage* item = (MenuItemImage*)sender;
    if (item) {
        switch (item->getTag()) {
            case 1:
                if (!GameMediator::shareInstance()->getTurnOffSound()) {
                    GameMediator::shareInstance()->setTurnOffSound(true);
                    soundItem->setNormalImage(Sprite::create("option/vol2.png"));
                    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
                }else{
                    GameMediator::shareInstance()->setTurnOffSound(false);
                    soundItem->setNormalImage(Sprite::create("option/vol1.png"));
                    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background.mp3");
                }
                    
                break;
            case 2:
                Director::getInstance()->popScene();
                break;
                
            default:
                break;
        }
    }
}