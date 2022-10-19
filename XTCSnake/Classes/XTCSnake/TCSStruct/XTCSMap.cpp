
#include "XTCSMap.hpp"

#include "XString.h"
#include "XTime.h"
#include "XLog.h"

#include "XTCSInfoManager.hpp"
#include "XTCSSnake.hpp"

USING_NS_CC;
using namespace XDESIGNPATTERBASE;
using namespace XSTRINGTOOL;
using namespace XTIMETOOL;
using namespace std;


CTCSMapFSM::CTCSMapFSM(std::string name, XDESIGNPATTERBASE::XIStatePtr defaultState)
    : m_str_name(name){
    m_state_defaultState_ptr = defaultState;
    m_state_curState_ptr = defaultState;
}
    
CTCSMapFSM::CTCSMapFSM()
{
    
}

CTCSShowSnakeState::CTCSShowSnakeState(std::string name)
{
    m_str_name = name;
    setTag(STATETAG_MAP_SHOWSNAKE);
}

void CTCSShowSnakeState::onUpdate(float deltaTime)
{
    auto _cTCSMapFSM_temp_ptr = dynamic_cast<CTCSMapFSM*>(this->getParent().get());
    auto _cTCSMap_temp_ptr = _cTCSMapFSM_temp_ptr->getParent();
    _cTCSMap_temp_ptr->showSnake();
}

CTCSEatAndAddFoodState::CTCSEatAndAddFoodState(std::string name)
{
    m_str_name = name;
    setTag(STATETAG_MAP_EATFOOD);
}
    
void CTCSEatAndAddFoodState::onEnter(XDESIGNPATTERBASE::XIStatePtr prev)
{
    auto _cTCSMapFSM_temp_ptr = dynamic_cast<CTCSMapFSM*>(this->getParent().get());
    auto _cTCSMap_temp_ptr = _cTCSMapFSM_temp_ptr->getParent();
    _cTCSMap_temp_ptr->showSnake();
    _cTCSMap_temp_ptr->addFood();
}

void CTCSEatAndAddFoodState::onUpdate(float deltaTime)
{
    
}

void CTCSEatAndAddFoodState::onExit(XDESIGNPATTERBASE::XIStatePtr next)
{
    //XLOG_DEBUG("%s:onExit", m_str_name.c_str());
    //auto _cTCSMapFSM_temp_ptr = dynamic_cast<CTCSMapFSM*>(this->getParent().get());
    //auto _cTCSMap_temp_ptr = _cTCSMapFSM_temp_ptr->getParent();
    //_cTCSMap_temp_ptr->addFood();
    
}

CTCSGameOverState::CTCSGameOverState(std::string name)
{
    m_str_name = name;
    setTag(STATETAG_MAP_GAMEOVER);
}
    
void CTCSGameOverState::onEnter(XDESIGNPATTERBASE::XIStatePtr prev)
{
    XLOG_DEBUG("%s:onEnter, gameOver", m_str_name.c_str());
    auto _cTCSMapFSM_temp_ptr = dynamic_cast<CTCSMapFSM*>(this->getParent().get());
    auto _cTCSMap_temp_ptr = _cTCSMapFSM_temp_ptr->getParent();
    _cTCSMap_temp_ptr->gameOver();
    TCSINFO->vibrate(1);
}

void CTCSGameOverState::onExit(XDESIGNPATTERBASE::XIStatePtr next)
{
//    auto _cTCSMapFSM_temp_ptr = dynamic_cast<CTCSMapFSM*>(this->getParent().get());
//    auto _cTCSMap_temp_ptr = _cTCSMapFSM_temp_ptr->getParent();
//    _cTCSMap_temp_ptr->setGameState(GAMESTATE_TCS_GAMESTART);
    XLOG_DEBUG("%s:onExit, gameBegin", m_str_name.c_str());
}

CTCSShowSnake2EatAndAddFood::CTCSShowSnake2EatAndAddFood(std::string name, CTCSShowSnakeStatePtr fromState, CTCSEatAndAddFoodStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 2;
}
    
bool CTCSShowSnake2EatAndAddFood::onCheck()
{
    auto _cTCSMapFsm_temp_ptr = dynamic_cast<CTCSMapFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSMap_temp_ptr = dynamic_cast<CTCSMap*>(_cTCSMapFsm_temp_ptr->getParent());
    if (!_cTCSMap_temp_ptr->isExistFood())
    {
        return true;
    }
    return false;
}

bool CTCSShowSnake2EatAndAddFood::onCompleteCallBack()
{
    return true;
}


