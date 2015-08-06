//
//  JSONPacker.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/21.
//
//

#ifndef __Takigyo__JSONPacker__
#define __Takigyo__JSONPacker__

#include "cocos2d.h"
#include "PatternRate.h"
#include "Globals.h"

namespace JSONPacker{
    enum class DataType
    {
        GAME_STATE     = 1,
        POSITION_CHECK = 2,
        LEUKOCYTE      = 3,
    };
    struct UserData {
        Nen nen;
        float auraLeft;
        GameState state;
        float playTime;
//        bool gameOver;
//        int score;
//        std::vector<std::vector<cocos2d::Color3B>> board;
    };
    struct UnpackedLevelInfo {
        int level;
        double tempo;
        std::vector<PatternRate> patternRate;
    };
    
    struct UnpackedPatternList {
        float duration;
        std::vector<Pattern> patternList;
    };
    
    UnpackedLevelInfo unpackLevelInfoJSON(std::string json, int round);
    UnpackedPatternList unpackPatternListJSON(std::string json, int patternId);
    UserData unpackUserDataJSON(std::string json);
    std::string packUserData(const UserData data);
    
    int unpackUserId(std::string json);
    std::string packUserId(const int userId);
}

#endif /* defined(__Takigyo__JSONPacker__) */
