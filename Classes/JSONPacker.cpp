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
    UnpackedRankInfo unpackRankInfoJSON(std::string json, int exp) {
        rapidjson::Document rankDocument;
        rankDocument.Parse<0>(json.c_str());
        
        int rank;
        std::string name;
        int nextExp;
        int leastExp;
        for (rapidjson::SizeType i = 0; i < rankDocument["rank"].Size(); ++i) {
            rapidjson::Value& rankDoc = rankDocument["rank"][i];
            int tmpExp = rankDoc["exp"].GetInt();
            int tmpNext = rankDoc["next"].GetInt();
            if (tmpExp <= exp && exp < tmpNext) {
                rank = rankDoc["rank"].GetInt();
                name = rankDoc["name"].GetString();
                nextExp = rankDoc["next"].GetInt();
                leastExp = rankDoc["exp"].GetInt();
                break;
            }
        }
        UnpackedRankInfo rankInfo;
        rankInfo.rank = rank;
        rankInfo.name = name;
        rankInfo.leastExp = leastExp;
        rankInfo.nextExp = nextExp;
        
        return rankInfo;
    }
    
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
    
    UserData unpackUserDataJSON(std::string json) {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());
        
        UserData userData;
        userData.state      = (GameState)document["state"].GetInt();
        userData.nen        = (Nen)document["nen"].GetInt();
        userData.auraLeft   = (float)document["aura"].GetDouble();
        userData.playTime   = (float)document["playTime"].GetDouble();
        userData.patternId  = document["pid"].GetInt();
        userData.userId     = document["uid"].GetInt();
        userData.nextRound  = document["r"].GetInt();
       
        return userData;
    }
    
    std::string packUserData(const UserData userData) {
        rapidjson::Document document;
        document.SetObject();
        
        document.AddMember("state",     (int)userData.state, document.GetAllocator());
        document.AddMember("nen",       (int)userData.nen, document.GetAllocator());
        document.AddMember("aura",      (double)userData.auraLeft, document.GetAllocator());
        document.AddMember("playTime",  (double)userData.playTime, document.GetAllocator());
        document.AddMember("pid",       userData.patternId, document.GetAllocator());
        document.AddMember("uid",       userData.userId, document.GetAllocator());
        document.AddMember("r",         userData.nextRound, document.GetAllocator());
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        
        std::string returnString(buffer.GetString(), buffer.Size());
        
        return returnString;
    }
}