CTCSEatAndAddFood2GameOver::CTCSEatAndAddFood2GameOver(std::string name, CTCSEatAndAddFoodStatePtr fromState, CTCSGameOverStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 1;
}
    
bool CTCSEatAndAddFood2GameOver::onCheck()
{
    auto _cTCSMapFsm_temp_ptr = dynamic_cast<CTCSMapFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSMap_temp_ptr = dynamic_cast<CTCSMap*>(_cTCSMapFsm_temp_ptr->getParent());
    auto _cTCSSnake_temp_ptr = _cTCSMap_temp_ptr->getSnake();
    if (_cTCSMap_temp_ptr->isDeath())
    {
        return true;
    }
    return false;
}

bool CTCSEatAndAddFood2GameOver::onCompleteCallBack()
{
    return false;
}

CTCSEatAndAddFood2ShowSnake::CTCSEatAndAddFood2ShowSnake(std::string name, CTCSEatAndAddFoodStatePtr fromState, CTCSShowSnakeStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 3;
}
    
bool CTCSEatAndAddFood2ShowSnake::onCheck()
{
    auto _cTCSMapFsm_temp_ptr = dynamic_cast<CTCSMapFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSMap_temp_ptr = dynamic_cast<CTCSMap*>(_cTCSMapFsm_temp_ptr->getParent());
    if (_cTCSMap_temp_ptr->isExistFood())
    {
        return true;
    }
    return false;
}

bool CTCSEatAndAddFood2ShowSnake::onCompleteCallBack()
{
    return false;
}


CTCSEatAndAddFood2EatAndAddFood::CTCSEatAndAddFood2EatAndAddFood(std::string name, CTCSEatAndAddFoodStatePtr fromState, CTCSEatAndAddFoodStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 2;
}
    
bool CTCSEatAndAddFood2EatAndAddFood::onCheck()
{
    auto _cTCSMapFsm_temp_ptr = dynamic_cast<CTCSMapFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSMap_temp_ptr = dynamic_cast<CTCSMap*>(_cTCSMapFsm_temp_ptr->getParent());
    if (!_cTCSMap_temp_ptr->isExistFood())
    {
        return true;
    }
    return false;
}

bool CTCSEatAndAddFood2EatAndAddFood::onCompleteCallBack()
{
    return true;
}

CTCSShowSnake2GameOver::CTCSShowSnake2GameOver(std::string name, CTCSShowSnakeStatePtr fromState, CTCSGameOverStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 1;
}
    
bool CTCSShowSnake2GameOver::onCheck()
{
    auto _cTCSMapFsm_temp_ptr = dynamic_cast<CTCSMapFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSMap_temp_ptr = dynamic_cast<CTCSMap*>(_cTCSMapFsm_temp_ptr->getParent());
    auto _cTCSSnake_temp_ptr = _cTCSMap_temp_ptr->getSnake();
    if (_cTCSMap_temp_ptr->isDeath())
    {
        return true;
    }
    return false;
}

bool CTCSShowSnake2GameOver::onCompleteCallBack()
{
    return false;
}

CTCSGameOver2ShowSnake::CTCSGameOver2ShowSnake(std::string name, CTCSGameOverStatePtr fromState, CTCSShowSnakeStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 1;
}
    
bool CTCSGameOver2ShowSnake::onCheck()
{
    return false;
}

bool CTCSGameOver2ShowSnake::onCompleteCallBack()
{
    return false;
};

CTCSGameOver2EatAndAddFood::CTCSGameOver2EatAndAddFood(std::string name, CTCSGameOverStatePtr fromState, CTCSEatAndAddFoodStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 2;
}
    
bool CTCSGameOver2EatAndAddFood::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSMapFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSMap_temp_ptr = dynamic_cast<CTCSMap*>(_cTCSFsm_temp_ptr->getParent());
    if (GAMESTATE_TCS_GAMESTART == _cTCSMap_temp_ptr->getGameState())
    {
        return true;
    }
    return false;
}

bool CTCSGameOver2EatAndAddFood::onCompleteCallBack()
{
    return true;
}

CTCSMap::CTCSMap()
{
}

CTCSMap::~CTCSMap()
{
}

bool CTCSMap::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    initData();
    initUI();
    initSnake();
    initFSM();
    showSnake();
    
    this->scheduleUpdate();
    
    return true;
}

void CTCSMap::onEnter()
{
    Node::onEnter();
}

STCSGAMESTATE CTCSMap::getGameState()
{
    return m_sTCSGameState_state;
}

