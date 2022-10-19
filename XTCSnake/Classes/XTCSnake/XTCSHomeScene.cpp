//
//  XTCSHomeScene.cpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/19.
//

#include "XTCSHomeScene.hpp"

#include "ui/UIScale9Sprite.h"

#include "XTCSInfoManager.hpp"
#include "XTCSGameScene.hpp"
#include "XTCSCommLayer.hpp"
#include "XTCSSoundManager.hpp"

USING_NS_CC;
using namespace cocos2d::ui;

CTCSHomeScene::CTCSHomeScene()
{
    
}

CTCSHomeScene::~CTCSHomeScene()
{
    
}

CTCSHomeScene* CTCSHomeScene::create()
{
    CTCSHomeScene* scene = new(std::nothrow) CTCSHomeScene;
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

bool CTCSHomeScene::init() { 
    if (!Scene::init())
    {
        return false;
    }
    CTCSHomeLayer* pLayer = CTCSHomeLayer::create();
    this->addChild(pLayer);
    //监听back键
    cocos2d::EventListenerKeyboard* pListener = cocos2d::EventListenerKeyboard::create();
    pListener->onKeyReleased = CC_CALLBACK_2(CTCSHomeScene::onKeyReleased, this);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
    return true;
}

void CTCSHomeScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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
void CTCSHomeScene::EnterBackGround()
{
    
}

// 应用进入前台
void CTCSHomeScene::EnterForeGround()
{
    
}

CTCSHomeLayer::CTCSHomeLayer()
{
    
}

CTCSHomeLayer::~CTCSHomeLayer()
{
    
}

bool CTCSHomeLayer::init() { 
    if (!Layer::init())
    {
        return false;
    }
    
    initUI();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CTCSHomeLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CTCSHomeLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSHomeLayer::onTouchEnded, this);
    listener->onTouchEnded = CC_CALLBACK_2(CTCSHomeLayer::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //this->scheduleUpdate();
    
    return true;
}

bool CTCSHomeLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) { 
    return true;
}

void CTCSHomeLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) { 
    ;
}

void CTCSHomeLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) { 
    ;
}

void CTCSHomeLayer::initUI() { 
    Size _size_gameSize = getTCSGameSize();
    Size _size_screenSize = getTCSScreenSize();
    
    //背景
    Sprite* _sp_homeBg_ptr = Sprite::create("TCSCom/img_bg.png");
    this->addChild(_sp_homeBg_ptr, 10);
    _sp_homeBg_ptr->setPosition(_size_screenSize * 0.5);
    
    //蛇
    initSnake();
    
    //标题
    Label* _lb_title_ptr = getTCSLabel(getTCSLanguage("tcsHomeLayer_title"), "xiangsu24.TTF",132);
    this->addChild(_lb_title_ptr, 20);
    _lb_title_ptr->setPosition(_size_gameSize * 0.5 + Size(0, 227 * _size_gameSize.height / 1280 + _lb_title_ptr->getContentSize().height * 0.5));
    _lb_title_ptr->setTextColor(Color4B(58, 56, 60, 255));
    Label* _lb_smallTitle_ptr = getTCSLabel(getTCSLanguage("tcsHomeLayer_smallTitle"), "xiangsu24.TTF",66);
    this->addChild(_lb_smallTitle_ptr, 20);
    _lb_smallTitle_ptr->setPosition(_size_gameSize * 0.5 + Size(0, 227 * _size_gameSize.height / 1280 + _lb_smallTitle_ptr->getContentSize().height * 0.5 - 80));
    _lb_smallTitle_ptr->setTextColor(Color4B(58, 56, 60, 255));
    
    //排行榜
    Button* _btn_charts_ptr = Button::create("TCSHome/img_charts.png");
    this->addChild(_btn_charts_ptr, 20);
    _btn_charts_ptr->setName("btn_charts");
    _btn_charts_ptr->setPosition(Vec2(61 + _btn_charts_ptr->getContentSize().width * 0.5, _size_gameSize.height - 56 - _btn_charts_ptr->getContentSize().height * 0.5));
    _btn_charts_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSHomeLayer::btnCallback, this));
    
    //声音
    Button* _btn_sound_ptr = Button::create("TCSHome/img_openSound.png");
    this->addChild(_btn_sound_ptr, 20);
    _btn_sound_ptr->setName("btn_sound");
    _btn_sound_ptr->setPosition(Vec2(_size_gameSize.width - 61 - _btn_sound_ptr->getContentSize().width * 0.5, _size_gameSize.height - 56 - _btn_sound_ptr->getContentSize().height * 0.5));
    _btn_sound_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSHomeLayer::btnCallback, this));
    if (!TCSINFO->isOpenSound())
    {
        _btn_sound_ptr->loadTextureNormal("TCSHome/img_closeSound.png");
    }
    
    //震动
    Button* _btn_shake_ptr = Button::create("TCSHome/img_openShake.png");
    this->addChild(_btn_shake_ptr, 20);
    _btn_shake_ptr->setName("btn_shake");
    _btn_shake_ptr->setPosition(Vec2(_btn_sound_ptr->getPosition().x -  _btn_sound_ptr->getContentSize().width * 0.5 - 36 - _btn_shake_ptr->getContentSize().width * 0.5, _btn_sound_ptr->getPosition().y));
    _btn_shake_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSHomeLayer::btnCallback, this));
    if (!TCSINFO->isOpenShake())
    {
        _btn_sound_ptr->loadTextureNormal("TCSHome/img_closeShake.png");
    }
    
    //分享
    Button* _btn_share_ptr = Button::create("TCSHome/img_share.png");
    //this->addChild(_btn_share_ptr, 20);
    _btn_share_ptr->setName("btn_shard");
    _btn_share_ptr->setPosition(Vec2(_size_gameSize.width - 61 - _btn_share_ptr->getContentSize().width * 0.5, _size_gameSize.height - 56 - _btn_share_ptr->getContentSize().height * 0.5));
    
    //反馈
    Button* _btn_feekback_ptr = Button::create("TCSHome/img_feekback.png");
    //this->addChild(_btn_feekback_ptr, 20);
    _btn_feekback_ptr->setName("btn_feekback");
    _btn_feekback_ptr->setPosition(Vec2(_btn_share_ptr->getPosition().x /*-  _btn_share_ptr->getContentSize().width * 0.5 - 36 - _btn_feekback_ptr->getContentSize().width * 0.5*/, _btn_share_ptr->getPosition().y));
    
    //开始游戏
    Button* _btn_start_ptr = Button::create("TCSCom/img_nothing.png");
    _btn_start_ptr->setScale9Enabled(true);
    _btn_start_ptr->setContentSize(Size(250, 50));
    Label* _lb_start_ptr = getTCSLabel(getTCSLanguage("tcsHomeLayer_begin"), "xiangsu24.TTF", 72);
    _btn_start_ptr->getRendererNormal()->addChild(_lb_start_ptr, 10);
    _lb_start_ptr->setTextColor(Color4B(58, 56, 60, 255));
    _lb_start_ptr->setPosition(_btn_start_ptr->getContentSize() * 0.5);
    this->addChild(_btn_start_ptr, 20);
    _btn_start_ptr->setName("btn_start");
    _btn_start_ptr->setPosition(Vec2(_size_gameSize.width * 0.5, _size_gameSize.height * 0.5 - (330 * _size_gameSize.height / 1280.0) - _btn_start_ptr->getContentSize().height * 0.5));
    _btn_start_ptr->addTouchEventListener(CC_CALLBACK_2(CTCSHomeLayer::btnCallback, this));
}

void CTCSHomeLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) { 
    ;
}

void CTCSHomeLayer::btnCallback(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    Button* _btn_temp_ptr = dynamic_cast<Button*>(ref);
    if (type == Widget::TouchEventType::ENDED)
    {
        TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_BUTTON);
        TCSINFO->vibrate(0);
        if (_btn_temp_ptr->getName() == "btn_start")
        {
            CTCSGameScene* _cTGS_temp_ptr = CTCSGameScene::create();
            Director::getInstance()->replaceScene(_cTGS_temp_ptr);
        }
        else if (_btn_temp_ptr->getName() == "btn_charts")
        {
            CTCSChartsDialog* _cTCD_temp_ptr = CTCSChartsDialog::create();
            this->addChild(_cTCD_temp_ptr, 99);
        }
        else if (_btn_temp_ptr->getName() == "btn_sound")
        {
            bool _b_sound = TCSINFO->isOpenSound();
            TCSINFO->setSound(!_b_sound);
            if (TCSINFO->isOpenSound())
            {
                _btn_temp_ptr->loadTextureNormal("TCSHome/img_openSound.png");
            }
            else
            {
                _btn_temp_ptr->loadTextureNormal("TCSHome/img_closeSound.png");
            }
        }
        else if (_btn_temp_ptr->getName() == "btn_shake")
        {
            bool _b_shake = TCSINFO->isOpenShake();
            TCSINFO->setShake(!_b_shake);
            if (TCSINFO->isOpenShake())
            {
                _btn_temp_ptr->loadTextureNormal("TCSHome/img_openShake.png");
            }
            else
            {
                _btn_temp_ptr->loadTextureNormal("TCSHome/img_closeShake.png");
            }
        }
    };
}

void CTCSHomeLayer::initSnake()
{
    Size _size_gameSize = getTCSGameSize();
    Sprite* _sp_snakeHead_ptr = Sprite::create("TCSCom/img_smallHead.png");
    this->addChild(_sp_snakeHead_ptr, 20);
    _sp_snakeHead_ptr->setPosition(Vec2(_size_gameSize.width * 0.5, _size_gameSize.height * 0.5 + 2 + _sp_snakeHead_ptr->getContentSize().height * 0.5));
    
    for (int i = 0; i < 3; i++)
    {
        Sprite* _sp_snakeBody_ptr = Sprite::create("TCSCom/img_smallBody.png");
        this->addChild(_sp_snakeBody_ptr, 20);
        _sp_snakeBody_ptr->setPosition(Vec2(_size_gameSize.width * 0.5, _size_gameSize.height * 0.5 - _sp_snakeHead_ptr->getContentSize().height * (0.5 + i)));
    }
}

//void CTCSHomeLayer::update(float dt) {
//    ;
//}




