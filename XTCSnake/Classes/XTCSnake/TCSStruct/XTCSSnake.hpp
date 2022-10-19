//
//  XTCSSnake.hpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/22.
//

#ifndef XTCSNAKE_XTCSSTRUCT_SNAKE_H
#define XTCSNAKE_XTCSSTRUCT_SNAKE_H

#include "XFiniteStateMachine.h"

#include "XTCSDataStruct.hpp"

class CTCSSnakeFSM : public XDESIGNPATTERBASE::XIFSMBase
{
public:
    CTCSSnakeFSM(std::string name, XDESIGNPATTERBASE::XIStatePtr defaultState);
    
    void setParent(CTCSSnake* parent) { m_cTCSSnake_parent_ptr = parent; }
    CTCSSnake* getParent() { return m_cTCSSnake_parent_ptr; }
    
private:
    CTCSSnakeFSM();
    
private:
    std::string m_str_name;
    
    CTCSSnake* m_cTCSSnake_parent_ptr;
};

//移动状态
class CTCSMoveState : public XDESIGNPATTERBASE::XIState
{
public:
    CTCSMoveState(std::string name);
    
    virtual void onUpdate(float deltaTime) override;
private:
};

//转向状态
class CTCSTurnToState : public XDESIGNPATTERBASE::XIState
{
public:
    CTCSTurnToState(std::string name);
    
    virtual void onEnter(XDESIGNPATTERBASE::XIStatePtr prev) override;
    
    virtual void onUpdate(float deltaTime) override;
private:
    
};

//吃状态
class CTCSEatState : public XDESIGNPATTERBASE::XIState
{
public:
    CTCSEatState(std::string name);
    
    virtual void onEnter(XDESIGNPATTERBASE::XIStatePtr prev) override;
    
    virtual void onUpdate(float deltaTime) override;
private:
    
    bool needAddSpeed(int nowSpeed, int nowLength);
};

//死亡状态
class CTCSDeathState : public XDESIGNPATTERBASE::XIState
{
public:
    CTCSDeathState(std::string name);
    
    virtual void onEnter(XDESIGNPATTERBASE::XIStatePtr prev) override;
    virtual void onExit(XDESIGNPATTERBASE::XIStatePtr prev) override;
private:
};

//移动转死亡
class CTCSMove2Death : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSMove2Death(std::string name, CTCSMoveStatePtr fromState, CTCSDeathStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//移动转转向
class CTCSMove2TurnTo : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSMove2TurnTo(std::string name, CTCSMoveStatePtr fromState, CTCSTurnToStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//移动转吃
class CTCSMove2Eat : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSMove2Eat(std::string name, CTCSMoveStatePtr fromState, CTCSEatStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//吃转死亡
class CTCSEat2Death : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSEat2Death(std::string name, CTCSEatStatePtr fromState, CTCSDeathStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//吃转转向
class CTCSEat2TurnTo : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSEat2TurnTo(std::string name, CTCSEatStatePtr fromState, CTCSTurnToStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//吃转吃
class CTCSEat2Eat : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSEat2Eat(std::string name, CTCSEatStatePtr fromState, CTCSEatStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//吃转移动
class CTCSEat2Move : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSEat2Move(std::string name, CTCSEatStatePtr fromState, CTCSMoveStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//转向转死亡
class CTCSTurnTo2Death : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSTurnTo2Death(std::string name, CTCSTurnToStatePtr fromState, CTCSDeathStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//转向转转向
class CTCSTurnTo2TurnTo : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSTurnTo2TurnTo(std::string name, CTCSTurnToStatePtr fromState, CTCSTurnToStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//转向转吃
class CTCSTurnTo2Eat : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSTurnTo2Eat(std::string name, CTCSTurnToStatePtr fromState, CTCSEatStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//转向转移动
class CTCSTurnTo2Move : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSTurnTo2Move(std::string name, CTCSTurnToStatePtr fromState, CTCSMoveStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//死亡转移动
class CTCSDeath2Move : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSDeath2Move(std::string name, CTCSDeathStatePtr fromState, CTCSMoveStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

class CTCSSnake
{
public:
    CTCSSnake();
    ~CTCSSnake();
    
    void initFSM();
    void initData();
    
    void onUpdate(float dt);
    
    void setMap(CTCSMap* snakeMap);
    CTCSMap* getMap();
    
    void setDir(STCSDirection _dir);
    STCSDirection getDir();
    void setSpeed(int speed);
    int getSpeed();
    void move();
    void addLength();
    void addSpeed();
    
    int getLength();
    SnakePos getHeadPos();
    SnakePos getTailPos();
    ListSnakePos getSnakePos();
    void deleteTail();
    void death();
protected:
    int m_i_length {2};
    STCSDirection m_sTCSDir_dir {DIRECTION_NONE};
    CTCSMap* m_cTCSMap_map_ptr;
    CTCSSnakeFSMPtr m_cTCSSFSM_action_Ptr;
    SnakePos m_snakePos_headPos{int(XTCSMAP_HEIGHT * 0.5), int(XTCSMAP_WIDTH * 0.5)};
    SnakePos m_snakePos_tailPos{-1, -1};
    SnakePos m_snakePos_lastTailPos{-1, -1};
    int m_i_speed {15};
    ListSnakePos m_listSnakePos_pos;
};

#endif /* XTCSNAKE_XTCSSTRUCT_SNAKE_H */