void CTCSMap::setGameState(STCSGAMESTATE state)
{
    m_sTCSGameState_state = state;
}

void CTCSMap::initData()
{
    for (int j = 0; j < XTCSMAP_HEIGHT; j++)
    {
        for (int i = 0; i < XTCSMAP_WIDTH; i++)
        {
            if (m_seqSpMap_map.size() <= j * XTCSMAP_WIDTH + i)
            {
                break;
            }
            m_seqSpMap_map.at(j * XTCSMAP_WIDTH + i)->removeFromParent();
            m_mapContent_map[j][i] = MAPCONTENT_NONE;
        }
    }
    m_seqTT_dir.clear();
    m_seqSpMap_map.clear();
    m_i_times = 0;
    m_i_foodPos = -1;
    m_sTCSGameState_state = GAMESTATE_TCS_GAMEOVER;
}

void CTCSMap::initUI()
{
    for (int j = 0; j < XTCSMAP_HEIGHT; j++)
    {
        for (int i = 0; i < XTCSMAP_WIDTH; i++)
        {
            auto _sp_map_ptr = Sprite::create("TCSGame/img_smallBg0.png");
            Label* _lb_temp_ptr = getTCSLabel(PUB_strformat("%d,%d,%d", j, i, j * XTCSMAP_WIDTH + i), "", 10);
            //_sp_map_ptr->addChild(_lb_temp_ptr, 10);
            _lb_temp_ptr->setPosition(_sp_map_ptr->getContentSize() * 0.5);
            this->addChild(_sp_map_ptr, 10);
            _sp_map_ptr->setPosition(Size((i + 0.5) * (_sp_map_ptr->getContentSize().width + 2), (XTCSMAP_HEIGHT - j - 0.5) * (_sp_map_ptr->getContentSize().height + 2)));
            m_seqSpMap_map.push_back(_sp_map_ptr);
        }
    }
}

void CTCSMap::initFSM()
{
    CTCSShowSnakeStatePtr _cTCSShowSnakeSt_show_Ptr = make_shared<CTCSShowSnakeState>("showSnakeState");
    CTCSEatAndAddFoodStatePtr _cTCSEatAndAddFoodSt_eat_Ptr = make_shared<CTCSEatAndAddFoodState>("eatAndAddFoodState");
    CTCSGameOverStatePtr _cTCSGameOverSt_gameOver_Ptr = make_shared<CTCSGameOverState>("showSnakeState");
    
    m_cTCSMFSM_action_Ptr = make_shared<CTCSMapFSM>("tcsMapFSM", _cTCSGameOverSt_gameOver_Ptr);
    m_cTCSMFSM_action_Ptr->setParent(this);
    m_cTCSMFSM_action_Ptr->addState(_cTCSGameOverSt_gameOver_Ptr);
    m_cTCSMFSM_action_Ptr->addState(_cTCSShowSnakeSt_show_Ptr);
    m_cTCSMFSM_action_Ptr->addState(_cTCSEatAndAddFoodSt_eat_Ptr);
    
    _cTCSGameOverSt_gameOver_Ptr->addTransition(make_shared<CTCSGameOver2ShowSnake>("gameOver2ShowSnake", _cTCSGameOverSt_gameOver_Ptr, _cTCSShowSnakeSt_show_Ptr));
    _cTCSGameOverSt_gameOver_Ptr->addTransition(make_shared<CTCSGameOver2EatAndAddFood>("gameOver2EatAndAddFood", _cTCSGameOverSt_gameOver_Ptr, _cTCSEatAndAddFoodSt_eat_Ptr));
    
    _cTCSShowSnakeSt_show_Ptr->addTransition(make_shared<CTCSShowSnake2GameOver>("showSnake2GameOver", _cTCSShowSnakeSt_show_Ptr, _cTCSGameOverSt_gameOver_Ptr));
    _cTCSShowSnakeSt_show_Ptr->addTransition(make_shared<CTCSShowSnake2EatAndAddFood>("showSnake2EatAndAddFood", _cTCSShowSnakeSt_show_Ptr, _cTCSEatAndAddFoodSt_eat_Ptr));
    
    _cTCSEatAndAddFoodSt_eat_Ptr->addTransition(make_shared<CTCSEatAndAddFood2GameOver>("eadAndAddFood2GameOver", _cTCSEatAndAddFoodSt_eat_Ptr, _cTCSGameOverSt_gameOver_Ptr));
    _cTCSEatAndAddFoodSt_eat_Ptr->addTransition(make_shared<CTCSEatAndAddFood2EatAndAddFood>("eadAndAddFood2EatAndAddFood", _cTCSEatAndAddFoodSt_eat_Ptr, _cTCSEatAndAddFoodSt_eat_Ptr));
    _cTCSEatAndAddFoodSt_eat_Ptr->addTransition(make_shared<CTCSEatAndAddFood2ShowSnake>("eadAndAddFood2ShowSnake", _cTCSEatAndAddFoodSt_eat_Ptr, _cTCSShowSnakeSt_show_Ptr));
}

