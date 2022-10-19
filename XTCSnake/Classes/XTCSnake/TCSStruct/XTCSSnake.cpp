//
//  XTCSSnake.cpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/22.
//

#include "XTCSSnake.hpp"

#include "XTime.h"
#include "XLog.h"

#include "XTCSMap.hpp"
#include "XTCSSoundManager.hpp"

using namespace XTIMETOOL;
using namespace XDESIGNPATTERBASE;
using namespace std;


CTCSSnakeFSM::CTCSSnakeFSM(std::string name, XDESIGNPATTERBASE::XIStatePtr defaultState) :
    m_str_name(name)
{
    //addState(defaultState);
    m_state_defaultState_ptr = defaultState;
    m_state_curState_ptr = defaultState;
}
    
CTCSSnakeFSM::CTCSSnakeFSM()
{
    
}

CTCSMoveState::CTCSMoveState(std::string name)
{
    m_str_name = name;
}
    
void CTCSMoveState::onUpdate(float deltaTime)
{
    auto _cTCSSnakeFSM_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(this->getParent().get());
    auto _cTCSSnake_temp_ptr = _cTCSSnakeFSM_temp_ptr->getParent();
    _cTCSSnake_temp_ptr->move();
}

CTCSTurnToState::CTCSTurnToState(std::string name)
{
    m_str_name = name;
}

void CTCSTurnToState::onEnter(XDESIGNPATTERBASE::XIStatePtr prev)
{
    auto _cTCSSnakeFSM_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(this->getParent().get());
    auto _cTCSSnake_temp_ptr = _cTCSSnakeFSM_temp_ptr->getParent();
    auto _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    auto _sTCSDir_curDir = _cTCSSnake_temp_ptr->getDir();
    auto _cTCSTT_temp = _cTCSMap_temp_ptr->popTurnTo();
    if (_cTCSTT_temp == TURNTO_LEFT)
    {
        if (_sTCSDir_curDir == DIRECTION_UP)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_LEFT);
        }
        else if (_sTCSDir_curDir == DIRECTION_DOWN)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_RIGHT);
        }
        else if (_sTCSDir_curDir == DIRECTION_LEFT)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_DOWN);
        }
        else if (_sTCSDir_curDir == DIRECTION_RIGHT)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_UP);
        }
    }
    else if (_cTCSTT_temp == TURNTO_RIGHT)
    {
        if (_sTCSDir_curDir == DIRECTION_UP)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_RIGHT);
        }
        else if (_sTCSDir_curDir == DIRECTION_DOWN)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_LEFT);
        }
        else if (_sTCSDir_curDir == DIRECTION_LEFT)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_UP);
        }
        else if (_sTCSDir_curDir == DIRECTION_RIGHT)
        {
            _cTCSSnake_temp_ptr->setDir(DIRECTION_DOWN);
        }
    }
}

void CTCSTurnToState::onUpdate(float deltaTime)
{
    auto _cTCSSnakeFSM_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(this->getParent().get());
    auto _cTCSSnake_temp_ptr = _cTCSSnakeFSM_temp_ptr->getParent();
    _cTCSSnake_temp_ptr->move();
}

CTCSEatState::CTCSEatState(std::string name)
{
    m_str_name = name;
}
    
void CTCSEatState::onEnter(XDESIGNPATTERBASE::XIStatePtr prev)
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(this->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    auto _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    _cTCSSnake_temp_ptr->addLength();
    if (needAddSpeed(_cTCSSnake_temp_ptr->getSpeed(), _cTCSSnake_temp_ptr->getLength()))
    {
        _cTCSSnake_temp_ptr->addSpeed();
    }
    _cTCSMap_temp_ptr->clearFood();
    TCSSoundInstance()->tcsPlayEffect(CTCSSoundManager::TCS_SOUND_EAT);
}

