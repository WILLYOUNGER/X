//
//  XTCSCommLayer.hpp
//  XTCSnake
//
//  Created by Will Young on 2022/10/1.
//

#ifndef XTCSNAKE_XTCSCOMMLAYER_H
#define XTCSNAKE_XTCSCOMMLAYER_H

#include "cocos2d.h"
#include "ui/UIButton.h"

#include "XTCSSoundManager.hpp"

class CTCSDialogBase : public cocos2d::Layer
{
public:
    CREATE_FUNC(CTCSDialogBase)
    
    ~CTCSDialogBase();
    
    void setCallback(std::function<void(int)> cb);
protected:
    CTCSDialogBase();
    
    virtual bool init() override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    virtual void initUI();

protected:
    std::function<void(int)> m_callback;
};

class CTCSPauseDialog : public CTCSDialogBase
{
public:
    CREATE_FUNC(CTCSPauseDialog)
    
    ~CTCSPauseDialog();
    
private:
    CTCSPauseDialog();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type);
    
    virtual bool init() override;
    
    virtual void initUI() override;

private:
    
};

class CTCSGameOverDialog : public CTCSDialogBase
{
public:
    static CTCSGameOverDialog* create(int score);
    
    ~CTCSGameOverDialog();
    
private:
    CTCSGameOverDialog();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type);
    
    bool init(int score);
    
    virtual void initUI() override;

private:
    int m_i_score;
};

class CTCSChartsDialog : public CTCSDialogBase
{
public:
    CREATE_FUNC(CTCSChartsDialog)
    
    ~CTCSChartsDialog();
    
private:
    CTCSChartsDialog();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type);
    
    virtual bool init() override;
    
    virtual void initUI() override;

private:

};

#endif /* XTCSNAKE_XTCSCOMMLAYER_H */
