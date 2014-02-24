//
//  ShaderSprite.h
//  Match
//
//  Created by ricky stone on 14-2-8.
//
//

#ifndef Match_ShaderSprite_h
#define Match_ShaderSprite_h


#include "CCSprite.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCCustomCommand.h"
#include "cocos2d.h"

USING_NS_CC;

template <class spriteType>
class ShaderSpriteCreator
{
public:
    static spriteType* createSprite(const std::string& filename)
    {
        spriteType* ret = spriteType::create();
        ret->setTexture(filename);
        ret->initShader();
        ret->setBackgroundNotification();
        return ret;
    }
};

class ShaderSprite : public cocos2d::Sprite
{
public:
    ShaderSprite();
    ~ShaderSprite();
    
    virtual void initShader();
    void setBackgroundNotification();
    
    void draw();
    void listenBackToForeground(Object *obj);
    
protected:
    virtual void buildCustomUniforms() = 0;
    virtual void setCustomUniforms() = 0;
protected:
    std::string _fragSourceFile;
    
protected:
    cocos2d::CustomCommand _renderCommand;
    void onDraw();
    
};

class GreyScaleSprite : public ShaderSprite, public ShaderSpriteCreator<GreyScaleSprite>
{
public:
    CREATE_FUNC(GreyScaleSprite);
    GreyScaleSprite();
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

class BlurSprite : public ShaderSprite, public ShaderSpriteCreator<BlurSprite>
{
public:
    CREATE_FUNC(BlurSprite);
    BlurSprite();
    void setBlurSize(float f);
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
protected:
    Point blur_;
    GLfloat    sub_[4];
    GLuint    blurLocation;
    GLuint    subLocation;
};

#endif