bool CTCSEatState::needAddSpeed(int nowSpeed, int nowLength)
{
    int _i_addLength = 99999;
    bool _b_res = false;
    switch (nowSpeed) {
        case 15:
            _i_addLength = 3;
            break;
        case 14:
            _i_addLength = 7;
            break;
        case 13:
            _i_addLength = 12;
            break;
        case 12:
            _i_addLength = 17;
            break;
        case 11:
            _i_addLength = 22;
            break;
        case 10:
            _i_addLength = 27;
            break;
        case 9:
            _i_addLength = 32;
            break;
        case 8:
            _i_addLength = 37;
            break;
        default:
            break;
    }
    if (nowLength >= _i_addLength)
    {
        _b_res = true;
    }
    return _b_res;
}

void CTCSEatState::onUpdate(float deltaTime)
{
    XLOG_DEBUG("%s:onEnter, eat", m_str_name.c_str());
    auto _cTCSSnakeFSM_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(this->getParent().get());
    auto _cTCSSnake_temp_ptr = _cTCSSnakeFSM_temp_ptr->getParent();
    _cTCSSnake_temp_ptr->move();
}

CTCSDeathState::CTCSDeathState(std::string name)
{
    m_str_name = name;
}
    
void CTCSDeathState::onEnter(XDESIGNPATTERBASE::XIStatePtr prev)
{
    
}

void CTCSDeathState::onExit(XDESIGNPATTERBASE::XIStatePtr prev)
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(this->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    _cTCSSnake_temp_ptr->death();
}

CTCSMove2TurnTo::CTCSMove2TurnTo(std::string name, CTCSMoveStatePtr fromState, CTCSTurnToStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 2;
}
    
bool CTCSMove2TurnTo::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (TURNTO_NONE != _cTCSMap_temp_ptr->getTurnTo())
    {
        return true;
    }
    return false;
}

bool CTCSMove2TurnTo::onCompleteCallBack()
{
    return true;
}

CTCSTurnTo2Death::CTCSTurnTo2Death(std::string name, CTCSTurnToStatePtr fromState, CTCSDeathStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 1;
}
    
bool CTCSTurnTo2Death::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (GAMESTATE_TCS_GAMEOVER == _cTCSMap_temp_ptr->getGameState())
    {
        return true;
    }
    return false;
}

bool CTCSTurnTo2Death::onCompleteCallBack()
{
    return false;
}

CTCSTurnTo2Move::CTCSTurnTo2Move(std::string name, CTCSTurnToStatePtr fromState, CTCSMoveStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 4;
}
    
bool CTCSTurnTo2Move::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (TURNTO_NONE == _cTCSMap_temp_ptr->getTurnTo())
    {
        SnakePos _snakePos_head = _cTCSSnake_temp_ptr->getHeadPos();
        
        STCSDirection _cSTCDir_temp = _cTCSSnake_temp_ptr->getDir();
        if (DIRECTION_UP == _cSTCDir_temp)
        {
            _snakePos_head.second--;
        }
        else if (DIRECTION_DOWN == _cSTCDir_temp)
        {
            _snakePos_head.second++;
        }
        else if (DIRECTION_LEFT == _cSTCDir_temp)
        {
            _snakePos_head.first--;
        }
        else if (DIRECTION_RIGHT == _cSTCDir_temp)
        {
            _snakePos_head.first++;
        }
        
        if (_snakePos_head.second * XTCSMAP_WIDTH + _snakePos_head.first != _cTCSMap_temp_ptr->getFoodPos())
        {
            return true;
        }
        
        return false;
    }
    return false;
}

bool CTCSTurnTo2Move::onCompleteCallBack()
{
    return false;
}

CTCSTurnTo2TurnTo::CTCSTurnTo2TurnTo(std::string name, CTCSTurnToStatePtr fromState, CTCSTurnToStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 2;
}
    
bool CTCSTurnTo2TurnTo::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (TURNTO_NONE != _cTCSMap_temp_ptr->getTurnTo())
    {
        return true;
    }
    return false;
}

bool CTCSTurnTo2TurnTo::onCompleteCallBack()
{
    return true;
}

CTCSTurnTo2Eat::CTCSTurnTo2Eat(std::string name, CTCSTurnToStatePtr fromState, CTCSEatStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 3; 
}
    
