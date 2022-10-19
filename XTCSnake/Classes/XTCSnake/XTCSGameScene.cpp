//
//  XTCSGameScene.cpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/16.
//

#include "XTCSGameScene.hpp"

#include "ui/UIScale9Sprite.h"

#include "XString.h"
#include "XMath.h"

#include "XTCSInfoManager.hpp"
#include "XTCSHomeScene.hpp"
#include "XTCSCommLayer.hpp"
#include "XTCSSoundManager.hpp"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace XSTRINGTOOL;
using namespace XMATHTOOL;

CTCSGameScene::CTCSGameScene()
{
    
}

CTCSGameScene::~CTCSGameScene()
{
    
}

CTCSGameScene* CTCSGameScene::create()
{
    CTCSGameScene* scene = new(std::nothrow) CTCSGameScene;
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        scene = NULL;
        return NULL;
    }
}

bool CTCSGameScene::init() {
    if (!Scene::init())
    {
        return false;
    }
    CTCSGameLayer* pLayer = CTCSGameLayer::create();
    this->addChild(pLayer);
    //监听back键
    cocos2d::EventListenerKeyboard* pListener = cocos2d::EventListenerKeyboard::create();
    pListener->onKeyReleased = CC_CALLBACK_2(CTCSGameScene::onKeyReleased, this);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
    return true;
}

void CTCSGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
        case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
        {
        }
        break;
            default:
        break;
    }
}
// 应用进入后台
void CTCSGameScene::EnterBackGround()
{
    
}

// 应用进入前台
void CTCSGameScene::EnterForeGround()
{
    
}


bool CTCSGameLayer::init() {
    if (!Layer::init())
    {
        return false;
    }
    
    initUI();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CTCSGameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CTCSGameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSGameLayer::onTouchEnded, this);
    listener->onTouchCancelled  = CC_CALLBACK_2(CTCSGameLayer::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    return true;
}

void CTCSGameLayer::onEnter()
{
    Layer::onEnter();
    m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMESTART);
    TCSSoundInstance()->tcsPlayBackgroundMusic(CTCSSoundManager::TCS_SOUND_MUSIC);
}

void CTCSGameLayer::onExit()
{
    Layer::onExit();
    TCSSoundInstance()->tcsStopBackgroundMusic(CTCSSoundManager::TCS_SOUND_MUSIC);
}

bool CTCSGameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (TCSINFO->getOpWay() == 0 || m_cTCSMap_map_ptr->getGameState() == GAMESTATE_TCS_GAMEPAUSE)
    {
        return false;
    }
    m_vec2_touchBeginPos = touch->getLocation();
    return true;
}

void CTCSGameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) { 
    m_vec2_touchEndPos = touch->getLocation();
}

void CTCSGameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) { 
    m_vec2_touchEndPos = touch->getLocation();
    
    if (m_vec2_touchBeginPos.x != -1 && m_vec2_touchBeginPos.y != -1 && m_vec2_touchEndPos.x != -1 && m_vec2_touchEndPos.y != -1)
    {
        STCSDirection _sTCSDir_curDir = m_cTCSMap_map_ptr->getCurDir();
        Vec2 _vec2_dis = m_vec2_touchEndPos-m_vec2_touchBeginPos;
        float _f_angle = 0;
        PUB_calTwoPointAngle(m_vec2_touchBeginPos.x, m_vec2_touchBeginPos.y, m_vec2_touchEndPos.x, m_vec2_touchEndPos.y, _f_angle);
        STCSTurnTo _sTCSTT_res = TURNTO_NONE;
        if (DIRECTION_UP == _sTCSDir_curDir)
        {
            if (_vec2_dis.x < 0 && _f_angle < 45)
            {
                _sTCSTT_res = TURNTO_LEFT;
            }
            else if (_vec2_dis.x > 0 && _f_angle < 45)
            {
                _sTCSTT_res = TURNTO_RIGHT;
            }
        }
        else if (DIRECTION_DOWN == _sTCSDir_curDir)
        {
            if (_vec2_dis.x < 0 && _f_angle < 45)
            {
                _sTCSTT_res = TURNTO_RIGHT;
            }
            else if (_vec2_dis.x > 0 && _f_angle < 45)
            {
                _sTCSTT_res = TURNTO_LEFT;
            }
        }
        else if (DIRECTION_LEFT == _sTCSDir_curDir)
        {
            if (_vec2_dis.y < 0 && _f_angle > 45)
            {
                _sTCSTT_res = TURNTO_LEFT;
            }
            else if (_vec2_dis.y > 0 && _f_angle > 45)
            {
                _sTCSTT_res = TURNTO_RIGHT;
            }
        }
        else if (DIRECTION_RIGHT == _sTCSDir_curDir)
        {
            if (_vec2_dis.y < 0 && _f_angle > 45)
            {
                _sTCSTT_res = TURNTO_RIGHT;
            }
            else if (_vec2_dis.y > 0 && _f_angle > 45)
            {
                _sTCSTT_res = TURNTO_LEFT;
            }
        }
        m_cTCSMap_map_ptr->addTurnTo(_sTCSTT_res);
    }
    
    
}

void CTCSGameLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) { 
    m_vec2_touchBeginPos.x = -1;
    m_vec2_touchBeginPos.y = -1;
    m_vec2_touchEndPos.x = -1;
    m_vec2_touchEndPos.y = -1;
}

void CTCSGameLayer::initUI() {
    Size _size_gameSize = getTCSGameSize();
    Size _size_screenSize = getTCSScreenSize();
    
    //背景
    Sprite* _sp_homeBg_ptr = Sprite::create("TCSCom/img_bg.png");
    this->addChild(_sp_homeBg_ptr, 10);
    _sp_homeBg_ptr->setPosition(_size_screenSize * 0.5);
    
    //暂停
    Button* _btn_pause_ptr = Button::create("TCSGame/img_pause.png");
    this->addChild(_btn_pause_ptr, 20);
    _btn_pause_ptr->setName("btn_pause");
    _btn_pause_ptr->setPosition(Size(34 + _btn_pause_ptr->getContentSize().width * 0.5, _size_gameSize.height - 6 - _btn_pause_ptr->getContentSize().height * 0.5));
    _btn_pause_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    
    //分数
    m_lb_score_ptr = getTCSLabel(PUB_strformat((getTCSLanguage("tcsGameLayer_score") + ": %d").c_str(), m_i_score), "xiangsu15.TTF", 48);
    this->addChild(m_lb_score_ptr, 20);
    m_lb_score_ptr->setPosition(Vec2(Size(_size_gameSize.width * 0.5, _btn_pause_ptr->getPositionY())));
    m_lb_score_ptr->setTextColor(Color4B(58, 56, 60, 250));
    
    //重玩
    Button* _btn_restart_ptr = Button::create("TCSGame/img_restart.png");
    this->addChild(_btn_restart_ptr, 20);
    _btn_restart_ptr->setName("btn_restart");
    _btn_restart_ptr->setPosition(Size(_size_gameSize.width - _btn_restart_ptr->getContentSize().width * 0.5 - 34, _btn_pause_ptr->getPositionY()));
    _btn_restart_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    
    //地图
    m_cTCSMap_map_ptr = CTCSMap::create();
    this->addChild(m_cTCSMap_map_ptr, 10);
    
    Sprite* _sp_mapContent_Ptr = Sprite::create("TCSGame/img_smallBg0.png");
    
    m_cTCSMap_map_ptr->setContentSize(Size(XTCSMAP_WIDTH * (_sp_mapContent_Ptr->getContentSize().width + 2), XTCSMAP_HEIGHT * (_sp_mapContent_Ptr->getContentSize().height + 2)));
    m_cTCSMap_map_ptr->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    m_cTCSMap_map_ptr->setPosition(Size(_size_gameSize.width * 0.5, _btn_restart_ptr->getPositionY() - _btn_restart_ptr->getContentSize().height * 0.5 - 10));
    m_cTCSMap_map_ptr->setShowScoreCallBack(CC_CALLBACK_1(CTCSGameLayer::updateScore, this));
    m_cTCSMap_map_ptr->setShowGameOverCallBack(CC_CALLBACK_1(CTCSGameLayer::showGameOverCallback, this));
    
    //操作方式
    Label* _lb_opWayDes_ptr = getTCSLabel(TCSINFO->getLanguage("tcsGameLayer_opWay"), "xiangsu15.TTF", 38);
    this->addChild(_lb_opWayDes_ptr, 10);
    _lb_opWayDes_ptr->setPosition(Vec2(34 + _lb_opWayDes_ptr->getContentSize().width * 0.5, m_cTCSMap_map_ptr->getPositionY() - XTCSMAP_HEIGHT * (_sp_mapContent_Ptr->getContentSize().height + 2) - 40));
    _lb_opWayDes_ptr->setTextColor(Color4B(58, 56, 60, 250));
    
    Button* _btn_switchFrame_ptr = Button::create("TCSGame/img_switchFrame.png");
    this->addChild(_btn_switchFrame_ptr, 10);
    _btn_switchFrame_ptr->setName("btn_switch");
    _btn_switchFrame_ptr->setZoomScale(0);
    _btn_switchFrame_ptr->setPosition(Vec2(34 + _btn_switchFrame_ptr->getContentSize().width * 0.5, _lb_opWayDes_ptr->getPositionY() - _lb_opWayDes_ptr->getContentSize().height * 0.5 - _btn_switchFrame_ptr->getContentSize().height * 0.5 - 20));
    _btn_switchFrame_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    Sprite* _sp_switch_ptr = Sprite::create("TCSGame/img_switch.png");
    _btn_switchFrame_ptr->addChild(_sp_switch_ptr, 10);
    _sp_switch_ptr->setName("sp_switch");
    Label* _lb_opWay_ptr = getTCSLabel(TCSINFO->getLanguage("tcsGameLayer_button"), "xiangsu15.TTF", 38);
    _lb_opWay_ptr->setName("lb_opWay");
    _btn_switchFrame_ptr->addChild(_lb_opWay_ptr, 10);
    _lb_opWay_ptr->setPosition(Vec2(_btn_switchFrame_ptr->getContentSize().width * 0.6, _btn_switchFrame_ptr->getContentSize().height * 0.5));
    _lb_opWay_ptr->setTextColor(Color4B(58, 56, 60, 250));
    _sp_switch_ptr->setPosition(Vec2(_btn_switchFrame_ptr->getContentSize().width * 0.2, _btn_switchFrame_ptr->getContentSize().height * 0.5));
    if (TCSINFO->getOpWay() == 1)
    {
        _sp_switch_ptr->setPosition(Vec2(_btn_switchFrame_ptr->getContentSize().width * 0.8, _btn_switchFrame_ptr->getContentSize().height * 0.5));
        _lb_opWay_ptr->setPosition(Vec2(_btn_switchFrame_ptr->getContentSize().width * 0.4, _btn_switchFrame_ptr->getContentSize().height * 0.5));
        _lb_opWay_ptr->setString(TCSINFO->getLanguage("tcsGameLayer_slide"));
    }
    
    //方向键盘
    Vec2 _vec2_posBegin = Vec2(_size_gameSize.width * 0.5, m_cTCSMap_map_ptr->getPositionY() - XTCSMAP_HEIGHT * (_sp_mapContent_Ptr->getContentSize().height + 2) - 40);
    
    m_btn_up_ptr = Button::create("TCSGame/img_up.png");
    this->addChild(m_btn_up_ptr, 10);
    m_btn_up_ptr->setPosition(Vec2(_vec2_posBegin.x, _vec2_posBegin.y * 0.667));
    m_btn_up_ptr->setName("btn_up");
    m_btn_up_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    
    m_btn_down_ptr = Button::create("TCSGame/img_up.png");
    this->addChild(m_btn_down_ptr, 10);
    m_btn_down_ptr->setPosition(Vec2(_vec2_posBegin.x, _vec2_posBegin.y * 0.334));
    m_btn_down_ptr->setRotation(180);
    m_btn_down_ptr->setName("btn_down");
    m_btn_down_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    
    m_btn_right_ptr = Button::create("TCSGame/img_up.png");
    this->addChild(m_btn_right_ptr, 10);
    m_btn_right_ptr->setPosition(Vec2(_vec2_posBegin.x + m_btn_up_ptr->getContentSize().width + 10, _vec2_posBegin.y * 0.5));
    m_btn_right_ptr->setRotation(90);
    m_btn_right_ptr->setName("btn_right");
    m_btn_right_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    
    m_btn_left_ptr = Button::create("TCSGame/img_up.png");
    this->addChild(m_btn_left_ptr, 10);
    m_btn_left_ptr->setPosition(Vec2(_vec2_posBegin.x -  m_btn_up_ptr->getContentSize().width - 10, _vec2_posBegin.y * 0.5));
    m_btn_left_ptr->setRotation(-90);
    m_btn_left_ptr->setName("btn_left");
    m_btn_left_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    
    if (_vec2_posBegin.y * 0.334 < m_btn_up_ptr->getContentSize().height)
    {
        float _f_scale = _vec2_posBegin.y * 0.3 / m_btn_up_ptr->getContentSize().height;
        m_btn_up_ptr->setScale(_f_scale);
        m_btn_down_ptr->setScale(_f_scale);
        m_btn_left_ptr->setScale(_f_scale);
        m_btn_right_ptr->setScale(_f_scale);
    }
    
    Button* _btn_bigPause_ptr = Button::create("TCSGame/img_bigPause.png");
    this->addChild(_btn_bigPause_ptr, 10);
    _btn_bigPause_ptr->setName("btn_bigPause");
    _btn_bigPause_ptr->setPosition(Vec2(_size_gameSize.width - 34 - _btn_bigPause_ptr->getContentSize().width * 0.5, (m_cTCSMap_map_ptr->getPositionY() - XTCSMAP_HEIGHT * (_sp_mapContent_Ptr->getContentSize().height + 2) - 30) - _btn_bigPause_ptr->getContentSize().height * 0.5));
    _btn_bigPause_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSGameLayer::btnCallback, this));
    
    if (TCSINFO->getOpWay() == 1)
    {
        m_btn_left_ptr->setVisible(false);
        m_btn_right_ptr->setVisible(false);
        m_btn_up_ptr->setVisible(false);
        m_btn_down_ptr->setVisible(false);
    }
}

