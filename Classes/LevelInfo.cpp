//
//  LevelInfo.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/20.
//
//

#include "LevelInfo.h"
#include "JSONPacker.h"

using namespace cocos2d;


int LevelInfo::getPatternId(int round) {
    //rotations = std::vector<std::vector<Coordinate>>();
    
    // no need here now
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename("level.json");
    
    std::string jsonString = FileUtils::getInstance()->getStringFromFile(fullPath);
    
    JSONPacker::LevelInfo levelInfo = JSONPacker::unpackLevelInfoJSON(jsonString, round);
}
