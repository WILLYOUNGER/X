//
//  XTCSCommLayer.cpp
//  XTCSnake
//
//  Created by Will Young on 2022/10/1.
//

#include "XTCSCommLayer.hpp"

#include "XString.h"

#include "XTCSInfoManager.hpp"
#include "XTCSHomeScene.hpp"


USING_NS_CC;
using namespace XSTRINGTOOL;
using namespace cocos2d::ui;
using namespace std;

CTCSDialogBase::~CTCSDialogBase()
{
    
}
    
CTCSDialogBase::CTCSDialogBase()
{
    
}
    
bool CTCSDialogBase::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initUI();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CTCSDialogBase::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CTCSDialogBase::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSDialogBase::onTouchEnded, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSDialogBase::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //this->scheduleUpdate();
    
    return true;
}
    
bool CTCSDialogBase::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void CTCSDialogBase::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void CTCSDialogBase::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void CTCSDialogBase::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}
    
void CTCSDialogBase::initUI()
{
    
}

void CTCSDialogBase::setCallback(std::function<void(int)> cb)
{
    m_callback = cb;
}

CTCSPauseDialog::~CTCSPauseDialog()
{
    
}
    
CTCSPauseDialog::CTCSPauseDialog()
{
    
}
  
bool CTCSPauseDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

bool CTCSPauseDialog::init()
{
    if (!CTCSDialogBase::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CTCSPauseDialog::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CTCSPauseDialog::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSPauseDialog::onTouchEnded, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSPauseDialog::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
    
void CTCSPauseDialog::initUI()
{
    Size _size_gameSize = getTCSGameSize();
    
    //背景
    Sprite* _sp_bg_ptr = Sprite::create("TCSDialog/img_bg.png");
    this->addChild(_sp_bg_ptr, 10);
    _sp_bg_ptr->setName("sp_bg");
    _sp_bg_ptr->setPosition(_size_gameSize.width * 0.5, _size_gameSize.height * 0.6);
    
    Size _size_bgSize = _sp_bg_ptr->getContentSize();
    
    //标题
    Label* _lb_title_ptr = getTCSLabel(getTCSLanguage("tcsPauseLayer_title"), "xiangsu15.TTF", 48);
    _sp_bg_ptr->addChild(_lb_title_ptr, 10);
    _lb_title_ptr->setPosition(_size_bgSize.width * 0.5, _size_bgSize.height - 40 - _lb_title_ptr->getContentSize().height * 0.5);
    _lb_title_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    // 继续游戏
    Button* _bt_continue_ptr = Button::create("TCSCom/img_nothing.png");
    _sp_bg_ptr->addChild(_bt_continue_ptr, 10);
    _bt_continue_ptr->setName("btn_continue");
    _bt_continue_ptr->setScale9Enabled(true);
    _bt_continue_ptr->setContentSize(Size(200, 60));
    _bt_continue_ptr->setPosition(Size(_sp_bg_ptr->getContentSize().width * 0.5, _lb_title_ptr->getPositionY() - _lb_title_ptr->getContentSize().height * 0.5 - 55 - _bt_continue_ptr->getContentSize().height * 0.5));
    _bt_continue_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSPauseDialog::btnCallback, this));
    Label* _lb_continue_ptr = getTCSLabel(getTCSLanguage("tcsPauseLayer_continue"), "xiangsu15.TTF", 32);
    _bt_continue_ptr->addChild(_lb_continue_ptr, 10);
    _lb_continue_ptr->setPosition(_bt_continue_ptr->getContentSize() * 0.5);
    _lb_continue_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    // 返回首页
    Button* _bt_backHome_ptr = Button::create("TCSCom/img_nothing.png");
    _sp_bg_ptr->addChild(_bt_backHome_ptr, 10);
    _bt_backHome_ptr->setName("btn_backHome");
    _bt_backHome_ptr->setScale9Enabled(true);
    _bt_backHome_ptr->setContentSize(Size(200, 60));
    _bt_backHome_ptr->setPosition(Size(_sp_bg_ptr->getContentSize().width * 0.5, _bt_continue_ptr->getPositionY() - _bt_backHome_ptr->getContentSize().height * 0.5 - 35 - _bt_continue_ptr->getContentSize().height * 0.5));
    _bt_backHome_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSPauseDialog::btnCallback, this));
    Label* _lb_backHome_ptr = getTCSLabel(getTCSLanguage("tcsPauseLayer_backHome"), "xiangsu15.TTF", 32);
    _bt_backHome_ptr->addChild(_lb_backHome_ptr, 10);
    _lb_backHome_ptr->setPosition(_bt_backHome_ptr->getContentSize() * 0.5);
    _lb_backHome_ptr->setTextColor(Color4B(58, 56, 60, 255));

    
    // 历史排行
    Button* _bt_charts_ptr = Button::create("TCSCom/img_nothing.png");
    _sp_bg_ptr->addChild(_bt_charts_ptr, 10);
    _bt_charts_ptr->setName("btn_charts");
    _bt_charts_ptr->setScale9Enabled(true);
    _bt_charts_ptr->setContentSize(Size(200, 60));
    _bt_charts_ptr->setPosition(Size(_sp_bg_ptr->getContentSize().width * 0.5, _bt_backHome_ptr->getPositionY() - _bt_backHome_ptr->getContentSize().height * 0.5 - 35 - _bt_charts_ptr->getContentSize().height * 0.5));
    _bt_charts_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSPauseDialog::btnCallback, this));
    Label* _lb_charts_ptr = getTCSLabel(getTCSLanguage("tcsPauseLayer_charts"), "xiangsu15.TTF", 32);
    _bt_charts_ptr->addChild(_lb_charts_ptr, 10);
    _lb_charts_ptr->setPosition(_bt_charts_ptr->getContentSize() * 0.5);
    _lb_charts_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    // 重新开始
    Button* _bt_restart_ptr = Button::create("TCSCom/img_nothing.png");
    _sp_bg_ptr->addChild(_bt_restart_ptr, 10);
    _bt_restart_ptr->setName("btn_restart");
    _bt_restart_ptr->setScale9Enabled(true);
    _bt_restart_ptr->setContentSize(Size(200, 60));
    _bt_restart_ptr->setPosition(Size(_sp_bg_ptr->getContentSize().width * 0.5, _bt_charts_ptr->getPositionY() - _bt_charts_ptr->getContentSize().height * 0.5 - 35 - _bt_restart_ptr->getContentSize().height * 0.5));
    _bt_restart_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSPauseDialog::btnCallback, this));
    Label* _lb_restart_ptr = getTCSLabel(getTCSLanguage("tcsPauseLayer_restart"), "xiangsu15.TTF", 32);
    _bt_restart_ptr->addChild(_lb_restart_ptr, 10);
    _lb_restart_ptr->setPosition(_bt_restart_ptr->getContentSize() * 0.5);
    _lb_restart_ptr->setTextColor(Color4B(58, 56, 60, 255));
}

