#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "Globals.h"
#include "NetworkingWrapper.h"

enum class Target {
    Me,
    Opponent
};

class Character;
class OpponentCharacter;
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
    OpponentCharacter* opponentCharacter;
    
    bool networkedSession;

private:
    void receivedData(const void* data, unsigned long length);
    void stateChanged(ConnectionState state);
    
    std::unique_ptr<NetworkingWrapper> netWorkingWrapper;
    
    cocos2d::Node* rootNode;
    cocos2d::Node* levelNode;
    cocos2d::Node* waiting;
    cocos2d::Node* rockNode;
    cocos2d::Node* lifeBG;
    cocos2d::Node* lifeBG2;
    cocos2d::Node* waterfall;
    cocos2d::Sprite* auraBar;
    cocos2d::Sprite* auraBar2;
    cocos2d::ui::Text* comboLabel;
    cocos2d::ui::Text* countDownLabel;
    cocos2d::Node* bottomRock;
    cocos2d::Node* bottomRock2;
    cocos2d::ParticleSystemQuad* splashEffect;
    cocos2d::ParticleSystemQuad* splashEffect2;
    cocos2d::ui::Button* replayMultiButton;
    
    cocos2d::Size visibleSize;
    
    void onEnter() override;
    void setupTouchHandling();
    void update(float dt);
    void setCountDown(int score);
    void triggerTitle();
    void triggerReady();
    void triggerGameOver();
    
    void triggerMultiPreparation();
    void triggerMultiGameOver();
    void triggerMultiResult();
    
    void dropObstacles(ObstacleType obstacle, float tempo);
    void resetGameState();
    void setKen();
    void setTen();
    void singlePlayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void multiPlayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void replayButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void replayMultiButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void topButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void setRemainingAura(float auraLeft);
    void setOpponentRemainingAura(float auraLeft);
    void playWeather();
    void setComboCount(int combo);
    void setLevelCount();
    void onEnterTransitionDidFinish() override;
    void gotHit();
    void setGameActive(bool active);
    void playTimingAnimation();
    void sendDataOverNetwork();
    void setSinglePlayMode();
    void setMultiPlayMode();
    void unpack(std::string dataStr);
    
    float playingTime;
    float opponentPlayingTime;
    float auraLeft;
    float auraLeft2;
    float gettingHitCount;
    float patternPlayTime;
    float touchingTime;
    float timeForMulti;
    float timeForWaiting;
    
    bool readyForNextPattern;
    bool gettingHit;
    bool active;
    bool playingPattern;
    bool loadNext;
    bool replayButtonPressing;
    bool onMultiPlayerMode;
    bool isHost;
    bool sentPattern;
    bool isGameOver;
    bool isOpponentGameOver;
    
    int timeLeft;
    int playCount;
    int comboCount;
    int maxComboCount;
    int soundId;
    int gameRound;
    int nextRound;
    int pastRound;
    int touchingCount;
    
    int totalGoodCount;
    int totalGreatCount;
    int totalPerfectCount;
    int totalScore;
    
    int overallScore;
    int overallGamePlayCount;
    
    int userId;
    int opponentUserId;
    
    int winScore;
    int opponentWinScore;
    
    std::vector<Pattern> currentPattern;
    int currentLevel;
    int currentPatternId;
    int receivedPatternId;
    int pastPatternId;
    int beforeLevel;
    float currentDuration;
    double currentTempo;
    std::vector<float> timingList;
    std::vector<ObstacleType> obstacleList;
    
    cocos2d::Node* cloudsNode;
    
    GameState gameState;
    GameState opponentGameState;
    ObstacleType obstacleType;
};

#endif // __MainScene_SCENE_H__