bool CTCSTurnTo2Eat::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    SnakePos _snakePos_head = _cTCSSnake_temp_ptr->getHeadPos();
    
    STCSDirection _cSTCDir_temp = _cTCSSnake_temp_ptr->getDir();
    if (DIRECTION_UP == _cSTCDir_temp)
    {
        if (_snakePos_head.second - 1 >= 0)
        {
            _snakePos_head.second --;
        }
        else
        {
            _snakePos_head.second = XTCSMAP_HEIGHT - 1;
        }
    }
    else if (DIRECTION_DOWN == _cSTCDir_temp)
    {
        if (_snakePos_head.second + 1 <= XTCSMAP_HEIGHT - 1)
        {
            _snakePos_head.second ++;
        }
        else
        {
            _snakePos_head.second = 0;
        }
    }
    else if (DIRECTION_LEFT == _cSTCDir_temp)
    {
        if (_snakePos_head.first - 1 >= 0)
        {
            _snakePos_head.first --;
        }
        else
        {
            _snakePos_head.first = XTCSMAP_WIDTH - 1;
        }
    }
    else if (DIRECTION_RIGHT == _cSTCDir_temp)
    {
        if (_snakePos_head.first + 1 <= XTCSMAP_WIDTH - 1)
        {
            _snakePos_head.first ++;
        }
        else
        {
            _snakePos_head.first = 0;
        }
    }
    
    if (_snakePos_head.second * XTCSMAP_WIDTH + _snakePos_head.first == _cTCSMap_temp_ptr->getFoodPos())
    {
        return true;
    }
    return false;
}

bool CTCSTurnTo2Eat::onCompleteCallBack()
{
    return true;
}


CTCSMove2Eat::CTCSMove2Eat(std::string name, CTCSMoveStatePtr fromState, CTCSEatStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 3;
}
    
bool CTCSMove2Eat::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    SnakePos _snakePos_head = _cTCSSnake_temp_ptr->getHeadPos();
    
    STCSDirection _cSTCDir_temp = _cTCSSnake_temp_ptr->getDir();
    if (DIRECTION_UP == _cSTCDir_temp)
    {
        if (_snakePos_head.second - 1 >= 0)
        {
            _snakePos_head.second --;
        }
        else
        {
            _snakePos_head.second = XTCSMAP_HEIGHT - 1;
        }
    }
    else if (DIRECTION_DOWN == _cSTCDir_temp)
    {
        if (_snakePos_head.second + 1 <= XTCSMAP_HEIGHT - 1)
        {
            _snakePos_head.second ++;
        }
        else
        {
            _snakePos_head.second = 0;
        }
    }
    else if (DIRECTION_LEFT == _cSTCDir_temp)
    {
        if (_snakePos_head.first - 1 >= 0)
        {
            _snakePos_head.first --;
        }
        else
        {
            _snakePos_head.first = XTCSMAP_WIDTH - 1;
        }
    }
    else if (DIRECTION_RIGHT == _cSTCDir_temp)
    {
        if (_snakePos_head.first + 1 <= XTCSMAP_WIDTH - 1)
        {
            _snakePos_head.first ++;
        }
        else
        {
            _snakePos_head.first = 0;
        }
    }

    if (_snakePos_head.second * XTCSMAP_WIDTH + _snakePos_head.first == _cTCSMap_temp_ptr->getFoodPos())
    {
        return true;
    }
    return false;
}

bool CTCSMove2Eat::onCompleteCallBack()
{
    return true;
}


CTCSEat2Death::CTCSEat2Death(std::string name, CTCSEatStatePtr fromState, CTCSDeathStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 1;
}
    
bool CTCSEat2Death::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (GAMESTATE_TCS_GAMEOVER == _cTCSMap_temp_ptr->getGameState())
    {
        return true;
    }
    return false;
}

bool CTCSEat2Death::onCompleteCallBack()
{
    return false;
}

CTCSEat2TurnTo::CTCSEat2TurnTo(std::string name, CTCSEatStatePtr fromState, CTCSTurnToStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 2;
}
    
bool CTCSEat2TurnTo::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (TURNTO_NONE != _cTCSMap_temp_ptr->getTurnTo())
    {
        return true;
    }
    return false;
}

