//
//  XTCSGameScene.hpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/16.
//

#ifndef XTCSNAKE_XTCSGAMESCENE_H
#define XTCSNAKE_XTCSGAMESCENE_H

#include "cocos2d.h"
#include "ui/UIButton.h"

#include "XTCSMap.hpp"

class CTCSGameScene : public cocos2d::Scene
{
public:
    static CTCSGameScene* create();
    virtual ~CTCSGameScene();
    bool init()override;
    // 应用进入后台
    virtual void EnterBackGround();
    // 应用进入前台
    virtual void EnterForeGround();
    
protected:
    CTCSGameScene();
protected:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
};

class CTCSGameLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(CTCSGameLayer)
    ~CTCSGameLayer();
protected:
    virtual bool init() override;
    
    virtual void onEnter() override;
    
    virtual void onExit() override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void initUI();
    
    void btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type);
    
    virtual void update(float dt) override;
    
    void updateScore(int score);
    
    void pauseCallback(int type);
    
    void gameOverCallback(int type);
    
    void showGameOverCallback(int score);
private:
    //背景
    //cocos2d::Sprite* m_spr_bg_ptr{ nullptr };
    //操作杆
    //cocos2d::Sprite* m_spr_opRod_ptr{ nullptr };
    //遥感按钮
    //cocos2d::ui::Button* m_btn_opRod_ptr{ nullptr };
    
    int m_i_score {0};
    
    cocos2d::Label* m_lb_score_ptr {nullptr};
    
    cocos2d::Vec2 m_vec2_touchBeginPos {-1, -1};
    
    cocos2d::Vec2 m_vec2_touchEndPos {-1, -1};
    
    CTCSMap* m_cTCSMap_map_ptr;
    
    cocos2d::ui::Button* m_btn_up_ptr;
    
    cocos2d::ui::Button* m_btn_down_ptr;
    
    cocos2d::ui::Button* m_btn_left_ptr;
    
    cocos2d::ui::Button* m_btn_right_ptr;
};


#endif /* XTCSNAKE_XTCSGAMESCENE_H */
