#ifndef __gameTest__AsyncResourceLoader__
#define __gameTest__AsyncResourceLoader__

#include <vector>
#include <string>
#include "cocos2d.h"

USING_NS_CC;

#define ASYNC_LOADER_USE_THREAD         false
#define ASYNC_LOADER_DISPLAY            true

typedef void* (*ASYNC_RESOURCE_LOADER_CALLBACK)(void* pParam);

class AsyncResourceLoader : public cocos2d::Node
{
protected :
    Ref* target;
    SEL_CallFuncO selector;
    std::vector<std::string> imageVector;
    int loadedImageCount;
    bool useThread;
    void loadingCallBack(cocos2d::Ref * obj);
public :
    AsyncResourceLoader();
    ~AsyncResourceLoader();

    bool init();
    CREATE_FUNC(AsyncResourceLoader);   

    void runCallback(void);
    bool addLoadImage(const std::string & imageName);
    bool start( Ref * target, SEL_CallFuncO selector, void* pParam, bool isDisplay = true, bool useThread = false);
};
#endif /* defined(__gameTest__AsyncResourceLoader__) */
