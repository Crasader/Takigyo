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
}

#endif /* defined(__Takigyo__JSONPacker__) */
