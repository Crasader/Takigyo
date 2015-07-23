//
//  JSONPacker.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/21.
//
//

#include "Globals.h"
#include "JSONPacker.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace cocos2d;

namespace JSONPacker {
    UnpackedLevelInfo unpackLevelInfoJSON(std::string json, int round) {
        rapidjson::Document levelDocument;
        levelDocument.Parse<0>(json.c_str());
        
        std::vector<PatternRate> patternRate;
        int level;
        float tempo;
        for (rapidjson::SizeType i = 0; i < levelDocument.Size(); ++i) {
            rapidjson::Value& levelDoc = levelDocument[i];
            int tmpRound = levelDoc["round"].GetInt();
            if (tmpRound > round) {
                break;
            }
            level = levelDoc["level"].GetInt();
            tempo = levelDoc["tempo"].GetDouble();
            
            patternRate.clear();
            rapidjson::Value& patternRateDoc = levelDoc["rate"];
            for (rapidjson::SizeType j = 0; j < patternRateDoc.Size(); ++j) {
                rapidjson::Value& pattern = patternRateDoc[j];
                int prob = pattern["prob"].GetInt();
                int patternId = pattern["id"].GetInt();
                patternRate.push_back(PatternRate(prob, patternId));
            }
            
        }
        UnpackedLevelInfo levelInfo;
        levelInfo.level = level;
        levelInfo.tempo = tempo;
        levelInfo.patternRate = patternRate;
        
        return levelInfo;
    }
    
    UnpackedPatternList unpackPatternListJSON(std::string json, int patternId) {
        rapidjson::Document patternDocument;
        patternDocument.Parse<0>(json.c_str());
        bool error = patternDocument.HasParseError();
        if(error){CCLOG("PARSE ERROR!");};
        
        std::vector<Pattern> patternList;
        
        std::string stringPatternId = StringUtils::toString(patternId);
        const char* stringPatternKey = stringPatternId.c_str();
        rapidjson::Value& patternListDoc = patternDocument[stringPatternKey];
        
        rapidjson::Value& patternDoc = patternListDoc["pattern"];
        
        for (rapidjson::SizeType j = 0; j < patternDoc.Size(); ++j) {
            rapidjson::Value& pattern = patternDoc[j];
            ObstacleType type = (ObstacleType)pattern["type"].GetInt();
            
            float timing = (float)pattern["time"].GetDouble();
            Pattern patternStructure = Pattern();
            patternStructure.timing = timing;
            patternStructure.type = type;
            patternList.push_back(patternStructure);
        }
        
        float duration = (float)patternListDoc["duration"].GetDouble();
        
        UnpackedPatternList unpackedPatternList;
        unpackedPatternList.duration = duration;
        unpackedPatternList.patternList = patternList;
        
        return unpackedPatternList;
    }
}