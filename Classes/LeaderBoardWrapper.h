//
//  LeaderBoardWrapper.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#ifndef Takigyo_LeaderBoardWrapper_h
#define Takigyo_LeaderBoardWrapper_h

#include "NetworkManagerDelegate.h"

#ifdef __OBJC__
@class LeaderBoardManager;
#else
typedef struct objc_object LeaderBoardManager;
#endif

class LeaderBoardWrapper
{
public:
    LeaderBoardWrapper();
    ~LeaderBoardWrapper();
    
    void loadLeaderboardInfo();
    void reportHighScore(int score);
    void reportTotalScore(int exp);
    void showRanking();
    
    void loadAchievements();
    std::map<std::string, float> getAchievementList();
    void reportAchievementIdentifier(const char* identifier, float percent);
    void resetAchievementsForDebug();
    void reportMultiAchievement(std::map<std::string, float> &achievements);
private:
    LeaderBoardManager* leaderBoardManager;
};

#endif