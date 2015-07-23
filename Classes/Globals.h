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
    Ken,
    None
};

enum class ObstacleType {
    Rock,
    Heart
};

class Pattern {
public:
    float timing;
    ObstacleType type;
};

static const float PRESENT_OUTPUT_POTENTIAL = 10.0f;

static const float COUNT_DOWN_TIME = 3.0f;

static const float HIT_DAMAGE = 1.0f;
static const float RECOVERY   = 1.0f;
#endif