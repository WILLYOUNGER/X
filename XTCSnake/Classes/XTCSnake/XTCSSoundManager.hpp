
#ifndef XTCSNAKE_XTCSSOUNDMANAGER_H
#define XTCSNAKE_XTCSSOUNDMANAGER_H

#include "cocos2d.h"

USING_NS_CC;
class CTCSSoundManager
{
public:
    static CTCSSoundManager* GetInstance();
    void Destroy();
    bool init();
    virtual ~CTCSSoundManager();
    //音效
    enum TCS_SOUND_ENUM
    {
          TCS_SOUND_BEGIN = 0,
          TCS_SOUND_BUTTON,    //按钮
          TCS_SOUND_EAT,
          TCS_SOUND_MUSIC,
          TCS_SOUND_END,
    };
    public:
    //声音管理
    //装载声音
    void loadVoiceResource();
    //卸载声音
    void unloadVoiceResource();;
    //播放声音
    void tcsPlayEffect(int _type);
    //调整声音音量
    void tcsSetEffectsVolume(float _fVolume);
    //播放背景音乐
    void tcsPlayBackgroundMusic(int _type);
    //暂停背景音乐
    void tcsPauseBackgroundMusic(int _type);
    //继续播放背景音乐
    void tcsResumeBackgroundMusic(int _type);
    //关闭背景音乐
    void tcsStopBackgroundMusic(int _type);
    //调整背景音乐音量
    void tcsSetBackgroundMusicVolume(float _fVolume);
private:
    static CTCSSoundManager * m_pInstance;
};
#define TCSSoundInstance() CTCSSoundManager::GetInstance()


#endif /* XTCSNAKE_XTCSSOUNDMANAGER_H */
