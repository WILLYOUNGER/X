//
//  XTCSInfoManager.cpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/16.
//

#include "XTCSInfoManager.hpp"

#include <string>

#include "XTime.h"
#include "XLog.h"
#include "XCOCOS2DX.hpp"

#include "XTCSHomeScene.hpp"
#include "XTCSSoundManager.hpp"

USING_NS_CC;
using namespace std;
using namespace XFILETOOL;
using namespace XTIMETOOL;
using namespace XCOCOSTOOL;

static bool g_TCSFirstTimeGetDesign = true;
static Size g_TCSDesignResolutionSize = Size::ZERO;
static ResolutionPolicy g_TCSResolutionplocy = ResolutionPolicy::SHOW_ALL;

static void TCSChangeDesignMode()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (g_TCSFirstTimeGetDesign)
    {
       g_TCSFirstTimeGetDesign = false;
       g_TCSDesignResolutionSize = glview->getDesignResolutionSize();
       g_TCSResolutionplocy = glview->getResolutionPolicy();
    }
    float fScale = 720.0f / glview->getFrameSize().width;
    float fHeight = glview->getFrameSize().height * fScale;
    glview->setDesignResolutionSize(720.0f, fHeight, ResolutionPolicy::EXACT_FIT);
}

static void TCSRestoreDesignMode()
{
    //还原之前的
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    glview->setDesignResolutionSize(g_TCSDesignResolutionSize.width, g_TCSDesignResolutionSize.height, g_TCSResolutionplocy);
}

Label* getTCSLabel(std::string str, std::string font, int size, int width/* = 0*/, int height/* = 0*/)
{
    Label* _lb_res_ptr = nullptr;
    if ("" == font)
    {
        _lb_res_ptr = Label::createWithSystemFont(str, "", size);
    }
    else
    {
        _lb_res_ptr = Label::createWithTTF(str, font, size);
    }
    
    if (width > 0)
    {
        while (width < _lb_res_ptr->getContentSize().width)
        {
            if ("" == font)
            {
                _lb_res_ptr->setSystemFontSize(_lb_res_ptr->getSystemFontSize() - 1);
            }
            else
            {
                auto _ttfConfig = _lb_res_ptr->getTTFConfig();
                _ttfConfig.fontSize--;
                _lb_res_ptr->setTTFConfig(_ttfConfig);
            }
        }
    }
    
    if (height > 0)
    {
        while (height < _lb_res_ptr->getContentSize().height)
        {
            if ("" == font)
            {
                _lb_res_ptr->setSystemFontSize(_lb_res_ptr->getSystemFontSize() - 1);
            }
            else
            {
                auto _ttfConfig = _lb_res_ptr->getTTFConfig();
                _ttfConfig.fontSize--;
                _lb_res_ptr->setTTFConfig(_ttfConfig);
            }
        }
    }
    
    return _lb_res_ptr;
}

void setTCSResourse()
{
    //设置路径
    FileUtils::getInstance()->setSearchPaths({"res_tcs_v1/pub", "res_tcs_v1/zh"});
}

void TCSEnterGame()
{
    TCSChangeDesignMode();
    setTCSResourse();
    TCSSoundInstance()->loadVoiceResource();
    
    auto _scene = CTCSHomeScene::create();
    Director::getInstance()->replaceScene(_scene);
}

void TCSEnterHome()
{
    //do nothing
}

cocos2d::Size getTCSScreenSize()
{
    return TCSINFO->getScreenSize();
}

cocos2d::Size getTCSGameSize()
{
    return TCSINFO->getVisiableSize();
}

std::string getTCSLanguage(std::string key)
{
    return TCSINFO->getLanguage(key);
}

cocos2d::Size CTCSInfoManager::getScreenSize() {
    return Director::getInstance()->getVisibleSize();
}

cocos2d::Size CTCSInfoManager::getVisiableSize() {
    return Director::getInstance()->getVisibleSize() - Size(0, PUB_GetBangsHegiht() * 2.0);
}

