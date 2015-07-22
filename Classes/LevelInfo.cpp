//
//  LevelInfo.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/20.
//
//

#include "JSONPacker.h"
#include "LevelInfo.h"

using namespace cocos2d;

LevelInfo* LevelInfo::createPatternWithRound(int round) {
    LevelInfo* levelInfo = new (std::nothrow) LevelInfo();
    
    if (levelInfo && levelInfo->initWithRound(round)) {
        levelInfo->autorelease();
        return levelInfo;
    }
    
    CC_SAFE_DELETE(levelInfo);
    
    return nullptr;
}

bool LevelInfo::initWithRound(int round) {
    if (! Node::init()) {
        return false;
    }
    
    // no need here now
    std::string levelInfoJson = FileUtils::getInstance()->fullPathForFilename("levelinfo.json");
    std::string levelInfoJsonString = FileUtils::getInstance()->getStringFromFile(levelInfoJson);
    
    JSONPacker::UnpackedLevelInfo currentLevelInfo = JSONPacker::unpackLevelInfoJSON(levelInfoJsonString, round);
    this->level = currentLevelInfo.level;
    this->tempo = currentLevelInfo.tempo;
    this->patternId = this->choosePatternId(currentLevelInfo.patternRate);
    
    // no need here now
    std::string patternListJson = FileUtils::getInstance()->fullPathForFilename("patternlist.json");
    std::string patternListJsonString = FileUtils::getInstance()->getStringFromFile(patternListJson);
    
    JSONPacker::UnpackedPatternList patternList = JSONPacker::unpackPatternListJSON(patternListJsonString, round);
    this->duration = patternList.duration;
    this->pattern  = patternList.patternList;
    
    return true;
}

std::vector<Pattern> LevelInfo::getCurrentPattern() {
    return this->pattern;
}

int LevelInfo::getCurrentLevel() {
    return this->level;
}

float LevelInfo::getCurrentDuration() {
    return this->duration;
}

double LevelInfo::getCurrentTempo() {
    return this->tempo;
}

int LevelInfo::choosePatternId(std::vector<PatternRate> patternRateList) {
    int totalProbability = 0;
    int randomProbabiliy;
    for (auto patternRate : patternRateList) {
        totalProbability += patternRate.prob;
    }
    randomProbabiliy = rand() % totalProbability;
//    random_shuffle(patternRateList.begin(), patternRateList.end());
    int patternId;
    int probabilityCount = 0;
    for (auto patternRate : patternRateList) {
        probabilityCount += patternRate.prob;
        if (probabilityCount >= randomProbabiliy) {
            patternId = patternRate.patternId;
            break;
        }
    }
    return patternId;
}