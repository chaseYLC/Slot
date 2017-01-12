#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SystemConfig.h"
#include "SCTitle.h"

USING_NS_CC;

int _gTest = 0;

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
//bool HelloWorld::init()
//{
//    //////////////////////////////
//    // 1. super init first
//    if ( !Layer::init() )
//    {
//        return false;
//    }
//    
//
//    //auto visibleSize = Director::getInstance()->getVisibleSize();
//    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    ///////////////////////////////
//    //// 2. add a menu item with "X" image, which is clicked to quit the program
//    ////    you may modify it.
//
//    //// add a "close" icon to exit the progress. it's an autorelease object
//    //auto closeItem = MenuItemImage::create(
//    //                                       "CloseNormal.png",
//    //                                       "CloseSelected.png",
//    //                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    //
//    //closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//    //                            origin.y + closeItem->getContentSize().height/2));
//
//    //// create menu, it's an autorelease object
//    //auto menu = Menu::create(closeItem, NULL);
//    //menu->setPosition(Vec2::ZERO);
//    //this->addChild(menu, 1);
//
//    ///////////////////////////////
//    //// 3. add your codes below...
//
//    //// add a label shows "Hello World"
//    //// create and initialize a label
//    //
//    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    //
//    //// position the label on the center of the screen
//    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
//    //                        origin.y + visibleSize.height - label->getContentSize().height));
//
//    //// add the label as a child to this layer
//    //this->addChild(label, 1);
//
//    //// add "HelloWorld" splash screen"
//    //auto sprite = Sprite::create("HelloWorld.png");
//
//    //// position the sprite on the center of the screen
//    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    //// add the sprite as a child to this layer
//    //this->addChild(sprite, 0);
//    //
//    //return true;
//}

bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	m_asyncLoader = 0;

	m_asyncLoader = AsyncResourceLoader::create();
	m_asyncLoader->addLoadImage("company_logo.png");
	/*m_asyncLoader->start(this, callfuncO_selector(HelloWorld::asyncResourceCallback), this, false);*/
	m_asyncLoader->start(this, SEL_CallFuncO(&HelloWorld::asyncResourceCallback), this, false);
	this->addChild(m_asyncLoader);

	return true; 
}


void HelloWorld::menuCloseCallback(/*Ref* pSender*/)
{
	/*SND()->playBackgroundMusic(SoundPath::path(SoundPath::ST_BG_START), true);
	SND()->setBackgroundMusicVolume(0.5);*/

	if (_gTest)
	{
		//ClearClothesScene *gameTitleScene = ClearClothesScene::create();
		//CCDirector::sharedDirector()->setDepthTest(true);
		//CCDirector::sharedDirector()->replaceScene(gameTitleScene);
	}
	else
	{
		GameTitleScene *gameTitleScene = GameTitleScene::create();
		Director::getInstance()->setDepthTest(true);
		Director::getInstance()->replaceScene(gameTitleScene);
	}
	
	
	return;

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::asyncResourceCallback(cocos2d::Ref *obj)
{
	m_asyncLoader->removeFromParentAndCleanup(true);
	Size winSize = SystemConfig::getWinSize();
	Sprite *bg = Sprite::create("company_logo.png");
	bg->setPosition(cocos2d::Vec2(winSize.width / 2, winSize.height / 2));
	//    SystemConfig::setPosition(480, 960, bg);
	this->addChild(bg);

	bg->setOpacity(0);
	FiniteTimeAction *actions;
	if (_gTest)
	{
		actions = Sequence::create(
			CallFunc::create(CC_CALLBACK_0(HelloWorld::menuCloseCallback, this)),
			NULL
		);
	}
	else {
		actions = Sequence::create(
			FadeIn::create(2),
			FadeOut::create(1),
			//CallFuncN::create(this, SEL_CallFuncN(&HelloWorld::menuCloseCallback)),
			CallFunc::create(CC_CALLBACK_0(HelloWorld::menuCloseCallback, this)),
			NULL
		);
	}

	bg->runAction(actions);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
}

void HelloWorld::onExit()
{
	Layer::onExit();
	TextureCache::sharedTextureCache()->removeAllTextures();
}