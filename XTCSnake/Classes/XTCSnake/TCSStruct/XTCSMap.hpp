//
//  XTCSMap.hpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/24.
//

#ifndef XTCSNAKE_XTCSSTRUCT_MAP_H
#define XTCSNAKE_XTCSSTRUCT_MAP_H

#include "cocos2d.h"

#include "XLock.h"
#include "XFiniteStateMachine.h"

#include "XTCSDataStruct.hpp"

class CTCSMapFSM : public XDESIGNPATTERBASE::XIFSMBase
{
public:
    CTCSMapFSM(std::string name, XDESIGNPATTERBASE::XIStatePtr defaultState);
    
    void setParent(CTCSMap* parent) { m_cTCSMap_parent_ptr = parent; }
    CTCSMap* getParent() { return m_cTCSMap_parent_ptr; }
    
private:
    CTCSMapFSM();
    
private:
    std::string m_str_name;
    
    CTCSMap* m_cTCSMap_parent_ptr;
};

//显示蛇状态
class CTCSShowSnakeState : public XDESIGNPATTERBASE::XIState
{
public:
    CTCSShowSnakeState(std::string name);
    
    virtual void onUpdate(float deltaTime) override;
private:

};

//吃和生产食物状态
class CTCSEatAndAddFoodState : public XDESIGNPATTERBASE::XIState
{
public:
    CTCSEatAndAddFoodState(std::string name);
    
    virtual void onEnter(XDESIGNPATTERBASE::XIStatePtr prev) override;
    
    virtual void onUpdate(float deltaTime) override;
    
    virtual void onExit(XDESIGNPATTERBASE::XIStatePtr next) override;
private:
};

//结束状态
class CTCSGameOverState : public XDESIGNPATTERBASE::XIState
{
public:
    CTCSGameOverState(std::string name);
    
    virtual void onEnter(XDESIGNPATTERBASE::XIStatePtr prev) override;
    virtual void onExit(XDESIGNPATTERBASE::XIStatePtr next) override;
private:
};

//显示蛇转吃和生产食物
class CTCSShowSnake2EatAndAddFood : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSShowSnake2EatAndAddFood(std::string name, CTCSShowSnakeStatePtr fromState, CTCSEatAndAddFoodStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//显示蛇转游戏结束
class CTCSShowSnake2GameOver : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSShowSnake2GameOver(std::string name, CTCSShowSnakeStatePtr fromState, CTCSGameOverStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//吃和生产食物转游戏结束
class CTCSEatAndAddFood2GameOver : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSEatAndAddFood2GameOver(std::string name, CTCSEatAndAddFoodStatePtr fromState, CTCSGameOverStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//吃和生产食物转吃和生产食物
class CTCSEatAndAddFood2EatAndAddFood : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSEatAndAddFood2EatAndAddFood(std::string name, CTCSEatAndAddFoodStatePtr fromState, CTCSEatAndAddFoodStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//吃和生产食物转显示蛇
class CTCSEatAndAddFood2ShowSnake : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSEatAndAddFood2ShowSnake(std::string name, CTCSEatAndAddFoodStatePtr fromState, CTCSShowSnakeStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//游戏结束转展示蛇
class CTCSGameOver2ShowSnake : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSGameOver2ShowSnake(std::string name, CTCSGameOverStatePtr fromState, CTCSShowSnakeStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

//游戏结束转吃和生产食物
class CTCSGameOver2EatAndAddFood : public XDESIGNPATTERBASE::XITransition
{
public:
    CTCSGameOver2EatAndAddFood(std::string name, CTCSGameOverStatePtr fromState, CTCSEatAndAddFoodStatePtr toState);
    
    virtual bool onCheck() override;
    virtual bool onCompleteCallBack() override;
private:
};

class CTCSMap : public cocos2d::Node
{
public:
    CREATE_FUNC(CTCSMap)
    ~CTCSMap();
    
    STCSGAMESTATE getGameState();
    void setGameState(STCSGAMESTATE state);
    
    void showSnake();
    
    void addTurnTo(STCSTurnTo dir);
    STCSTurnTo getTurnTo();
    STCSTurnTo popTurnTo();
    STCSDirection getCurDir();
    
    void addFood();
    int getFoodPos();
    void clearFood();
    bool isExistFood();
    
    bool isDeath();
    void gameOver();
    
    //立刻移动
    void moveNow();
    
    CTCSSnakePtr getSnake();
    
    void setShowScoreCallBack(std::function<void(int)> cb);
    void setShowGameOverCallBack(std::function<void(int)> cb);
protected:
    CTCSMap();
    virtual bool init() override;
    virtual void onEnter() override;
    void initUI();
    void initSnake();
    void initFSM();
    void initData();
    
    virtual void update(float deltaTime) override;
protected:
    STCSMAPCONTENT m_mapContent_map[XTCSMAP_WIDTH][XTCSMAP_HEIGHT] { MAPCONTENT_NONE };
    
    SeqSpMap m_seqSpMap_map;
    SeqTurnTo m_seqTT_dir;
    
    CTCSSnakePtr m_cTCSSnake_snake_Ptr;
    CTCSMapSFSMPtr m_cTCSMFSM_action_Ptr;
    STCSGAMESTATE m_sTCSGameState_state {GAMESTATE_TCS_GAMEOVER};
    
    int m_i_times{0};
    
    //当前食物位置
    int m_i_foodPos{-1};
    
    pthread_mutex_t m_mutex_turnTo;
    
    std::function<void(int)> m_showScoreCallback{nullptr};
    std::function<void(int)> m_showGameOverCallback{nullptr};
};
#endif /* XTCSNAKE_XTCSSTRUCT_MAP_H */
