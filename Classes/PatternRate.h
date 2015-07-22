//
//  PatternRate.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/21.
//
//

#ifndef __Takigyo__PatternRate__
#define __Takigyo__PatternRate__

class PatternRate {
public:
    int prob;
    int patternId;
    
    PatternRate();
    PatternRate(int prob, int patternId);
//    static PatternRate add(PatternRate a, PatternRate b);
};

#endif /* defined(__Takigyo__PatternRate__) */
