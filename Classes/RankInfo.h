//
//  RankInfo.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#ifndef __Takigyo__RankInfo__
#define __Takigyo__RankInfo__

#include <cocos2d.h>
#include "PatternRate.h"
#include "Globals.h"

class RankInfo : cocos2d::Node {
public:
    static RankInfo* createPatternWithExp(int round);
    
    int getCurrentRank();
    int getNextExp();
    int getRemainExp();
    int getGaugeWidth();
    int getExpWidth();
    std::string getCurrentRankName();
    
private:
    int rank;
    int exp;
    std::string name;
    int leastExp;
    int nextExp;
    
    bool initWithExp(int round);
};
#endif /* defined(__Takigyo__RankInfo__) */
