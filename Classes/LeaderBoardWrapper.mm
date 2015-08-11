//
//  LeaderBoardWrapper.mm
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//


#include "LeaderBoardWrapper.h"
#include "LeaderBoardManager.h"
#include "Globals.h"

LeaderBoardWrapper::LeaderBoardWrapper()
{
    this->leaderBoardManager = [[LeaderBoardManager alloc] init];
    [leaderBoardManager retain];
}

LeaderBoardWrapper::~LeaderBoardWrapper()
{
    [leaderBoardManager release];
    leaderBoardManager = nil;
}

void LeaderBoardWrapper::loadLeaderboardInfo()
{
    [leaderBoardManager loadLeaderboardInfo];
}

void LeaderBoardWrapper::reportHighScore(int score)
{
    int64_t castedScore = static_cast<int64_t>(score);
    NSString* leaderBoardId = [NSString stringWithUTF8String:HIGHSCORE_LEADERBOARD_IDENTIFIER];
    
    [leaderBoardManager reportScore:castedScore forLeaderboardID:leaderBoardId];
}

void LeaderBoardWrapper::reportTotalScore(int exp)
{
    int64_t castedScore = static_cast<int64_t>(exp);
    NSString* leaderBoardId = [NSString stringWithUTF8String:TOTALSCORE_LEADERBOARD_IDENTIFIER];
    
    [leaderBoardManager reportScore:castedScore forLeaderboardID:leaderBoardId];
}

void LeaderBoardWrapper::showRanking()
{
    [leaderBoardManager showRanking];
}

void LeaderBoardWrapper::loadAchievements()
{
    [leaderBoardManager loadAchievements];
}

std::map<std::string, float> LeaderBoardWrapper::getAchievementList()
{
    std::map<std::string, float> ret;
    
    auto achievements = [leaderBoardManager getAchievementList];
    for (id key in [achievements keyEnumerator]) {
        GKAchievement* object = [achievements valueForKey:key];
        NSString *str = (NSString*)key;
        
        ret.insert(std::make_pair([str UTF8String], object.percentComplete));
    }
    
    return ret;
}

void LeaderBoardWrapper::reportAchievementIdentifier(const char *identifier, float percent)
{
    NSString* string = [NSString stringWithUTF8String:identifier];
    [leaderBoardManager reportAchievementIdentifier:string percentComplete:percent];
}

void LeaderBoardWrapper::resetAchievementsForDebug()
{
    [leaderBoardManager resetAchievementsForDebug];
}

void LeaderBoardWrapper::reportMultiAchievement(std::map<std::string, float> &achievements)
{
    NSMutableArray* array = [[NSMutableArray alloc] init];
    for (auto it : achievements) {
        GKAchievement* achievement  = [leaderBoardManager getAchievementForIdentifier:[NSString stringWithUTF8String:it.first.c_str()]];
        achievement.percentComplete = it.second;
        [array addObject:achievement];
    }
    
    [leaderBoardManager completeMultipleAchievements:array];
}