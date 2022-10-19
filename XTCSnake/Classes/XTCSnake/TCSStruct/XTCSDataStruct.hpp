//
//  XTCSDataStruct.hpp
//  XTCSnake
//
//  Created by Will Young on 2022/9/24.
//

#ifndef XTCSNAKE_XTCSSTRUCT_DATASTRUCT_H
#define XTCSNAKE_XTCSSTRUCT_DATASTRUCT_H

#include "cocos2d.h"

#define XTCSMAP_WIDTH 20
#define XTCSMAP_HEIGHT 20

typedef enum _xtcs_direction
{
    DIRECTION_NONE = 0,
    DIRECTION_UP = 1,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3,
    DIRECTION_RIGHT = 4
} STCSDirection;

typedef enum _xtcs_turnTo
{
    TURNTO_NONE = 0,
    TURNTO_LEFT = 1,
    TURNTO_RIGHT = 2,
} STCSTurnTo;

typedef enum _xtcs_stateTag
{
    STATETAG_MAP_SHOWSNAKE = 101,
    STATETAG_MAP_EATFOOD = 102,
    STATETAG_MAP_ADDFOOD = 103,
    STATETAG_MAP_GAMEOVER = 104,
    STATETAG_SNAKE_MOVE = 201,
    STATETAG_SNAKE_TURNTO = 202,
    STATETAG_SNAKE_EAT = 203,
    STATETAG_SNAKE_DEATH = 204,
} STCSSTATETAG;

typedef enum _xtcs_gameState
{
    GAMESTATE_TCS_GAMESTART = 1,
    GAMESTATE_TCS_GAMEOVER = 2,
    GAMESTATE_TCS_GAMEPAUSE = 3,
} STCSGAMESTATE;

typedef enum _xtcs_mapContent
{
    MAPCONTENT_NONE = 0,
    MAPCONTENT_HEAD = 1,
    MAPCONTENT_BODY = 2,
    MAPCONTENT_FOOD = 3,
} STCSMAPCONTENT;

//声明类
//蛇相关
class CTCSSnake;
class CTCSSnakeFSM;

//状态
class CTCSMoveState;
class CTCSTurnToState;
class CTCSEatState;
class CTCSDeathState;

//事件
class CTCSMove2Death;
class CTCSMove2TurnTo;
class CTCSMove2Eat;

class CTCSEat2Death;
class CTCSEat2TurnTo;
class CTCSEat2Eat;
class CTCSEat2Move;

class CTCSTurnTo2Death;
class CTCSTurnTo2TurnTo;
class CTCSTurnTo2Eat;
class CTCSTurnTo2Move;
class CTCSDeath2Move;


//地图相关
class CTCSMap;
class CTCSMapFSM;

//状态
class CTCSShowSnakeState;
class CTCSEatAndAddFoodState;
class CTCSGameOverState;

//事件
class CTCSShowSnake2EatAndAddFood;
class CTCSShowSnake2GameOver;

class CTCSEatAndAddFood2GameOver;
class CTCSEatAndAddFood2EatAndAddFood;
class CTCSEatAndAddFood2ShowSnake;

class CTCSGameOver2ShowSnake;
class CTCSGameOver2EatAndAddFood;

//智能指针类
//蛇相关
typedef std::shared_ptr<CTCSSnake> CTCSSnakePtr;
typedef std::shared_ptr<CTCSSnakeFSM> CTCSSnakeFSMPtr;

typedef std::shared_ptr<CTCSMoveState> CTCSMoveStatePtr;
typedef std::shared_ptr<CTCSTurnToState> CTCSTurnToStatePtr;
typedef std::shared_ptr<CTCSEatState> CTCSEatStatePtr;
typedef std::shared_ptr<CTCSDeathState> CTCSDeathStatePtr;

typedef std::shared_ptr<CTCSMove2Death> CTCSMove2DeathPtr;
typedef std::shared_ptr<CTCSMove2TurnTo> CTCSMove2TurnToPtr;
typedef std::shared_ptr<CTCSMove2Eat> CTCSMove2EatPtr;

typedef std::shared_ptr<CTCSEat2Death> CTCSEat2DeathPtr;
typedef std::shared_ptr<CTCSEat2TurnTo> CTCSEat2TurnToPtr;
typedef std::shared_ptr<CTCSEat2Eat> CTCSEat2EatPtr;
typedef std::shared_ptr<CTCSEat2Move> CTCSEat2MovePtr;

typedef std::shared_ptr<CTCSTurnTo2Death> CTCSTurnTo2DeathPtr;
typedef std::shared_ptr<CTCSTurnTo2TurnTo> CTCSTurnTo2TurnToPtr;
typedef std::shared_ptr<CTCSTurnTo2Eat> CTCSTurnTo2EatPtr;
typedef std::shared_ptr<CTCSTurnTo2Move> CTCSTurnTo2MovePtr;

typedef std::shared_ptr<CTCSDeath2Move> CTCSDeath2MovePtr;

//地图相关
typedef std::shared_ptr<CTCSMap> CTCSMapPtr;
typedef std::shared_ptr<CTCSMapFSM> CTCSMapSFSMPtr;

typedef std::shared_ptr<CTCSShowSnakeState> CTCSShowSnakeStatePtr;
typedef std::shared_ptr<CTCSEatAndAddFoodState> CTCSEatAndAddFoodStatePtr;
typedef std::shared_ptr<CTCSGameOverState> CTCSGameOverStatePtr;

typedef std::shared_ptr<CTCSShowSnake2GameOver> CTCSShowSnake2GameOverPtr;
typedef std::shared_ptr<CTCSShowSnake2EatAndAddFood> CTCSShowSnake2EatAndAddFoodPtr;

typedef std::shared_ptr<CTCSEatAndAddFood2GameOver> CTCSEatAndAddFood2GameOverPtr;
typedef std::shared_ptr<CTCSEatAndAddFood2EatAndAddFood> CTCSEatAndAddFood2EatAndAddFoodPtr;
typedef std::shared_ptr<CTCSEatAndAddFood2ShowSnake> CTCSEatAndAddFood2ShowSnakePtr;

typedef std::shared_ptr<CTCSGameOver2EatAndAddFood> CTCSAddFood2ShowSnakePtr;
typedef std::shared_ptr<CTCSGameOver2ShowSnake> CTCSGameOver2ShowSnakePtr;


typedef std::vector<cocos2d::Sprite*> SeqSpMap;
typedef std::list<std::pair<int, int>> ListSnakePos;
typedef std::pair<int, int> SnakePos;
typedef std::list<STCSTurnTo> SeqTurnTo;

#endif /* XTCSNAKE_XTCSSTRUCT_DATASTRUCT_H */
