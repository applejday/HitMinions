//
//  GameScene.cpp
//  HitMinions
//
//  Created by thang nguyen on 3/27/14.
//
//

#include "GameScene.h"
#include "Minion.h"
#include "PinkMinion.h"
#include "YellowMinion.h"
#include "GameMediator.h"

enum GAME_BUTTON{
    EXIT_BTN = 0,
    BACK_BTN = 1,
    RESULT_VIEW = 2
};

int GameScene::hit=0;
int GameScene::hitPos=0;


Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    GameMediator* gm = GameMediator::shareInstance();
    gm->setGameLayer(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    size = Director::getInstance()->getVisibleSize();
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
    scoreLabel = LabelTTF::create("0", "fonts/Softplain.ttf", 100);
    scoreLabel->setPosition(size.width/2, size.height - scoreLabel->getContentSize().height/2);
    scoreLabel->setColor(Color3B(242, 196, 13));
    this->addChild(scoreLabel);
    scores = 0;
    /* lives image */
    liveSprites = Array::createWithCapacity(6);
    liveSprites->retain();
    for (int i =0 ; i < 5; i++) {
        auto sprite = Sprite::create("play/gold1.png");
        sprite->setTag(i);
        sprite->setPosition(Point(250 + i*sprite->getContentSize().width, size.height - sprite->getContentSize().height));
        this->addChild(sprite);
        liveSprites->addObject(sprite);
    }
    lives = 5;
    
    /* result layer */
    
    resultView = MenuItemImage::create("play/result.png", "play/result.png", CC_CALLBACK_1(GameScene::onButtonClick, this));
    resultView->setPosition(Point(size.width/2, size.height/2));
    resultView->setVisible(false);
    resultView->setTag(RESULT_VIEW);
    numOfMinionsIsHited = LabelTTF::create("34", "fonts/UTM Facebook.ttf", 70);
    numOfMinionsIsHited->setPosition(Point(resultView->getContentSize().width/2 + 50, 515));
    numOfMinionsIsHited->setColor(Color3B(242, 196, 13));
    resultView->addChild(numOfMinionsIsHited);
    scoreResultLabel = LabelTTF::create("324", "fonts/UTM Facebook.ttf", 70);
    scoreResultLabel->setPosition(Point(resultView->getContentSize().width/2 + 50, resultView->getContentSize().height/2));
    scoreResultLabel->setColor(Color3B(242, 196, 13));
    resultView->addChild(scoreResultLabel);
    highScoreResultLabel = LabelTTF::create("343", "fonts/UTM Facebook.ttf", 70);
    highScoreResultLabel->setPosition(Point(resultView->getContentSize().width/2 + 50, 270));
    highScoreResultLabel->setColor(Color3B(242, 196, 13));
    resultView->addChild(highScoreResultLabel);
    
    auto resultMenu = Menu::create(resultView, NULL);
    resultMenu->setPosition(Point::ZERO);
    this->addChild(resultMenu, 1000);
    
    /**
     call game logic */
    
    mainMinion = new MainMinion(size.width/2 + origin.x, size.height/2 + origin.y);
	this->addChild(mainMinion->sprite,2);
	
    time = 0;
    currentTurn = 0;
	this->vt=8.0f;
    schedule(schedule_selector(GameScene::turnManage), 2);
    
    /** 
     event listener
     */
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
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
            case RESULT_VIEW:
                resultView->setVisible(false);
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
    if (lives > 0) {
        for (int i = 4; i >= lives; i--) {
            Sprite* spr = (Sprite*)liveSprites->getObjectAtIndex(i);
            spr->setTexture("play/gold2.png");
        }
    }else{
        /**finish game*/
        UserDefault* userDefault = UserDefault::getInstance();
        if (userDefault->getIntegerForKey("HIGH_SCORE", 0) < scores) {
            userDefault->setIntegerForKey("HIGH_SCORE", scores);
            userDefault->flush();
        }
        Director::getInstance()->getScheduler()->pauseAllTargets();
        Director::getInstance()->getActionManager()->pauseAllRunningActions();
        resultView->setVisible(true);
        numOfMinionsIsHited->setString(String::createWithFormat("%d", scores/100)->getCString());
        scoreResultLabel->setString(String::createWithFormat("%d", scores)->getCString());
        int highScore = userDefault->getIntegerForKey("HIGH_SCORE");
        highScoreResultLabel->setString(String::createWithFormat("%d", highScore)->getCString());
    }
    
}

