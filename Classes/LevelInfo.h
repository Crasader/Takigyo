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
#include "PatternRate.h"
#include "Globals.h"

class LevelInfo : cocos2d::Node {
public:
    static LevelInfo* createPatternWithRound(int round);
    static LevelInfo* createPatternWithRoundAndPatternId(int round, int patternId);
    
    int getCurrentLevel();
    int getCurrentPatternId();
    double getCurrentTempo();
    float getCurrentDuration();
    std::vector<Pattern> getCurrentPattern();
    
private:
    int level;
    float duration;
    int patternId;
    double tempo;
    std::vector<PatternRate> patternRate;
    std::vector<Pattern> pattern;
    
    bool initWithRound(int round);
    int choosePatternId(std::vector<PatternRate>);
    bool initWithRoundAndPatternId(int round, int patternId);
//    Pattern getRandomPattern(int level);
    
//    float getLevelTempo;
//    std::vector<float> getPattern;
//    std::vector<float> getPatternDuration;
};
#endif /* defined(__Takigyo__LevelInfo__) */