void CTCSMap::initSnake()
{
    m_cTCSSnake_snake_Ptr = make_shared<CTCSSnake>();
    m_cTCSSnake_snake_Ptr->setMap(this);
    m_i_times = m_cTCSSnake_snake_Ptr->getSpeed() - 1;
}

void CTCSMap::update(float dt)
{
    m_i_times++;
    if (m_i_times >= m_cTCSSnake_snake_Ptr->getSpeed())
    {
        m_cTCSSnake_snake_Ptr->onUpdate(dt);
        m_cTCSMFSM_action_Ptr->onUpdate(dt);
        if (m_showScoreCallback)
        {
            m_showScoreCallback((m_cTCSSnake_snake_Ptr->getLength() - 2) * 100);
        }
        m_i_times = 0;
    }
}

void CTCSMap::addTurnTo(STCSTurnTo dir)
{
    LockGuard lock(m_mutex_turnTo);
    //m_seqTT_dir.clear();
    if (m_seqTT_dir.size() <= 1)
    {
        if (dir != TURNTO_NONE )
        {
            m_seqTT_dir.push_back(dir);
            moveNow();
        }
    }
}

STCSTurnTo CTCSMap::getTurnTo()
{
    LockGuard lock(m_mutex_turnTo);
    STCSTurnTo _sTCSTT_res = TURNTO_NONE;
    if (m_seqTT_dir.size() > 0)
    {
        _sTCSTT_res = m_seqTT_dir.front();
    }
    return _sTCSTT_res;
}

STCSTurnTo CTCSMap::popTurnTo()
{
    LockGuard lock(m_mutex_turnTo);
    STCSTurnTo _sTCSTT_res = TURNTO_NONE;
    if (m_seqTT_dir.size() > 0)
    {
        _sTCSTT_res = m_seqTT_dir.front();
        m_seqTT_dir.pop_front();
    }
    return _sTCSTT_res;
}

void CTCSMap::showSnake()
{
    ListSnakePos _listSnakePos_temp = m_cTCSSnake_snake_Ptr->getSnakePos();
    SnakePos _snakePos_tailPos = m_cTCSSnake_snake_Ptr->getTailPos();
    SnakePos _snakePos_headPos = m_cTCSSnake_snake_Ptr->getHeadPos();
    
//    if (m_i_foodPos != -1)
//    {
//        m_mapContent_map[m_i_foodPos % XTCSMAP_WIDTH][m_i_foodPos / XTCSMAP_WIDTH] = MAPCONTENT_FOOD;
//        m_seqSpMap_map[m_i_foodPos]->setTexture("TCSCom/img_food.png");
//    }
    
    int i = 0;
    for (auto pos : _listSnakePos_temp)
    {
        if (_listSnakePos_temp.size() - 1 == i)
        {
            m_mapContent_map[pos.first][pos.second] = MAPCONTENT_HEAD;
            m_seqSpMap_map[pos.first + pos.second * XTCSMAP_WIDTH]->setTexture("TCSCom/img_smallHead.png");
            if (DIRECTION_DOWN == m_cTCSSnake_snake_Ptr->getDir())
            {
                m_seqSpMap_map[pos.first + pos.second * XTCSMAP_WIDTH]->setRotation(180);
            }
            else if (DIRECTION_UP == m_cTCSSnake_snake_Ptr->getDir())
            {
                m_seqSpMap_map[pos.first + pos.second * XTCSMAP_WIDTH]->setRotation(0);
            }
            else if (DIRECTION_LEFT == m_cTCSSnake_snake_Ptr->getDir())
            {
                m_seqSpMap_map[pos.first + pos.second * XTCSMAP_WIDTH]->setRotation(270);
            }
            else if (DIRECTION_RIGHT == m_cTCSSnake_snake_Ptr->getDir())
            {
                m_seqSpMap_map[pos.first + pos.second * XTCSMAP_WIDTH]->setRotation(90);
            }
        }
        else
        {
            if (MAPCONTENT_BODY != m_mapContent_map[pos.first][pos.second])
            {
                m_mapContent_map[pos.first][pos.second] = MAPCONTENT_BODY;
                m_seqSpMap_map[pos.first + pos.second * XTCSMAP_WIDTH]->setTexture("TCSCom/img_smallBody.png");
            }
        }
        i++;
    }
    
    if (_snakePos_tailPos.first != -1 && _snakePos_tailPos.second != -1 && _snakePos_tailPos != _snakePos_headPos)
    {
        if (m_mapContent_map[_snakePos_tailPos.first][_snakePos_tailPos.second] != MAPCONTENT_FOOD)
        {
            m_mapContent_map[_snakePos_tailPos.first][_snakePos_tailPos.second] = MAPCONTENT_NONE;
            m_seqSpMap_map[_snakePos_tailPos.first + _snakePos_tailPos.second * XTCSMAP_WIDTH]->setTexture("TCSGame/img_smallBg0.png");
        }
    }
    //m_cTCSSnake_snake_Ptr->deleteTail();
}

