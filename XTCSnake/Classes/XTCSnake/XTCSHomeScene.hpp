//
//  XTCSHomeScene.hpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/19.
//

#ifndef XTCSNAKE_XTCSHOMESCENE_H
#define XTCSNAKE_XTCSHOMESCENE_H

#include "cocos2d.h"
#include "ui/UIButton.h"

class CTCSHomeScene : public cocos2d::Scene
{
public:
    static CTCSHomeScene* create();
    virtual ~CTCSHomeScene();
    bool init()override;
    // 应用进入后台
    virtual void EnterBackGround();
    // 应用进入前台
    virtual void EnterForeGround();
    
protected:
    CTCSHomeScene();
protected:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
};

class CTCSHomeLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(CTCSHomeLayer)
    
    ~CTCSHomeLayer();
    
private:
    CTCSHomeLayer();
    
    virtual bool init() override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void initUI();
    
    void btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type);
    
    //virtual void update(float dt) override;
    void initSnake();
    
private:

};

#endif /* XTCSNAKE_XTCSHOMESCENE_H */