void CTCSGameLayer::btnCallback(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type) { 
    Button* _btn_temp_ptr = dynamic_cast<Button*>(ref);
    if (type == Widget::TouchEventType::ENDED)
    {
        TCSINFO->vibrate(0);
        if (_btn_temp_ptr->getName() == "btn_pause")
        {
            TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
            m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMEPAUSE);
            CTCSPauseDialog* _cTCSPause_temp_ptr = CTCSPauseDialog::create();
            this->addChild(_cTCSPause_temp_ptr, 99);
            _cTCSPause_temp_ptr->setCallback(CC_CALLBACK_1(CTCSGameLayer::pauseCallback, this));
        }
        else if (_btn_temp_ptr->getName() == "btn_bigPause")
        {
            TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
            if (m_cTCSMap_map_ptr->getGameState() == GAMESTATE_TCS_GAMEPAUSE)
            {
                m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMESTART);
                _btn_temp_ptr->loadTextureNormal("TCSGame/img_bigPause.png");
            }
            else if (m_cTCSMap_map_ptr->getGameState() == GAMESTATE_TCS_GAMESTART)
            {
                m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMEPAUSE);
                _btn_temp_ptr->loadTextureNormal("TCSGame/img_continue.png");
            }
        }
        else if (_btn_temp_ptr->getName() == "btn_up")
        {
            if (m_cTCSMap_map_ptr->getGameState() == GAMESTATE_TCS_GAMESTART)
            {
                STCSTurnTo _sTCSTT_res = TURNTO_NONE;
                STCSDirection _sTCSDir_curDir = m_cTCSMap_map_ptr->getCurDir();
                if (DIRECTION_LEFT == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_RIGHT;
                }
                else if (DIRECTION_RIGHT == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_LEFT;
                }
                m_cTCSMap_map_ptr->addTurnTo(_sTCSTT_res);
            }
        }
        else if (_btn_temp_ptr->getName() == "btn_down")
        {
            
            if (m_cTCSMap_map_ptr->getGameState() == GAMESTATE_TCS_GAMESTART)
            {
                STCSTurnTo _sTCSTT_res = TURNTO_NONE;
                STCSDirection _sTCSDir_curDir = m_cTCSMap_map_ptr->getCurDir();
                if (DIRECTION_LEFT == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_LEFT;
                }
                else if (DIRECTION_RIGHT == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_RIGHT;
                }
                m_cTCSMap_map_ptr->addTurnTo(_sTCSTT_res);
            }
        }
        else if (_btn_temp_ptr->getName() == "btn_left")
        {
            
            if (m_cTCSMap_map_ptr->getGameState() == GAMESTATE_TCS_GAMESTART)
            {
                STCSTurnTo _sTCSTT_res = TURNTO_NONE;
                STCSDirection _sTCSDir_curDir = m_cTCSMap_map_ptr->getCurDir();
                if (DIRECTION_UP == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_LEFT;
                }
                else if (DIRECTION_DOWN == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_RIGHT;
                }
                m_cTCSMap_map_ptr->addTurnTo(_sTCSTT_res);
            }
        }
        else if (_btn_temp_ptr->getName() == "btn_right")
        {
            
            if (m_cTCSMap_map_ptr->getGameState() == GAMESTATE_TCS_GAMESTART)
            {
                STCSTurnTo _sTCSTT_res = TURNTO_NONE;
                STCSDirection _sTCSDir_curDir = m_cTCSMap_map_ptr->getCurDir();
                if (DIRECTION_UP == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_RIGHT;
                }
                else if (DIRECTION_DOWN == _sTCSDir_curDir)
                {
                    _sTCSTT_res = TURNTO_LEFT;
                }
                m_cTCSMap_map_ptr->addTurnTo(_sTCSTT_res);
            }
        }
        else if (_btn_temp_ptr->getName() == "btn_restart")
        {
            TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
            m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMEOVER);
        }
        else if (_btn_temp_ptr->getName() == "btn_switch")
        {
            TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
            int _i_opWay = TCSINFO->getOpWay();
            if (0 == _i_opWay)
            {
                TCSINFO->setOpWay(1);
            }
            else
            {
                TCSINFO->setOpWay(0);
            }
            
            if (TCSINFO->getOpWay() == 1)
            {
                Label* _lb_opWay_ptr = dynamic_cast<Label*>(_btn_temp_ptr->getChildByName("lb_opWay"));
                if (_lb_opWay_ptr)
                {
                    _lb_opWay_ptr->setOpacity(0);
                    _lb_opWay_ptr->setPosition(Vec2(_btn_temp_ptr->getContentSize().width * 0.4, _btn_temp_ptr->getContentSize().height * 0.5));
                    _lb_opWay_ptr->setString(TCSINFO->getLanguage("tcsGameLayer_slide"));
                    _lb_opWay_ptr->runAction(Sequence::create(DelayTime::create(0.17f), FadeIn::create(0.17), nullptr));
                }
                
                Sprite* _sp_opWay_ptr = dynamic_cast<Sprite*>(_btn_temp_ptr->getChildByName("sp_switch"));
                if (_sp_opWay_ptr)
                {
                    _sp_opWay_ptr->runAction(MoveTo::create(0.17, Vec2(_btn_temp_ptr->getContentSize().width * 0.8, _btn_temp_ptr->getContentSize().height * 0.5)));
                }
                
                m_btn_left_ptr->setVisible(false);
                m_btn_right_ptr->setVisible(false);
                m_btn_up_ptr->setVisible(false);
                m_btn_down_ptr->setVisible(false);
            }
            else
            {
                Label* _lb_opWay_ptr = dynamic_cast<Label*>(_btn_temp_ptr->getChildByName("lb_opWay"));
                if (_lb_opWay_ptr)
                {
                    _lb_opWay_ptr->setPosition(Vec2(_btn_temp_ptr->getContentSize().width * 0.6, _btn_temp_ptr->getContentSize().height * 0.5));
                    _lb_opWay_ptr->setOpacity(0);
                    _lb_opWay_ptr->setString(TCSINFO->getLanguage("tcsGameLayer_button"));
                    _lb_opWay_ptr->runAction(Sequence::create(DelayTime::create(0.17f), FadeIn::create(0.17), nullptr));
                }
                
                Sprite* _sp_opWay_ptr = dynamic_cast<Sprite*>(_btn_temp_ptr->getChildByName("sp_switch"));
                if (_sp_opWay_ptr)
                {
                    _sp_opWay_ptr->runAction(MoveTo::create(0.17, Vec2(_btn_temp_ptr->getContentSize().width * 0.2, _btn_temp_ptr->getContentSize().height * 0.5)));
                }
                
                m_btn_left_ptr->setVisible(true);
                m_btn_right_ptr->setVisible(true);
                m_btn_up_ptr->setVisible(true);
                m_btn_down_ptr->setVisible(true);
            }
        }
    };
}

