//
//  UserDataManager.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#include "UserDataManager.h"

USING_NS_CC;

#pragma mark - Static Variables

UserDataManager* UserDataManager::_instance = nullptr;
const char* UserDataManager::PLAYTIMES_KEY = "playtimes";
const char* UserDataManager::PLAYER_EXP_KEY = "player_exp";
const char* UserDataManager::PLAYER_HIGH_SCORE_KEY = "player_high_score";
const char* UserDataManager::ATE_NORMAL_VIRUS_COUNT_KEY = "normal_virus";
const char* UserDataManager::ATE_MID_VIRUS_COUNT_KEY  = "mid_virus";
const char* UserDataManager::ATE_BOSS_VIRUS_COUNT_KEY = "boss_virus";
const char* UserDataManager::TUTORIAL_KEY = "tutorial";
const char* UserDataManager::GAME_PLAY_RETENTION_KEY = "game_play_retention";

#pragma mark - Lifecycle

UserDataManager* UserDataManager::getInstance()
{
    if (!_instance) {
        _instance = new UserDataManager();
    }
    return _instance;
}

UserDataManager::UserDataManager()
{
}

UserDataManager::~UserDataManager()
{
}

#pragma mark - Accessor

int UserDataManager::getPlayTimes() const
{
    return UserDefault::getInstance()->getIntegerForKey(PLAYTIMES_KEY, 0);
}

void UserDataManager::setPlayTimes(int times)
{
    UserDefault::getInstance()->setIntegerForKey(PLAYTIMES_KEY, times);
    UserDefault::getInstance()->flush();
}

int UserDataManager::getPlayerExp() const
{
    return UserDefault::getInstance()->getIntegerForKey(PLAYER_EXP_KEY, 0);
}

void UserDataManager::setPlayerExp(int exp)
{
    UserDefault::getInstance()->setIntegerForKey(PLAYER_EXP_KEY, exp);
    UserDefault::getInstance()->flush();
}

int UserDataManager::getPlayerHighScore() const
{
    return UserDefault::getInstance()->getIntegerForKey(PLAYER_HIGH_SCORE_KEY, 0);
}

void UserDataManager::setPlayerHighScore(int score)
{
    UserDefault::getInstance()->setIntegerForKey(PLAYER_HIGH_SCORE_KEY, score);
    UserDefault::getInstance()->flush();
}

bool UserDataManager::getPlayedTutorial() const
{
    return UserDefault::getInstance()->getBoolForKey(TUTORIAL_KEY, false);
}

void UserDataManager::setPlayedTutorial(bool isPlayedTutorial)
{
    UserDefault::getInstance()->setBoolForKey(TUTORIAL_KEY, isPlayedTutorial);
}

int UserDataManager::getGamePlayRetentionCount() const
{
    return UserDefault::getInstance()->getIntegerForKey(GAME_PLAY_RETENTION_KEY, 0);
}

void UserDataManager::setGamePlayRetentionCount(int count)
{
    UserDefault::getInstance()->setIntegerForKey(GAME_PLAY_RETENTION_KEY, count);
}

#pragma mark - For debug

void UserDataManager::deleteAllUserData()
{
    this->setPlayerExp(0);
    this->setPlayTimes(0);
}