bool CTCSEat2TurnTo::onCompleteCallBack()
{
    return true;
}

CTCSEat2Eat::CTCSEat2Eat(std::string name, CTCSEatStatePtr fromState, CTCSEatStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 3;
}

bool CTCSEat2Eat::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    SnakePos _snakePos_head = _cTCSSnake_temp_ptr->getHeadPos();
    
    STCSDirection _cSTCDir_temp = _cTCSSnake_temp_ptr->getDir();
    if (DIRECTION_UP == _cSTCDir_temp)
    {
        if (_snakePos_head.second - 1 >= 0)
        {
            _snakePos_head.second --;
        }
        else
        {
            _snakePos_head.second = XTCSMAP_HEIGHT - 1;
        }
    }
    else if (DIRECTION_DOWN == _cSTCDir_temp)
    {
        if (_snakePos_head.second + 1 <= XTCSMAP_HEIGHT - 1)
        {
            _snakePos_head.second ++;
        }
        else
        {
            _snakePos_head.second = 0;
        }
    }
    else if (DIRECTION_LEFT == _cSTCDir_temp)
    {
        if (_snakePos_head.first - 1 >= 0)
        {
            _snakePos_head.first --;
        }
        else
        {
            _snakePos_head.first = XTCSMAP_WIDTH - 1;
        }
    }
    else if (DIRECTION_RIGHT == _cSTCDir_temp)
    {
        if (_snakePos_head.first + 1 <= XTCSMAP_WIDTH - 1)
        {
            _snakePos_head.first ++;
        }
        else
        {
            _snakePos_head.first = 0;
        }
    }
    
    if (_snakePos_head.second * XTCSMAP_WIDTH + _snakePos_head.first == _cTCSMap_temp_ptr->getFoodPos())
    {
        return true;
    }
    return false;
}

bool CTCSEat2Eat::onCompleteCallBack()
{
    return true;
}


CTCSEat2Move::CTCSEat2Move(std::string name, CTCSEatStatePtr fromState, CTCSMoveStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 4;
}
    
bool CTCSEat2Move::onCheck()
{
    return true;
}

bool CTCSEat2Move::onCompleteCallBack()
{
    return false;
}

CTCSMove2Death::CTCSMove2Death(std::string name, CTCSMoveStatePtr fromState, CTCSDeathStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 1;
}
    
bool CTCSMove2Death::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (GAMESTATE_TCS_GAMEOVER == _cTCSMap_temp_ptr->getGameState())
    {
        return true;
    }
    return false;
}

bool CTCSMove2Death::onCompleteCallBack()
{
    return false;
}


CTCSDeath2Move::CTCSDeath2Move(std::string name, CTCSDeathStatePtr fromState, CTCSMoveStatePtr toState)
{
    m_str_name = name;
    m_state_fromState_ptr = fromState;
    m_state_toState_ptr = toState;
    m_i_order = 1;
}
    
bool CTCSDeath2Move::onCheck()
{
    auto _cTCSFsm_temp_ptr = dynamic_cast<CTCSSnakeFSM*>(m_state_fromState_ptr->getParent().get());
    auto _cTCSSnake_temp_ptr = dynamic_cast<CTCSSnake*>(_cTCSFsm_temp_ptr->getParent());
    CTCSMap* _cTCSMap_temp_ptr = _cTCSSnake_temp_ptr->getMap();
    if (GAMESTATE_TCS_GAMESTART == _cTCSMap_temp_ptr->getGameState())
    {
        return true;
    }
    return false;
}

bool CTCSDeath2Move::onCompleteCallBack()
{
    return false;
}

CTCSSnake::CTCSSnake()
{
    initFSM();
    initData();
}

CTCSSnake::~CTCSSnake()
{
    
}

