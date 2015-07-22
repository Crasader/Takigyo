//
//  Pattern.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/22.
//
//

#ifndef __Takigyo__Pattern__
#define __Takigyo__Pattern__

class PatternRate {
public:
    int type;
    int timing;
    
    PatternRate();
    PatternRate(int prob, int patternId);
    //    static PatternRate add(PatternRate a, PatternRate b);
};

#endif /* defined(__Takigyo__Pattern__) */
