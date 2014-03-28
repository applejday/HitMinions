//
//  GameScene.cpp
//  HitMinions
//
//  Created by thang nguyen on 3/27/14.
//
//

#include "GameScene.h"

enum GAME_BUTTON{
    EXIT_BTN = 0,
    BACK_BTN = 1
};


Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("play/background.jpg");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg);
    
    /* back button */
    auto backItem = MenuItemImage::create("play/undo1.png", "play/undo2.png", CC_CALLBACK_1(GameScene::onButtonClick, this));
    backItem->setTag(BACK_BTN);
    backItem->setPosition(Point(backItem->getContentSize().width, size.height - backItem->getContentSize().height/2));
    
    /* exit button */
    auto exitItem = MenuItemImage::create("play/cancel1.png", "play/cancel2.png", CC_CALLBACK_1(GameScene::onButtonClick, this));
    exitItem->setTag(EXIT_BTN);
    exitItem->setPosition(Point(size.width - exitItem->getContentSize().width, size.height - exitItem->getContentSize().height/2));
    
    auto menu = Menu::create(backItem, exitItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    /* Score label */
    scoreLabel = LabelTTF::create("345", "fonts/Softplain.ttf", 100);
    scoreLabel->setPosition(size.width/2, size.height - scoreLabel->getContentSize().height/2);
    scoreLabel->setColor(Color3B(242, 196, 13));
    this->addChild(scoreLabel);
    
    /* lives image */
    liveSprites = Array::createWithCapacity(5);
    for (int i =0 ; i < 5; i++) {
        auto sprite = Sprite::create("play/gold1.png");
        sprite->setTag(i);
        sprite->setPosition(Point(250 + i*sprite->getContentSize().width, size.height - sprite->getContentSize().height));
        this->addChild(sprite);
        liveSprites->addObject(sprite);
    }
    lives = 5;
    
    return true;
}

void GameScene::onButtonClick(cocos2d::Object *sender)
{
    MenuItemImage* item = (MenuItemImage*) sender;
    if (item) {
        switch (item->getTag()) {
            case EXIT_BTN:
                break;
            case BACK_BTN:
                Director::getInstance()->popScene();
                break;
            default:
                break;
        }
    }

}

void GameScene::updateLives(int value)
{
    lives += value;
    for (int i = 4; i >= lives; i--) {
        Sprite* spr = (Sprite*)liveSprites->getObjectAtIndex(i);
        spr->setTexture("play/gold2.png");
    }
}

void GameScene::updateScore(int value)
{
    scores += value;
    scoreLabel->setString(String::createWithFormat("%d", scores)->getCString());
}