std::string CTCSInfoManager::getLanguage(std::string strKey)
{
    std::string str = "";
    str = m_xmlTool_xml.getValueByKey(strKey);
    return str;
}

void CTCSInfoManager::init() {
    m_xmlTool_xml.init(FileUtils::getInstance()->fullPathForFilename("tcsLanguage.xml").c_str());
    m_json_userData_Ptr = make_shared<XJson>();
    XJSONTOOLINSTANCE()->openJsonByFile(FileUtils::getInstance()->getWritablePath() + "tcsUserData.json", m_json_userData_Ptr);
}

CTCSInfoManager::CTCSInfoManager() {
    
}

CTCSInfoManager::~CTCSInfoManager() {
    
}


CTCSInfoManager *CTCSInfoManager::getInstance() {
    static CTCSInfoManager* s_cTCSInfo_instance_ptr = nullptr;
    if (s_cTCSInfo_instance_ptr == nullptr)
    {
        s_cTCSInfo_instance_ptr = new CTCSInfoManager();
        s_cTCSInfo_instance_ptr->init();
    }
    return s_cTCSInfo_instance_ptr;
}

cocos2d::Color4B CTCSInfoManager::getColor4B(std::string typekey)
{
    return Color4B();
}

void CTCSInfoManager::addScoreRecord(int score)
{
    //纪录历史
    XJsonValuePtr _xJVP_scoreValues = m_json_userData_Ptr->getValue("allHisToryScore");
    list<XJsonValuePtr> _listXJVP_historys;
    _xJVP_scoreValues->getArrayValue(_listXJVP_historys);
    XJsonValuePtr _xJVP_scoreValue = make_shared<XJsonValue>();
    
    XJsonPtr _xJson_score_Ptr = genAHistory(score, int(_listXJVP_historys.size()) + 1, 10);
    
    _xJVP_scoreValue->setObjectValue(_xJson_score_Ptr);
    _listXJVP_historys.push_back(_xJVP_scoreValue);
    
    XJsonValuePtr _xJVP_historys_Ptr = make_shared<XJsonValue>();
    _xJVP_historys_Ptr->setArrayValue(_listXJVP_historys);
    
    m_json_userData_Ptr->setKeyValue("allHisToryScore", _xJVP_historys_Ptr);
    
    //插入名次
    vector<int> _vecI_hisScore = getHistroyScore(3);
    
    if (score > _vecI_hisScore[0])
    {
        XJsonValuePtr _xJVP_second_Ptr =  m_json_userData_Ptr->getValue("second");
        m_json_userData_Ptr->setKeyValue("third", _xJVP_second_Ptr);
        XJsonValuePtr _xJVP_first_Ptr =  m_json_userData_Ptr->getValue("first");
        m_json_userData_Ptr->setKeyValue("second", _xJVP_first_Ptr);
        m_json_userData_Ptr->setKeyValue("first", _xJVP_scoreValue);
    }
    else if (score > _vecI_hisScore[1])
    {
        XJsonValuePtr _xJVP_second_Ptr =  m_json_userData_Ptr->getValue("second");
        m_json_userData_Ptr->setKeyValue("third", _xJVP_second_Ptr);
        m_json_userData_Ptr->setKeyValue("second", _xJVP_scoreValue);
    }
    else if (score > _vecI_hisScore[2])
    {
        m_json_userData_Ptr->setKeyValue("third", _xJVP_scoreValue);
    }
    XJSONTOOLINSTANCE()->saveFileByJson(FileUtils::getInstance()->getWritablePath() + "tcsUserData.json", m_json_userData_Ptr);
}