void CTCSPauseDialog::btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    Button* _btn_temp_ptr = dynamic_cast<Button*>(ref);
    if (type == Widget::TouchEventType::ENDED)
    {
        TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
        TCSINFO->vibrate(0);
        if (_btn_temp_ptr->getName() == "btn_backHome")
        {
            CTCSHomeScene* _cTHS_temp_ptr = CTCSHomeScene::create();
            Director::getInstance()->replaceScene(_cTHS_temp_ptr);
        }
        else if (_btn_temp_ptr->getName() == "btn_continue")
        {
            if (m_callback)
            {
                //游戏继续
                m_callback(0);
            }
            this->removeFromParent();
        }
        else if (_btn_temp_ptr->getName() == "btn_charts")
        {
            CTCSChartsDialog* _cTCD_temp_ptr = CTCSChartsDialog::create();
            this->getParent()->addChild(_cTCD_temp_ptr, 199);
        }
        else if (_btn_temp_ptr->getName() == "btn_restart")
        {
            if (m_callback)
            {
                //重新开始
                m_callback(1);
            }
            
            this->removeFromParent();
        }
    }
}

CTCSGameOverDialog* CTCSGameOverDialog::create(int score)
{
    CTCSGameOverDialog* dialog = new(std::nothrow) CTCSGameOverDialog;
    if (dialog && dialog->init(score))
    {
        dialog->autorelease();
        return dialog;
    }
    else
    {
        delete dialog;
        dialog = NULL;
        return NULL;
    }
}

CTCSGameOverDialog::~CTCSGameOverDialog()
{
    
}
    
