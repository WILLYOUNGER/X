#include "XTCSSoundManager.hpp"
#include "SimpleAudioEngine.h"
#include "XTCSInfoManager.hpp"
#include <string>

using namespace std;

static std::string g_LLKVoiceArray[CTCSSoundManager::TCS_SOUND_END] = {
    "",
    "TCSSound/tcsClick.mp3",
    "TCSSound/tcsEat.mp3",
    "TCSSound/tcsMusic.mp3",
};
CTCSSoundManager * CTCSSoundManager::m_pInstance = nullptr;
CTCSSoundManager * CTCSSoundManager::GetInstance()
{
    if (nullptr == m_pInstance)
    {
        m_pInstance = new CTCSSoundManager();
        m_pInstance->init();
    }
    return m_pInstance;
}
void CTCSSoundManager::Destroy()
{
    if (nullptr != m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}
bool CTCSSoundManager::init()
{
    return true;
}
CTCSSoundManager::~CTCSSoundManager()
{
}
void CTCSSoundManager::loadVoiceResource()
{
    //预加载音乐
    CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadEffect(g_LLKVoiceArray[TCS_SOUND_BUTTON].c_str());
    audio->preloadEffect(g_LLKVoiceArray[TCS_SOUND_EAT].c_str());
    audio->preloadEffect(g_LLKVoiceArray[TCS_SOUND_MUSIC].c_str());
}
void CTCSSoundManager::unloadVoiceResource()
{
    //卸载音乐
    CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->unloadEffect(g_LLKVoiceArray[TCS_SOUND_BUTTON].c_str());
    audio->unloadEffect(g_LLKVoiceArray[TCS_SOUND_EAT].c_str());
    audio->unloadEffect(g_LLKVoiceArray[TCS_SOUND_MUSIC].c_str());
}
void CTCSSoundManager::tcsPlayEffect(int _type)
{
    if (TCS_SOUND_BEGIN <_type && _type < TCS_SOUND_END && TCSINFO->isOpenSound())
    {
        CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playEffect(g_LLKVoiceArray[_type].c_str());
    }
}
void CTCSSoundManager::tcsSetEffectsVolume(float _fVolume)
{
       CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(_fVolume);
}
void CTCSSoundManager::tcsPlayBackgroundMusic(int _type)
{
    tcsSetBackgroundMusicVolume(1);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(g_LLKVoiceArray[_type].c_str(), true);
    if (!TCSINFO->isOpenSound())
    {
       CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
}
void CTCSSoundManager::tcsPauseBackgroundMusic(int _type)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void CTCSSoundManager::tcsResumeBackgroundMusic(int _type)
{
    if (TCSINFO->isOpenSound())
    {
        if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
        {
             CCLOG("");
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}
void CTCSSoundManager::tcsStopBackgroundMusic(int _type)
{
       CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}
void CTCSSoundManager::tcsSetBackgroundMusicVolume(float _fVolume)
{
       CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_fVolume);
}
