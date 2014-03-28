//
//  MainMenuScene.cpp
//  HitMinions
//
//  Created by thang nguyen on 3/27/14.
//
//

#include "MainMenuScene.h"
#include "OptionScene.h"
#include "GameScene.h"

enum BUTTON_TAG{
    HELP_BTN = 0,
    INFO_BTN = 1,
    PLAY_BTN = 2,
    SETTING_BTN = 3,
    HELP_DIALOG = 4,
    INFO_DIALOG = 5
};


Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto mainMenuLayer = MainMenuScene::create();
    scene->addChild(mainMenuLayer);
    return scene;
}

bool MainMenuScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create("start/play.jpg");
    bg->setPosition(Point(size.width/2, size.height/2));
    this->addChild(bg);
    
    auto helpItem = MenuItemImage::create("start/help1.png", "start/help2.png", CC_CALLBACK_1(MainMenuScene::onButtonClick, this));
    helpItem->setTag(HELP_BTN);
    helpItem->setPosition(Point(helpItem->getContentSize().width, size.height- helpItem->getContentSize().height));
    auto infoItem = MenuItemImage::create("start/info1.png","start/info2.png", CC_CALLBACK_1(MainMenuScene::onButtonClick, this));
    infoItem->setTag(INFO_BTN);
    infoItem->setPosition(Point(size.width - infoItem->getContentSize().width, size.height - infoItem->getContentSize().height));
    auto menu1 = Menu::create(helpItem, infoItem, NULL);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
    
    auto settingItem = MenuItemImage::create("start/option1.png", "start/option2.png", CC_CALLBACK_1(MainMenuScene::onButtonClick, this));
    settingItem->setTag(SETTING_BTN);
    auto playItem = MenuItemImage::create("start/play1.png", "start/play2.png", CC_CALLBACK_1(MainMenuScene::onButtonClick, this));
    playItem->setTag(PLAY_BTN);
    auto menu2 = Menu::create(playItem, settingItem, NULL);
    menu2->setPosition(Point(size.width/2, size.height/2));
    menu2->alignItemsVerticallyWithPadding(-15);
    this->addChild(menu2);
    
    /* them hinh minion dong */
    Vector<SpriteFrame*> animFrames(3);
    auto spriteFrame = SpriteFrame::create("start/minion1.png", Rect(0, 0, 308, 431));
    animFrames.pushBack(spriteFrame);
    auto spriteFrame1 = SpriteFrame::create("start/minion2.png", Rect(0, 0, 308, 431));
    animFrames.pushBack(spriteFrame1);
    auto spriteFrame2 = SpriteFrame::create("start/minion3.png", Rect(0, 0, 308, 431));
    animFrames.pushBack(spriteFrame2);
    auto spriteFrame3 = SpriteFrame::create("start/minion4.png", Rect(0, 0, 308, 431));
    animFrames.pushBack(spriteFrame3);
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f);
    auto sprite = Sprite::createWithSpriteFrame(spriteFrame);
    sprite->setPosition(Point(200, 200));
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
    this->addChild(sprite);
    
    /* help dialog */
    helpDialog = MenuItemImage::create("start/help.png","start/help.png", CC_CALLBACK_1(MainMenuScene::onButtonClick, this));
    helpDialog->setTag(HELP_DIALOG);
    helpDialog->setVisible(false);
    auto m1 = Menu::create(helpDialog, NULL);
    m1->setPosition(Point(size.width/2, size.height/2));
    this->addChild(m1);
    
    /* info dialog */
    infoDialog = MenuItemImage::create("start/info.png","start/info.png", CC_CALLBACK_1(MainMenuScene::onButtonClick, this));
    infoDialog->setTag(INFO_DIALOG);
    infoDialog->setVisible(false);
    auto m2 = Menu::create(infoDialog, NULL);
    m2->setPosition(Point(size.width/2, size.height/2));
    this->addChild(m2);

    
    return true;
}

void MainMenuScene::onButtonClick(Object* sender)
{
    MenuItemImage* item = (MenuItemImage*) sender;
    if (item) {
        switch (item->getTag()) {
            case HELP_BTN:
                helpDialog->setVisible(true);
                break;
            case INFO_BTN:
                infoDialog->setVisible(true);
                break;
            case PLAY_BTN:{
                auto gameScene = GameScene::createScene();
                Director::getInstance()->pushScene(TransitionCrossFade::create(0.3, gameScene));
                break;
            }
            case SETTING_BTN:{
                auto optScene = OptionScene::createScene();
                Director::getInstance()->pushScene(TransitionCrossFade::create(0.3, optScene));
                break;
            }
            case HELP_DIALOG:
                helpDialog->setVisible(false);
                break;
            case INFO_DIALOG:
                infoDialog->setVisible(false);
                break;
            default:
                break;
        }
    }
}