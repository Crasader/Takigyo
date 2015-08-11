//
//  RankInfo.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#include "RankInfo.h"
#include "JSONPacker.h"

USING_NS_CC;

RankInfo* RankInfo::createPatternWithExp(int exp) {
    RankInfo* rankInfo = new (std::nothrow) RankInfo();
    
    if (rankInfo && rankInfo->initWithExp(exp)) {
        rankInfo->autorelease();
        return rankInfo;
    }
    
    CC_SAFE_DELETE(rankInfo);
    
    return nullptr;
}

bool RankInfo::initWithExp(int exp) {
    if (! Node::init()) {
        return false;
    }
    
    // no need here now
    std::string rankInfoJson = FileUtils::getInstance()->fullPathForFilename("rank.json");
    std::string rankInfoJsonString = FileUtils::getInstance()->getStringFromFile(rankInfoJson);
    
    JSONPacker::UnpackedRankInfo currentRankInfo = JSONPacker::unpackRankInfoJSON(rankInfoJsonString, exp);
    this->exp = exp;
    this->rank = currentRankInfo.rank;
    this->name = currentRankInfo.name;
    this->leastExp = currentRankInfo.leastExp;
    this->nextExp = currentRankInfo.nextExp;
    
    return true;
}

int RankInfo::getCurrentRank() {
    return this->rank;
}

int RankInfo::getRemainExp() {
    return this->nextExp - this->exp;
}

int RankInfo::getGaugeWidth() {
    return this->nextExp - this->leastExp;
}

int RankInfo::getExpWidth() {
    return this->getGaugeWidth() - this->getRemainExp();
}

int RankInfo::getNextExp() {
    return this->nextExp;
}
std::string RankInfo::getCurrentRankName() {

    return this->name;
}