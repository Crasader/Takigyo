//
//  UserDataManager.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#ifndef __Takigyo__UserDataManager__
#define __Takigyo__UserDataManager__

#include "cocos2d.h"

class UserDataManager
{
public:
    static UserDataManager* getInstance();
    void deleteAllUserData();
    
    int getPlayTimes() const;
    void setPlayTimes(int times);
    
    int getPlayerExp() const;
    void setPlayerExp(int exp);

    int getPlayerHighScore() const;
    void setPlayerHighScore(int score);
    
    bool getPlayedTutorial() const;
    void setPlayedTutorial(bool isPlayedTutorial);
    
    int getGamePlayRetentionCount() const;
    void setGamePlayRetentionCount(int count);
    
private:
    static UserDataManager* _instance;
    static const char* PLAYTIMES_KEY;
    static const char* PLAYER_EXP_KEY;
    static const char* PLAYER_HIGH_SCORE_KEY;
    static const char* ATE_NORMAL_VIRUS_COUNT_KEY;
    static const char* ATE_MID_VIRUS_COUNT_KEY;
    static const char* ATE_BOSS_VIRUS_COUNT_KEY;
    static const char* TUTORIAL_KEY;
    static const char* GAME_PLAY_RETENTION_KEY;
    
    UserDataManager();
    ~UserDataManager();
};

#endif /* defined(__Takigyo__UserDataManager__) */
