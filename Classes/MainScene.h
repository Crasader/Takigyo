#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "Globals.h"
#include "NetworkingWrapper.h"

enum class GameState
{
    Title,
    Ready,
    Playing,
    GameOver
};

class Character;
enum class Nen;

class MainScene : public cocos2d::Layer , public NetworkingDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
protected:
    Character* character;
    
    bool networkedSession;

private:
    void receivedData(const void* data, unsigned long length);
    void stateChanged(ConnectionState state);
    
    std::unique_ptr<NetworkingWrapper> netWorkingWrapper;
    
    cocos2d::Node* rootNode;
    cocos2d::Node* levelNode;
    cocos2d::Node* rockNode;
    cocos2d::Sprite* auraBar;
    cocos2d::ui::Text* comboLabel;
    cocos2d::ui::Text* countDownLabel;
    
    void onEnter() override;
    void setupTouchHandling();
    void update(float dt);
    void setCountDown(int score);
    void triggerTitle();
    void triggerReady();
    void triggerGameOver();
    void dropObstacles(ObstacleType obstacle, float tempo);
    void resetGameState();
    void setKen();
    void setTen();
    void singlePlayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void multiPlayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void replayButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void setRemainingAura(float auraLeft);
    void playWeather();
    void setComboCount(int combo);
    void setLevelCount();
    void onEnterTransitionDidFinish() override;
    void gotHit();
    void setGameActive(bool active);
    void playTimingAnimation();
    
    float playingTime;
    float auraLeft;
    float gettingHitCount;
    float patternPlayTime;
    float touchingTime;
    
    bool gettingHit;
    bool active;
    bool playingPattern;
    bool loadNext;
    bool isEvening;
    bool replayButtonPressing;
    bool onMultiPlayerMode;
    
    int timeLeft;
    int playCount;
    int comboCount;
    int maxComboCount;
    int soundId;
    int gameRound;
    int touchingCount;
    
    int totalGoodCount;
    int totalGreatCount;
    int totalPerfectCount;
    int totalScore;
    
    int overallScore;
    int overallGamePlayCount;
    
    std::vector<Pattern> currentPattern;
    int currentLevel;
    int beforeLevel;
    float currentDuration;
    double currentTempo;
    std::vector<float> timingList;
    std::vector<ObstacleType> obstacleList;
    
    cocos2d::Node* cloudsNode;
    
    GameState gameState;
    ObstacleType obstacleType;
};

#endif // __MainScene_SCENE_H__