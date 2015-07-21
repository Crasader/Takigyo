//
//  LevelInfo.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/20.
//
//

#ifndef __Takigyo__LevelInfo__
#define __Takigyo__LevelInfo__

#include <cocos2d.h>

class Pattern;

class LevelInfo {
//    struct Pattern {
//        float tempo;
//        //std::vector<float> probability;
//        std::vector<Pattern> pattern;
//    };
    // 1lv 1pattern
//    int levelUpStage;
//    int levelUpStage2;
public:
    int getPatternId(int round);
    
private:

//    Pattern getRandomPattern(int level);
    
//    float getLevelTempo;
//    std::vector<float> getPattern;
//    std::vector<float> getPatternDuration;
};
#endif /* defined(__Takigyo__LevelInfo__) */