void CTCSSnake::initData()
{
    m_i_length = 2;
    m_i_speed = 15;
    m_snakePos_tailPos.first = -1;
    m_snakePos_tailPos.second = -1;
    m_snakePos_headPos.first = int(XTCSMAP_HEIGHT * 0.5);
    m_snakePos_headPos.second = int(XTCSMAP_WIDTH * 0.5);
    SnakePos m_snakePos_tailPos{-1, -1};
    SnakePos m_snakePos_lastTailPos{-1, -1};
    
    m_sTCSDir_dir = STCSDirection(1);
    m_listSnakePos_pos.clear();
    
    for (int i = 0; i < m_i_length; i++)
    {
        if (DIRECTION_UP == m_sTCSDir_dir)
        {
            m_listSnakePos_pos.push_front(make_pair(m_snakePos_headPos.first, m_snakePos_headPos.second + i));
        }
        else if (DIRECTION_DOWN == m_sTCSDir_dir)
        {
            m_listSnakePos_pos.push_front(make_pair(m_snakePos_headPos.first, m_snakePos_headPos.second - i));
        }
        else if (DIRECTION_LEFT == m_sTCSDir_dir)
        {
            m_listSnakePos_pos.push_front(make_pair(m_snakePos_headPos.first - i, m_snakePos_headPos.second));
        }
        else if (DIRECTION_RIGHT == m_sTCSDir_dir)
        {
            m_listSnakePos_pos.push_front(make_pair(m_snakePos_headPos.first + i, m_snakePos_headPos.second));
        }
    }
}

void CTCSSnake::initFSM()
{
    auto _cTCSMoveSt_move = make_shared<CTCSMoveState>("moveState");
    auto _cTCSTurnToSt_turnTo = make_shared<CTCSTurnToState>("turnToState");
    auto _cTCSEatSt_eat = make_shared<CTCSEatState>("eatState");
    auto _cTCSDeathSt_death = make_shared<CTCSDeathState>("deathState");
    
    m_cTCSSFSM_action_Ptr = make_shared<CTCSSnakeFSM>("tcsSnakeFSM", _cTCSDeathSt_death);
    m_cTCSSFSM_action_Ptr->setParent(this);
    m_cTCSSFSM_action_Ptr->addState(_cTCSDeathSt_death);
    m_cTCSSFSM_action_Ptr->addState(_cTCSTurnToSt_turnTo);
    m_cTCSSFSM_action_Ptr->addState(_cTCSEatSt_eat);
    m_cTCSSFSM_action_Ptr->addState(_cTCSMoveSt_move);
    
    _cTCSMoveSt_move->addTransition(make_shared<CTCSMove2Death>("move2Death", _cTCSMoveSt_move, _cTCSDeathSt_death));
    _cTCSMoveSt_move->addTransition(make_shared<CTCSMove2TurnTo>("move2TurnTo", _cTCSMoveSt_move, _cTCSTurnToSt_turnTo));
    _cTCSMoveSt_move->addTransition(make_shared<CTCSMove2Eat>("move2Eat", _cTCSMoveSt_move, _cTCSEatSt_eat));
    
    _cTCSTurnToSt_turnTo->addTransition(make_shared<CTCSTurnTo2Death>("turnTo2Death", _cTCSTurnToSt_turnTo, _cTCSDeathSt_death));
    _cTCSTurnToSt_turnTo->addTransition(make_shared<CTCSTurnTo2TurnTo>("turnTo2TurnTo", _cTCSTurnToSt_turnTo, _cTCSTurnToSt_turnTo));
    _cTCSTurnToSt_turnTo->addTransition(make_shared<CTCSTurnTo2Eat>("turnTo2Eat", _cTCSTurnToSt_turnTo, _cTCSEatSt_eat));
    _cTCSTurnToSt_turnTo->addTransition(make_shared<CTCSTurnTo2Move>("turnTo2Move", _cTCSTurnToSt_turnTo, _cTCSMoveSt_move));
    
    _cTCSEatSt_eat->addTransition(make_shared<CTCSEat2Death>("eat2Death", _cTCSEatSt_eat, _cTCSDeathSt_death));
    _cTCSEatSt_eat->addTransition(make_shared<CTCSEat2TurnTo>("eat2TurnTo", _cTCSEatSt_eat, _cTCSTurnToSt_turnTo));
    _cTCSEatSt_eat->addTransition(make_shared<CTCSEat2Eat>("eat2Eat", _cTCSEatSt_eat, _cTCSEatSt_eat));
    _cTCSEatSt_eat->addTransition(make_shared<CTCSEat2Move>("eat2Move", _cTCSEatSt_eat, _cTCSMoveSt_move));

    _cTCSDeathSt_death->addTransition(make_shared<CTCSDeath2Move>("death2Move", _cTCSDeathSt_death, _cTCSMoveSt_move));
}

