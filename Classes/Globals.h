//
//  Globals.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/15.
//
//

#ifndef Takigyo_Globals_h
#define Takigyo_Globals_h
#include "Globals.h"

enum class Nen
{
    Ten,
    Ken
};

enum class ObstacleType {
    Rock,
    Heart
};

enum class GameState
{
    Title = 1,
    Ready = 2,
    MultiPreparation = 3,
    WAITING = 4,
    COUNT_DOWN = 5,
    Playing = 6,
    GameOver = 7
};

class Pattern {
public:
    float timing;
    ObstacleType type;
};

static const float PRESENT_OUTPUT_POTENTIAL = 10.0f;

static const float COUNT_DOWN_TIME = 3.0f;

static const float HIT_DAMAGE = 1.0f;
static const float RECOVERY   = 0.5f;
#endif