//
//  Utility.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/28.
//
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Utility.h"

using namespace cocos2d;

std::string Utility::getTimeString(int timeSec)
{
    int minute = timeSec / 60;
    int second = timeSec % 60;
    
    std::ostringstream minute_out, second_out;
    minute_out << std::setfill('0') << std::setw(2) << minute;
    second_out << std::setfill('0') << std::setw(2) << second;
    
    return std::string(minute_out.str() + ":" + second_out.str());
};

std::string Utility::getScoreString(int score) {
    std::ostringstream score_out;
    score_out << std::setfill('0') << std::setw(7) << score;
    
    return std::string(score_out.str());
};