#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "Globals.h"

enum class GameState
{
    Title,
    Ready,
    Playing,
    GameOver
};

class Character;
enum class Nen;

class MainScene : public cocos2d::Layer
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

private:
    cocos2d::Node* rootNode;
    cocos2d::Sprite* auraBar;
    cocos2d::ui::Text* comboLabel;
    cocos2d::ui::Text* levelLabel;
    cocos2d::ui::Text* countDownLabel;
    
    void onEnter() override;
    void setupTouchHandling();
    void update(float dt);
    void setCountDown(int score);
    void triggerTitle();
    void triggerReady();
    void triggerGameOver();
    void dropObstacles(ObstacleType obstacle);
    void resetGameState();
    void setKen();
    void setTen();
    void singlePlayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void setRemainingAura(float auraLeft);
    void playWeather();
    void setComboCount(int combo);
    void setLevelCount();
    void onEnterTransitionDidFinish() override;
    void gotHit();
    void setGameActive(bool active);
    
    float countDown;
    float auraLeft;
    float gettingHitCount;
    float playingTime;
    
    bool gettingHit;
    bool active;
    bool playingPattern;
    bool loadNext;
    
    int timeLeft;
    int playCount;
    int comboCount;
    int maxComboCount;
    int soundId;
    int gameRound;
    
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