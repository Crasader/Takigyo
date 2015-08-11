//
//  LeaderBoardManager.mm
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#import <Foundation/Foundation.h>
#import "LeaderBoardManager.h"
#include "NetworkManagerDelegate.h"

#ifdef COCOS2D_DEBUG
#define NMLog(format, ...) NSLog(format, ##__VA_ARGS__)
#else
#define NMLog(...) do {} while (0)
#endif

@interface LeaderBoardManager ()

@property (nonatomic, strong) NSArray* leaderboards;
@property(nonatomic, retain) NSMutableDictionary *achievementsDictionary;

@end

@implementation LeaderBoardManager

#pragma mark - LeaderBoard Methods

- (void)loadLeaderboardInfo
{
    [GKLeaderboard loadLeaderboardsWithCompletionHandler: ^(NSArray *leaderboards, NSError *error) {
        self.leaderboards = leaderboards;
    }];
}

- (void)reportScore: (int64_t) score forLeaderboardID: (NSString*) identifier
{
    if (![GKLocalPlayer localPlayer].isAuthenticated) {
        NMLog(@"Failed report score because of non authenticated");
        return ;
    }
    
    GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier: identifier];
    scoreReporter.value = score;
    scoreReporter.context = 0;
    scoreReporter.shouldSetDefaultLeaderboard = YES;

    [GKScore reportScores:@[scoreReporter] withCompletionHandler:^(NSError* error) {
        if (error) {
            NMLog(@"Failed report score: %@", [error localizedDescription]);
        }
    }];
}

- (void)showRanking
{
    GKGameCenterViewController* gcview = [[GKGameCenterViewController alloc] init];
    
    gcview.gameCenterDelegate = self;
    gcview.viewState = GKGameCenterViewControllerStateDefault;
    [[UIApplication sharedApplication].keyWindow.rootViewController presentViewController:gcview animated:YES completion:nil];
}

#pragma mark - GKGameCenterControllerDelegate Methods

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController
{
    [[UIApplication sharedApplication].keyWindow.rootViewController dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - Achievement Methods

- (void)loadAchievements
{
    self.achievementsDictionary = [[NSMutableDictionary alloc] init];
    [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray *achievements, NSError *error)
    {
        if (error == nil) {
            for (GKAchievement* achievement in achievements) {
                [self.achievementsDictionary setObject: achievement forKey: achievement.identifier];
            }
        }
    }];
}

- (GKAchievement*)getAchievementForIdentifier: (NSString*) identifier
{
    GKAchievement *achievement = [self.achievementsDictionary objectForKey:identifier];
    
    if (achievement == nil)
    {
        achievement = [[GKAchievement alloc] initWithIdentifier:identifier];
        achievement.showsCompletionBanner = YES;
        [self.achievementsDictionary setObject:achievement forKey:achievement.identifier];
    }
    return achievement;
}

- (void)reportAchievementIdentifier: (NSString*) identifier percentComplete: (float) percent
{
    GKAchievement *achievement = [self getAchievementForIdentifier:identifier];
    
    if (achievement) {
        achievement.percentComplete = percent;
        achievement.showsCompletionBanner = YES;
        [achievement reportAchievementWithCompletionHandler:^(NSError *error)
         {
             if (error != nil)
             {
                 NSLog(@"Error in reporting achievements: %@", error);
             }
         }];
    }
}

- (void)completeMultipleAchievements: (NSArray*) achievements
{
    [GKAchievement reportAchievements: achievements withCompletionHandler:^(NSError *error)
    {
        if (error != nil) {
            NSLog(@"Error in reporting achievements: %@", error);
        }
    }];
}

- (NSMutableDictionary*)getAchievementList
{
    return self.achievementsDictionary;
}

- (void)resetAchievementsForDebug
{
    // ローカルに保存されているアチーブメントオブジェクトをすべてクリアする
    self.achievementsDictionary = [[NSMutableDictionary alloc] init];
    // Game Centerに保存されているすべての達成状況をクリアする
    [GKAchievement resetAchievementsWithCompletionHandler:^(NSError *error)
    {
        if (error != nil) {
            // エラー処理
        }
    }];
}

@end