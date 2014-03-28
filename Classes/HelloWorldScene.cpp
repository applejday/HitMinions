#include "HelloWorldScene.h"

int HelloWorld::hit=0;
int HelloWorld::hitPos=0;
int HelloWorld::score=0;
int HelloWorld::life=5;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	scoreLabel = LabelTTF::create("Score :","Arial", 24);
    
    // position the label on the center of the screen
    scoreLabel->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - scoreLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(scoreLabel, 1);

	this->schedule(schedule_selector(HelloWorld::UpdateScore), 0.5f);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("play/background.jpg");
	sprite->setScaleX(visibleSize.width/sprite->getContentSize().width);
	sprite->setScaleX(visibleSize.height/sprite->getContentSize().height);
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	mainMinion = new MainMinion(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
	
	this->addChild(mainMinion->sprite,2);
	
    time = 0;
    
	this->vt=8.0f;
	auto pinkMinion = new PinkMinion(2,this->vt,1);
	this->addChild(pinkMinion);
	auto yellowMinion = new YellowMinion(6,this->vt);
	this->addChild(yellowMinion);
	/*this->removeFromParentAndCleanup(true);*/
	auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule(schedule_selector(HelloWorld::TurnManage), 2);

    return true;
}

void HelloWorld::TurnManage(float dt)
{
    log("call new turn");
    if(time<50)
    {
        /*
         int n=rand()%4;*/
        int a,p1,p2,p3;
        a=arc4random()%4;
        
         p1=arc4random()%8;
         do
             p2=arc4random()%8;
         while(p2==p1);
         do
             p3=arc4random()%8;
         while(p3==p1||p3==p2);
         if(a==1)
         {
             YellowMinion* yellowMinion = new YellowMinion(p1+1,this->vt);
             this->addChild(yellowMinion);
         }
         if(a!=1)
         {
             PinkMinion* pinkMinion = new PinkMinion(p2+1,this->vt,1);
             this->addChild(pinkMinion);
             PinkMinion* pink1Minion = new PinkMinion(p3+1,this->vt,1);
             this->addChild(pink1Minion);
         }
    }
    
    time++;
}

void HelloWorld::UpdateScore(float dt)
{
	scoreLabel->setString(String::createWithFormat("%d::%d", HelloWorld::score,HelloWorld::life)->getCString());
}

void HelloWorld::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{

}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *unused_event)
{
    Touch* touch = touches[0];
	Point location = touch->getLocation();
	HelloWorld::hit=1;
	if(location.x>visibleSize.width/2)
    {
        
        mainMinion->RightDown(location.y);
        if (isScheduled(schedule_selector(HelloWorld::UpdateMainMinionRight))) {
            this->unschedule(schedule_selector(HelloWorld::UpdateMainMinionRight));
        }
        this->schedule(schedule_selector(HelloWorld::UpdateMainMinionRight), 0.2f,1,0);
	}
	else
	{
		mainMinion->LeftDown(location.y);
		if (isScheduled(schedule_selector(HelloWorld::UpdateMainMinionLeft))) {
            this->unschedule(schedule_selector(HelloWorld::UpdateMainMinionLeft));
        }
        this->schedule(schedule_selector(HelloWorld::UpdateMainMinionLeft), 0.2f,1,0);
	}

}
void HelloWorld::UpdateMainMinionLeft(float dt)
{
	HelloWorld::hit=0;
	mainMinion->Left();
}

void HelloWorld::UpdateMainMinionRight(float dt)
{
	HelloWorld::hit=0;
	mainMinion->Right();
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