STCSDirection CTCSMap::getCurDir()
{
    return m_cTCSSnake_snake_Ptr->getDir();
}

void CTCSMap::addFood()
{
    while (true)
    {
        m_i_foodPos = PUB_getRandInt(0, XTCSMAP_WIDTH * XTCSMAP_HEIGHT - 1);
        if (m_mapContent_map[m_i_foodPos % XTCSMAP_WIDTH][m_i_foodPos / XTCSMAP_WIDTH] == MAPCONTENT_NONE)
        {
            m_mapContent_map[m_i_foodPos % XTCSMAP_WIDTH][m_i_foodPos / XTCSMAP_WIDTH] = MAPCONTENT_FOOD;
            m_seqSpMap_map[m_i_foodPos]->setTexture("TCSCom/img_smallFood.png");
            XLOG_DEBUG("addFood, x:%d, y:%d", m_i_foodPos % XTCSMAP_WIDTH, m_i_foodPos / XTCSMAP_WIDTH);
            break;
        }
    }
}

int CTCSMap::getFoodPos()
{
    return m_i_foodPos;
}

void CTCSMap::clearFood()
{
    if (m_i_foodPos > -1 && m_i_foodPos < XTCSMAP_WIDTH * XTCSMAP_HEIGHT)
    {
        XLOG_DEBUG("clearFood, x:%d, y:%d", m_i_foodPos % XTCSMAP_WIDTH, m_i_foodPos / XTCSMAP_WIDTH);
        m_mapContent_map[m_i_foodPos % XTCSMAP_WIDTH][m_i_foodPos / XTCSMAP_WIDTH] = MAPCONTENT_NONE;
        m_seqSpMap_map[m_i_foodPos]->setTexture("TCSGame/img_smallBg0.png");
        m_i_foodPos = -1;
    }
}

bool CTCSMap::isExistFood()
{
    return m_i_foodPos != -1;
}

CTCSSnakePtr CTCSMap::getSnake()
{
    return m_cTCSSnake_snake_Ptr;
}

bool CTCSMap::isDeath()
{
    if((m_mapContent_map[m_cTCSSnake_snake_Ptr->getHeadPos().first][m_cTCSSnake_snake_Ptr->getHeadPos().second] == MAPCONTENT_BODY && m_cTCSSnake_snake_Ptr->getTailPos() != m_cTCSSnake_snake_Ptr->getHeadPos())|| GAMESTATE_TCS_GAMEOVER == m_sTCSGameState_state)
    {
        return true;
    }
    return false;
}

void CTCSMap::gameOver()
{
    if (m_showGameOverCallback)
    {
        m_showGameOverCallback((m_cTCSSnake_snake_Ptr->getLength() - 2) * 100);
    }
    initData();
    initUI();
    m_i_times = m_cTCSSnake_snake_Ptr->getSpeed() - 1;
}

void CTCSMap::moveNow()
{
    if (m_i_times < m_cTCSSnake_snake_Ptr->getSpeed() - 6)
    {
        m_i_times = m_cTCSSnake_snake_Ptr->getSpeed() - 6;
    }
    else if (m_i_times > m_cTCSSnake_snake_Ptr->getSpeed() - 1)
    {
        m_i_times = m_cTCSSnake_snake_Ptr->getSpeed() - 1;
    }
    //m_i_times = m_cTCSSnake_snake_Ptr->getSpeed() - 5;
}

void CTCSMap::setShowScoreCallBack(std::function<void(int)> cb)
{
    m_showScoreCallback = cb;
}

void CTCSMap::setShowGameOverCallBack(std::function<void(int)> cb)
{
    m_showGameOverCallback = cb;
}
