#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "CocosGUI.h"

enum class GameState
{
    Title,
    Ready,
    Playing,
    GameOver
};

enum class Obstacle
{
    Rock,
    Heart,
    None
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
    cocos2d::ui::Text* scoreLabel;
    
    void onEnter() override;
    void setupTouchHandling();
    void update(float dt);
    void setCountDown(int score);
    void triggerTitle();
    void triggerReady();
    void triggerGameOver();
    void dropObstacles();
    void resetGameState();
    void setKen();
    void setTen();
    void singlePlayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void setRemainingAura(float auraLeft);
    void playWeather();
    void onEnterTransitionDidFinish() override;
    
    float countDown;
    float auraLeft;
    
    int timeLeft;
    int playCount;
    
    cocos2d::Node* cloudsNode;
    
    GameState gameState;
    Obstacle obstacleType;
};

#endif // __MainScene_SCENE_H__