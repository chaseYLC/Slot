#include "AsyncResourceLoader.h"
#include "SystemConfig.h"
#include <thread>
#include <random>
#include <ctime>

void *threadCallback(void *data)
{
    AsyncResourceLoader* parl = (AsyncResourceLoader*)data;
    parl->runCallback();
    //PoolManager::getInstance()->pop();        
    return NULL;
}

using namespace cocos2d;

AsyncResourceLoader::AsyncResourceLoader()
{
    init();
}

bool AsyncResourceLoader::init()
{
    loadedImageCount = 0;
	target = nullptr;
	selector = nullptr;
    
    return true;
}

AsyncResourceLoader::~AsyncResourceLoader()
{
    CCLOG( "AsyncResourceLoader::~AsyncResourceLoader()" );
}

bool AsyncResourceLoader::addLoadImage(const std::string& imageName)
{
    imageVector.push_back( imageName );
    return true;
}


void AsyncResourceLoader::runCallback(void)
{
    if (target && selector)
    {
        (target->*selector)(NULL);
    }
}

void AsyncResourceLoader::loadingCallBack(cocos2d::Ref *obj)
{
    loadedImageCount++;

    if( imageVector.size() == loadedImageCount )
    {
        if( useThread ){
			std::thread(&threadCallback, this).detach();
        }
		else{
            runCallback();
        }
    }
}


bool AsyncResourceLoader::start( Ref *target, SEL_CallFuncO selector, void* pParam, bool isDisplay, bool useThread )
{
	std::srand(std::time(0));

    this->target = target;
    this->selector = selector;
    this->useThread = useThread;
    
    // 화면에 로딩 이미지 출력 한다.
    if( isDisplay )
    {
        Size winSize = Director::getInstance()->getWinSize();
        
        char bgName[255];
        sprintf(bgName, "loadingBG/%d.jpg", (std::rand() % 4) + 1 );
        Sprite *bg = Sprite::create(bgName);
        bg->setPosition( ccp(winSize.width/2, winSize.height/2) );
        addChild(bg);
        
        Animation *animate;
        animate = Animation::create();
        animate->setDelayPerUnit( 0.2f );
        animate->addSpriteFrameWithFileName( "loading_1.png" );
        animate->addSpriteFrameWithFileName( "loading_2.png" );
        animate->addSpriteFrameWithFileName( "loading_3.png" );
        animate->addSpriteFrameWithFileName( "loading_4.png" );
        
        Animate *theAnimation = Animate::create( animate );
        RepeatForever *repeat = RepeatForever::create(theAnimation);
        Sprite *sprite = Sprite::create( "loading_1.png" );
        SystemConfig::setPosition( 420, 30, sprite);
        this->addChild( sprite );
        sprite->runAction( repeat );
    }
    
    for( int i = 0; i < imageVector.size(); ++i )
    {
        TextureCache::getInstance()->addImageAsync(
                imageVector[i].c_str(),
			CC_CALLBACK_1(AsyncResourceLoader::loadingCallBack, this));
    }
    
    return true;
}