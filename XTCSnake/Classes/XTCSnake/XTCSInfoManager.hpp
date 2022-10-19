//
//  XTCSInfoManager.hpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/16.
//

#ifndef XTCSNAKE_XTCSINFOMANAGER_H
#define XTCSNAKE_XTCSINFOMANAGER_H


#include "string"

#include <cocos2d.h>

#include "XFile.h"

extern cocos2d::Size getTCSScreenSize();
extern cocos2d::Size getTCSGameSize();
extern std::string getTCSLanguage(std::string key);
extern cocos2d::Label* getTCSLabel(std::string str, std::string font, int Size, int width = 0, int height = 0);

extern void TCSEnterGame();
extern void TCSEnterHome();

class CTCSInfoManager
{
public:
    static CTCSInfoManager* getInstance();
    
    cocos2d::Size getVisiableSize();
    
    cocos2d::Size getScreenSize();
    
    std::string getLanguage(std::string key);
    
    cocos2d::Color4B getColor4B(std::string typekey);
    
    void addScoreRecord(int score);
    
    //获取前num名次的分数(现在无论如何都为3)
    std::vector<int> getHistroyScore(int num);
    
    bool isOpenSound();
    
    void setSound(bool isOpen);
    
    bool isOpenShake();
    
    void setShake(bool isOpen);
    
    int getOpWay();
    
    void setOpWay(int type);
    
    void vibrate(int type);
private:
    CTCSInfoManager();
    
    ~CTCSInfoManager();
    
    void init();
    
    XFILETOOL::XJsonPtr genAHistory(int score, int times, int useTime);
private:
    XFILETOOL::XXmlTool m_xmlTool_xml;
    
    XFILETOOL::XJsonPtr m_json_userData_Ptr;
};

#define TCSINFO CTCSInfoManager::getInstance()

#endif /* XTCSNAKE_XTCSINFOMANAGER_H */