void CTCSGameLayer::update(float dt) { 
    ;
}

CTCSGameLayer::~CTCSGameLayer()
{
    
}

void CTCSGameLayer::updateScore(int score)
{
    m_i_score = score;
    m_lb_score_ptr->setString(PUB_strformat((getTCSLanguage("tcsGameLayer_score") + ": %d").c_str(), m_i_score));
}

void CTCSGameLayer::pauseCallback(int type)
{
    if (0 == type)
    {
        //继续游戏
        m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMESTART);
    }
    else if (1 == type)
    {
        //重新开始
        m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMEOVER);
    }
}

void CTCSGameLayer::gameOverCallback(int type)
{
    if (0 == type)
    {
        //再来一局
        m_cTCSMap_map_ptr->setGameState(GAMESTATE_TCS_GAMESTART);
    }
    else if (1 == type)
    {
        
    }
}

void CTCSGameLayer::showGameOverCallback(int score)
{
    CTCSGameOverDialog* _CTGOD_over_ptr = CTCSGameOverDialog::create(score);
    this->addChild(_CTGOD_over_ptr, 99);
    _CTGOD_over_ptr->setCallback(CC_CALLBACK_1(CTCSGameLayer::gameOverCallback, this));
    TCSINFO->addScoreRecord(score);
}
