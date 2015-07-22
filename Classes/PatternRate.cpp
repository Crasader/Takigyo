//
//  PatternRate.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/21.
//
//

#include "PatternRate.h"

PatternRate:: PatternRate() : prob(0), patternId(0) {
}

PatternRate:: PatternRate(int prob, int patternId) : prob(prob), patternId(patternId) {
}
//PatternRate PatternRate::add(PatternRate a, PatternRate b) {
//    return PatternRate(a.prob + b.prob, a.patternId + b.patternId);
//}