vector<int> CTCSInfoManager::getHistroyScore(int num)
{
    vector<int> _vecI_hisScore;
    XJsonValuePtr _xJVP_first_Ptr =  m_json_userData_Ptr->getValue("first");
    if (XJSONTYPE_NONE != _xJVP_first_Ptr->getType())
    {
        _vecI_hisScore.push_back(_xJVP_first_Ptr->getObjectValue()->getValue("score")->getLongValue());
    }
    else
    {
        _vecI_hisScore.push_back(0);
        _vecI_hisScore.push_back(0);
        _vecI_hisScore.push_back(0);
        return _vecI_hisScore;
    }
    XJsonValuePtr _xJVP_second_Ptr =  m_json_userData_Ptr->getValue("second");
    if (XJSONTYPE_NONE != _xJVP_second_Ptr->getType())
    {
        _vecI_hisScore.push_back(_xJVP_second_Ptr->getObjectValue()->getValue("score")->getLongValue());
    }
    else
    {
        _vecI_hisScore.push_back(0);
        _vecI_hisScore.push_back(0);
        return _vecI_hisScore;
    }
    XJsonValuePtr _xJVP_third_Ptr =  m_json_userData_Ptr->getValue("third");
    if (XJSONTYPE_NONE != _xJVP_third_Ptr->getType())
    {
        _vecI_hisScore.push_back(_xJVP_third_Ptr->getObjectValue()->getValue("score")->getLongValue());
    }
    else
    {
        _vecI_hisScore.push_back(0);
        return _vecI_hisScore;
    }
    return _vecI_hisScore;
}


XFILETOOL::XJsonPtr CTCSInfoManager::genAHistory(int score, int times, int useTime)
{
    long _l_nowSecond, _l_nowMSecond;

    PUB_getNowTime(_l_nowSecond, _l_nowMSecond);
    
    XJsonPtr _xJson_score_Ptr = make_shared<XJson>();
    XJsonValuePtr _xJsonValue_timeValue_Ptr = make_shared<XJsonValue>();
    _xJsonValue_timeValue_Ptr->setStringValue(PUB_second2String(_l_nowSecond));
    _xJson_score_Ptr->setKeyValue("time", _xJsonValue_timeValue_Ptr);
    XJsonValuePtr _xJsonValue_scoreValuePtr = make_shared<XJsonValue>();;
    _xJsonValue_scoreValuePtr->setLongValue(score);
    _xJson_score_Ptr->setKeyValue("score", _xJsonValue_scoreValuePtr);
    XJsonValuePtr _xJsonValue_numsValuePtr = make_shared<XJsonValue>();;
    _xJsonValue_numsValuePtr->setLongValue(times);
    _xJson_score_Ptr->setKeyValue("num", _xJsonValue_numsValuePtr);
    XJsonValuePtr _xJsonValue_useTimeValuePtr = make_shared<XJsonValue>();;
    _xJsonValue_useTimeValuePtr->setLongValue(useTime);
    _xJson_score_Ptr->setKeyValue("useTime", _xJsonValue_useTimeValuePtr);
    
    return _xJson_score_Ptr;
}


bool CTCSInfoManager::isOpenSound()
{
    return UserDefault::getInstance()->getBoolForKey("TCS_SOUND", true);
}

void CTCSInfoManager::setSound(bool isOpen)
{
    UserDefault::getInstance()->setBoolForKey("TCS_SOUND", isOpen);
}

bool CTCSInfoManager::isOpenShake()
{
    return UserDefault::getInstance()->getBoolForKey("TCS_SHAKE", true);
}

void CTCSInfoManager::setShake(bool isOpen)
{
    UserDefault::getInstance()->setBoolForKey("TCS_SHAKE", isOpen);
}

int CTCSInfoManager::getOpWay()
{
    return UserDefault::getInstance()->getIntegerForKey("TCS_OpWay", 0);
}

void CTCSInfoManager::setOpWay(int type)
{
    UserDefault::getInstance()->setIntegerForKey("TCS_OpWay", type);
}

void CTCSInfoManager::vibrate(int type)
{
    if (!isOpenShake())
    {
        return;
    }
    if (type == 0)
    {
        PUB_Vibrate();
    }
    else if (type == 1)
    {
        PUB_LongVibrate();
    }
}