void CTCSSnake::onUpdate(float dt)
{
    m_cTCSSFSM_action_Ptr->onUpdate(dt);
}

void CTCSSnake::setMap(CTCSMap* snakeMap)
{
    m_cTCSMap_map_ptr = snakeMap;
}

CTCSMap* CTCSSnake::getMap()
{
    return m_cTCSMap_map_ptr;
}

void CTCSSnake::setDir(STCSDirection dir)
{
    m_sTCSDir_dir = dir;
}

STCSDirection CTCSSnake::getDir()
{
    return m_sTCSDir_dir;
}

void CTCSSnake::setSpeed(int speed)
{
    m_i_speed = speed;
}

int CTCSSnake::getLength()
{
    return m_i_length;
}

int CTCSSnake::getSpeed()
{
    return m_i_speed;
}

SnakePos CTCSSnake::getHeadPos()
{
    return m_snakePos_headPos;
}

SnakePos CTCSSnake::getTailPos()
{
    return m_snakePos_tailPos;
}

void CTCSSnake::deleteTail()
{
    m_snakePos_lastTailPos = m_snakePos_tailPos;
    m_snakePos_tailPos.first = -1;
    m_snakePos_tailPos.second = -1;
}

ListSnakePos CTCSSnake::getSnakePos()
{
    return m_listSnakePos_pos;
}

void CTCSSnake::move()
{
    if (GAMESTATE_TCS_GAMEPAUSE == m_cTCSMap_map_ptr->getGameState())
    {
        return;
    }
    
    if (DIRECTION_UP == m_sTCSDir_dir)
    {
        if (m_snakePos_headPos.second - 1 >= 0)
        {
            m_snakePos_headPos.second --;
        }
        else
        {
            m_snakePos_headPos.second = XTCSMAP_HEIGHT - 1;
        }
    }
    else if (DIRECTION_DOWN == m_sTCSDir_dir)
    {
        if (m_snakePos_headPos.second + 1 < XTCSMAP_HEIGHT)
        {
            m_snakePos_headPos.second ++;
        }
        else
        {
            m_snakePos_headPos.second = 0;
        }
    }
    else if (DIRECTION_LEFT == m_sTCSDir_dir)
    {
        if (m_snakePos_headPos.first - 1 >= 0)
        {
            m_snakePos_headPos.first --;
        }
        else
        {
            m_snakePos_headPos.first = XTCSMAP_WIDTH - 1;
        }
    }
    else if (DIRECTION_RIGHT == m_sTCSDir_dir)
    {
        if (m_snakePos_headPos.first + 1 < XTCSMAP_WIDTH)
        {
            m_snakePos_headPos.first ++;
        }
        else
        {
            m_snakePos_headPos.first = 0;
        }
    }
    
    m_snakePos_lastTailPos = m_snakePos_tailPos;
    m_snakePos_tailPos = m_listSnakePos_pos.front();
    m_listSnakePos_pos.pop_front();
    m_listSnakePos_pos.push_back(make_pair(m_snakePos_headPos.first, m_snakePos_headPos.second));
    //XLOG_DEBUG("head Pos: x:%d, y:%d", m_snakePos_headPos.first, m_snakePos_headPos.second);
}

void CTCSSnake::addLength()
{
    m_listSnakePos_pos.push_front(make_pair(m_snakePos_tailPos.first, m_snakePos_tailPos.second));
    m_snakePos_tailPos = m_snakePos_lastTailPos;
    m_i_length++;
}

void CTCSSnake::addSpeed()
{
    if (m_i_speed >= 6)
    {
        m_i_speed--;
    }
}

void CTCSSnake::death()
{
    initData();
}