CTCSGameOverDialog::CTCSGameOverDialog()
{
    
}
    
bool CTCSGameOverDialog::init(int score)
{
    m_i_score = score;
    if (!CTCSDialogBase::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CTCSGameOverDialog::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CTCSGameOverDialog::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSGameOverDialog::onTouchEnded, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSGameOverDialog::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
    
void CTCSGameOverDialog::initUI()
{
    Size _size_gameSize = getTCSGameSize();
    
    //背景
    Sprite* _sp_bg_ptr = Sprite::create("TCSDialog/img_bg.png");
    this->addChild(_sp_bg_ptr, 10);
    _sp_bg_ptr->setName("sp_bg");
    _sp_bg_ptr->setPosition(_size_gameSize.width * 0.5, _size_gameSize.height * 0.6);
    
    Size _size_bgSize = _sp_bg_ptr->getContentSize();
    
    //标题
    Label* _lb_title_ptr = getTCSLabel(getTCSLanguage("tcsOverLayer_title"), "xiangsu15.TTF", 62);
    _sp_bg_ptr->addChild(_lb_title_ptr, 10);
    _lb_title_ptr->setPosition(_size_bgSize.width * 0.5, _size_bgSize.height - 40 - _lb_title_ptr->getContentSize().height * 0.5);
    _lb_title_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    //分数
    Label* _lb_score_ptr = getTCSLabel(getTCSLanguage("tcsOverLayer_score"), "xiangsu15.TTF", 48);
    _sp_bg_ptr->addChild(_lb_score_ptr, 10);
    _lb_score_ptr->setPosition(_size_bgSize.width * 0.5, _lb_title_ptr->getPositionY() - _lb_title_ptr->getContentSize().height * 0.5 - 75 - _lb_score_ptr->getContentSize().height * 0.5);
    _lb_score_ptr->setTextColor(Color4B(58, 56, 60, 255));
    Label* _lb_scoreNum_ptr = getTCSLabel(PUB_strformat("%d", m_i_score), "xiangsu15.TTF", 48);
    _sp_bg_ptr->addChild(_lb_scoreNum_ptr, 10);
    _lb_scoreNum_ptr->setPosition(_size_bgSize.width * 0.5, _lb_score_ptr->getPositionY() - _lb_score_ptr->getContentSize().height * 0.5 - 50 - _lb_score_ptr->getContentSize().height * 0.5);
    _lb_scoreNum_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    // 返回首页
    Button* _bt_backHome_ptr = Button::create("TCSCom/img_nothing.png");
    _sp_bg_ptr->addChild(_bt_backHome_ptr, 10);
    _bt_backHome_ptr->setName("btn_backHome");
    _bt_backHome_ptr->setScale9Enabled(true);
    _bt_backHome_ptr->setContentSize(Size(200, 60));
    _bt_backHome_ptr->setPosition(Size(_sp_bg_ptr->getContentSize().width * 0.75, 75 + _bt_backHome_ptr->getContentSize().height * 0.5));
    _bt_backHome_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameOverDialog::btnCallback, this));
    Label* _lb_backHome_ptr = getTCSLabel(getTCSLanguage("tcsOverLayer_backHome"), "xiangsu15.TTF", 38);
    _bt_backHome_ptr->addChild(_lb_backHome_ptr, 10);
    _lb_backHome_ptr->setPosition(_bt_backHome_ptr->getContentSize() * 0.5);
    _lb_backHome_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    // 再来一局
    Button* _bt_again_ptr = Button::create("TCSCom/img_nothing.png");
    _sp_bg_ptr->addChild(_bt_again_ptr, 10);
    _bt_again_ptr->setName("btn_again");
    _bt_again_ptr->setScale9Enabled(true);
    _bt_again_ptr->setContentSize(Size(200, 60));
    _bt_again_ptr->setPosition(Size(_sp_bg_ptr->getContentSize().width * 0.25, _bt_backHome_ptr->getPositionY()));
    _bt_again_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameOverDialog::btnCallback, this));
    Label* _lb_again_ptr = getTCSLabel(getTCSLanguage("tcsOverLayer_again"), "xiangsu15.TTF", 38);
    _bt_again_ptr->addChild(_lb_again_ptr, 10);
    _lb_again_ptr->setPosition(_bt_again_ptr->getContentSize() * 0.5);
    _lb_again_ptr->setTextColor(Color4B(58, 56, 60, 255));
}