void GameScene::updateScore(int value)
{
    scores += value;
    scoreLabel->setString(String::createWithFormat("%d", scores)->getCString());
}


/**
 Game Logic
*/

void GameScene::turnManage(float dt)
{
    if (time <= 0) {
        log("next turn");
        currentTurn ++;
        time = getTimeByTurn(currentTurn);
    }
    a=arc4random()%4;
    
    p1=arc4random()%8;
    do
        p2=arc4random()%8;
    while(p2==p1);
    do
        p3=arc4random()%8;
    while(p3==p1||p3==p2);
    
    switch (currentTurn) {
        case 1:{
            if(a==1)
            {
                Minion* yellowMinion = YellowMinion::create(p1+1, this->vt, 0, 1);
                this->addChild(yellowMinion);
            }else{
                /* chuot loai A - loai thuong */
                Minion* pinkMinion = PinkMinion::create(p2+1,this->vt,1, 3);
                this->addChild(pinkMinion);
                Minion* pink1Minion = PinkMinion::create(p3+1,this->vt,1, 1);
                this->addChild(pink1Minion);
            }
            break;
        }
        case 2:{
            if(a==1)
            {
                Minion* yellowMinion = YellowMinion::create(p1+1, this->vt, 0, 1);
                this->addChild(yellowMinion);
            }else{
                /* chuot loai A - loai thuong */
                Minion* pinkMinion = PinkMinion::create(p2+1,this->vt,1, 1);
                this->addChild(pinkMinion);
                /* chuot loai B - co the chuyen duong ray*/
                Minion* pink1Minion = PinkMinion::create(p3+1,this->vt,1, 2);
                this->addChild(pink1Minion);
            }
            break;
        }
        case 3:{
            if(a==1)
            {
                Minion* yellowMinion = YellowMinion::create(p1+1, this->vt, 0, 1);
                this->addChild(yellowMinion);
            }else{
                /* chuot loai A - loai thuong */
                Minion* pinkMinion = PinkMinion::create(p2+1,this->vt,1, 1);
                this->addChild(pinkMinion);
                /* chuot loai B - co the chuyen duong ray*/
                Minion* pink1Minion = PinkMinion::create(p3+1,this->vt,1, 2);
                this->addChild(pink1Minion);
                /* chuot loai C - toc do nhanh */
                Minion* pink2Minion = PinkMinion::create(p1+1,this->vt,1, 3);
                this->addChild(pink2Minion);
            }
            break;
        }


        default:
            break;
    }
    time--;
}

int GameScene::getTimeByTurn(int turn)
{
    switch (turn) {
        case 1:
            return 50;
        case 2:
            return 40;
        case 3:
            return 30;
            
        default:
            return 30;
            break;
    }
}
void GameScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event)
{
    Touch* touch = touches[0];
	Point location = touch->getLocation();
	GameScene::hit=1;
	if(location.x> size.width/2)
    {
        
        mainMinion->RightDown(location.y);
        if (isScheduled(schedule_selector(GameScene::updateMainMinionRight))) {
            this->unschedule(schedule_selector(GameScene::updateMainMinionRight));
        }
        this->schedule(schedule_selector(GameScene::updateMainMinionRight), 0.2f,1,0);
	}
	else
	{
		mainMinion->LeftDown(location.y);
		if (isScheduled(schedule_selector(GameScene::updateMainMinionLeft))) {
            this->unschedule(schedule_selector(GameScene::updateMainMinionLeft));
        }
        this->schedule(schedule_selector(GameScene::updateMainMinionLeft), 0.2f,1,0);
	}
    
}
void GameScene::updateMainMinionLeft(float dt)
{
	GameScene::hit=0;
	mainMinion->Left();
}

void GameScene::updateMainMinionRight(float dt)
{
	GameScene::hit=0;
	mainMinion->Right();
}
