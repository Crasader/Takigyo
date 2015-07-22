//
//  Pattern.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/22.
//
//

#include "Pattern.h"

Pattern:: Pattern() : type (0), timing(0) {
}

Pattern:: Pattern(int type, float timing) : type(type), timing(timing) {
}