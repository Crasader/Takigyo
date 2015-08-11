//
//  LeaderBoardManager.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#ifndef Takigyo_LeaderBoardManager_h
#define Takigyo_LeaderBoardManager_h

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface LeaderBoardManager : NSObject<GKGameCenterControllerDelegate>

- (void)loadLeaderboardInfo;

- (void)reportScore: (int64_t) score forLeaderboardID: (NSString*) identifier;

- (void)showRanking;

- (void)loadAchievements;

- (GKAchievement*)getAchievementForIdentifier: (NSString*) identifier;

- (void)reportAchievementIdentifier: (NSString*) identifier percentComplete: (float) percent;

- (void)completeMultipleAchievements: (NSArray*) achievements;

- (NSMutableDictionary*)getAchievementList;

- (void)resetAchievementsForDebug;

@end

#endif