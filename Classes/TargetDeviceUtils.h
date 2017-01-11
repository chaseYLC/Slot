#ifndef  _TARGET_DEVICE_UTILS_
#define  _TARGET_DEVICE_UTILS_

#include "cocos2d.h"

enum RelativeToType { RELATIVE_TO_BEST, RELATIVE_TO_FIT };

class TargetDeviceUtils
{
public :

    // Indicates if the current platform is an Android device
    static inline bool isAndroid() 
    { 
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
            return true; 
        #else 
            return false; 
        #endif 
    }

    
    // Indicates if the current paltform is an iOS device
    static inline bool isIOS()
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
            return true; 
        #else 
            return false; 
        #endif 
    }

        
    // Indicates if the current platform is the BlackBerry PlayBook device
    static inline bool isWin32() 
    { 
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
            return true; 
        #else 
            return false; 
        #endif 
    }
    
    // Gets the scale size relative to a fixed size wireframe design
//    static inline float getScaleRelativeToDesignWireframe(RelativeToType relativeTo)
//    {
//        cocos2d::CCSize WIREFRAME_DIMENSIONS = cocos2d::CCSizeMake(320, 480);
//        //Calculate ratios
//        cocos2d::CCSize screenSize = cocos2d::CCDirector::sharedDirector()->getWinSizeInPixels();
//        float widthRatio = screenSize.width / WIREFRAME_DIMENSIONS.width;
//        float heightRatio = screenSize.height / WIREFRAME_DIMENSIONS.height;
//        
//        switch(relativeTo)
//        {
//            case RELATIVE_TO_BEST:
//                return widthRatio > heightRatio ? heightRatio : widthRatio;
//                break;
//        }
//        return 1;
//    }


    static inline bool enableRetinaDisplay(bool b, RelativeToType rType)
    {
        cocos2d::Size screenSize = cocos2d::Director::getInstance()->getWinSizeInPixels();        
//        float fFrameScale = 1;
//        if( screenSize.width > 480 ) fFrameScale = 2;
//        else fFrameScale = 1;
//        
//        cocos2d::CCSize WIREFRAME_DIMENSIONS = cocos2d::CCSizeMake(320*fFrameScale, 480*fFrameScale);
        cocos2d::Size WIREFRAME_DIMENSIONS = cocos2d::Size(640, 960);
        cocos2d::Size frameSize;
        //Calculate ratios

//        float widthRatio = screenSize.width/WIREFRAME_DIMENSIONS.width;
//        float heightRatio = screenSize.height/WIREFRAME_DIMENSIONS.height;
        float bestRation = screenSize.width / WIREFRAME_DIMENSIONS.width;
        bool bRet = false;
        switch (rType ) {
            case RELATIVE_TO_BEST :
            {
                frameSize.width = screenSize.width;
                frameSize.height = WIREFRAME_DIMENSIONS.height*bestRation;
                CCLOG( "frame : %f %f ---- ", frameSize.width, frameSize.height );
            }
                break;

            case RELATIVE_TO_FIT :
            default:
                frameSize.width = screenSize.width;
                frameSize.height = screenSize.height;                
                break;
        }
        
	
		cocos2d::Director::getInstance()->getOpenGLView()->setFrameSize(frameSize.width, frameSize.height);
		cocos2d::Director::getInstance()->getOpenGLView()->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
		/*cocos2d::GLView::sharedOpenGLView()->setFrameSize(frameSize.width, frameSize.height);
		cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionShowAll);*/
        bRet = true;
//        cocos2d::CCEGLView::sharedOpenGLView()->setFrameSize(640, 960);
//        if( bestRation == 2 )
//        {
//        	CCLOG( "setDesignResolutionSize 640x960");
//            cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960*bestRation, kResolutionNoBorder);
//            bRet = true;
//
//        } else {
//        	CCLOG( "setDesignResolutionSize 320x480");
//            cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960*bestRation, kResolutionNoBorder);
//            bRet = true;
////            cocos2d::CCEGLView::sharedOpenGLView()->setDesignResolutionSize(320, 480*bestRation,kResolutionExactFit);
//            bRet = false;
//        }
        
        return bRet;
    }
    
    // Gets the point in the screen relative to a fixed size wireframe design
    static inline cocos2d::Point relativeCCPointMake( float x, float y )
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
        return cocos2d::Vec2(x, y);
#else 
        return cocos2d::Vec2(x*2, y*2);
#endif
    }
    
};
#endif // _TARGET_DEVICE_UTILS_