bool CTCSGameOverDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void CTCSGameOverDialog::btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    Button* _btn_temp_ptr = dynamic_cast<Button*>(ref);
    if (type == Widget::TouchEventType::ENDED)
    {
        TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
        TCSINFO->vibrate(0);
        if (_btn_temp_ptr->getName() == "btn_backHome")
        {
            CTCSHomeScene* _cTHS_temp_ptr = CTCSHomeScene::create();
            Director::getInstance()->replaceScene(_cTHS_temp_ptr);
        }
        else if (_btn_temp_ptr->getName() == "btn_again")
        {
            if (m_callback)
            {
                //再来一局
                m_callback(0);
            }
            this->removeFromParent();
        }
    };
}

CTCSChartsDialog::~CTCSChartsDialog()
{
    
}
    
CTCSChartsDialog::CTCSChartsDialog()
{
    
}
    
bool CTCSChartsDialog::init()
{
    if (!CTCSDialogBase::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CTCSChartsDialog::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CTCSChartsDialog::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSChartsDialog::onTouchEnded, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSChartsDialog::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
    
void CTCSChartsDialog::initUI()
{
    Size _size_gameSize = getTCSGameSize();
    
    //背景
    Sprite* _sp_bg_ptr = Sprite::create("TCSDialog/img_bg.png");
    this->addChild(_sp_bg_ptr, 10);
    _sp_bg_ptr->setName("sp_bg");
    _sp_bg_ptr->setPosition(_size_gameSize.width * 0.5, _size_gameSize.height * 0.6);
    
    Size _size_bgSize = _sp_bg_ptr->getContentSize();
    
    //标题
    Label* _lb_title_ptr = getTCSLabel(getTCSLanguage("tcsChartsLayer_title"), "xiangsu15.TTF", 48);
    _sp_bg_ptr->addChild(_lb_title_ptr, 10);
    _lb_title_ptr->setPosition(_size_bgSize.width * 0.5, _size_bgSize.height - 60 - _lb_title_ptr->getContentSize().height * 0.5);
    _lb_title_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    vector<int> _vecI_hisScore = TCSINFO->getHistroyScore(3);
    
    //名次
    for (int i = 0; i < _vecI_hisScore.size(); i++)
    {
        Label* _lb_first_ptr = getTCSLabel(PUB_strformat("%d", _vecI_hisScore[i]), "xiangsu15.TTF", 32);
        _sp_bg_ptr->addChild(_lb_first_ptr, 10);
        _lb_first_ptr->setPosition(_size_bgSize.width * 0.5, _lb_title_ptr->getPositionY() - _lb_title_ptr->getContentSize().height * 0.5 - _lb_title_ptr->getContentSize().height * 0.5 - 90 - 55 * i);
        _lb_first_ptr->setTextColor(Color4B(58, 56, 60, 255));
    }
    
    // 关闭
    Button* _bt_close_ptr = Button::create("TCSCom/img_nothing.png");
    _sp_bg_ptr->addChild(_bt_close_ptr, 10);
    _bt_close_ptr->setName("btn_close");
    _bt_close_ptr->setScale9Enabled(true);
    _bt_close_ptr->setContentSize(Size(200, 60));
    _bt_close_ptr->setPosition(Size(_sp_bg_ptr->getContentSize().width * 0.5, 40 + _bt_close_ptr->getContentSize().height * 0.5));
    _bt_close_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSChartsDialog::btnCallback, this));
    Label* _lb_close_ptr = getTCSLabel(getTCSLanguage("tcsChartsLayer_close"), "xiangsu15.TTF", 32);
    _bt_close_ptr->addChild(_lb_close_ptr, 10);
    _lb_close_ptr->setPosition(_bt_close_ptr->getContentSize() * 0.5);
    _lb_close_ptr->setTextColor(Color4B(58, 56, 60, 255));
}


bool CTCSChartsDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void CTCSChartsDialog::btnCallback(Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    Button* _btn_temp_ptr = dynamic_cast<Button*>(ref);
    if (type == Widget::TouchEventType::ENDED)
    {
        TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
        TCSINFO->vibrate(0);
        if (_btn_temp_ptr->getName() == "btn_close")
        {
            this->removeFromParent();
        }
    };
}
