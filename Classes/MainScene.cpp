#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MainScene.h"
#include "Globals.h"
#include "Character.h"
#include "CharacterReader.h"
#include "SimpleAudioEngine.h"

USING_NS_TIMELINE

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    // Register the readers for our custom classes
    // Be very careful to do CharacterReader::getInstance, not CharacterReader::getInstance() which will crash
    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    Size size = Director::getInstance()->getVisibleSize();
    
    this->rootNode = CSLoader::createNode("MainScene.csb");
    ui::Helper::doLayout(this->rootNode);
    
    this->rootNode->setContentSize(size);
    auto waterfall = rootNode->getChildByName("waterfall");
    auto bottomRock = waterfall->getChildByName("bottomRock");
    this->character = bottomRock->getChildByName<Character*>("Character");
    auto lifeBG = rootNode->getChildByName("lifeBG");
    this->auraBar = lifeBG->getChildByName<Sprite*>("lifeBar");
    this->countDownLabel = rootNode->getChildByName<cocos2d::ui::Text*>("countDownLabel");
    this->scoreLabel     = rootNode->getChildByName<cocos2d::ui::Text*>("scoreLabel");
    this->cloudsNode = rootNode->getChildByName("clouds");
    this->countDown = 0.0f;
    this->playCount = 0;
    
    ui::Button* playButton = this->rootNode->getChildByName<ui::Button*>("PlayButton");
    playButton->addTouchEventListener(CC_CALLBACK_2(MainScene::singlePlayerPressed, this));
    
    addChild(this->rootNode);
    
    this->resetGameState();
    
    return true;
}

void MainScene::onEnter() {
    Layer::onEnter();
    
    // schedule the update method to be called every frame
    this->scheduleUpdate();
    
    this->triggerTitle();
    
    this->setupTouchHandling();
    
    this->playWeather();
}

#pragma mark -
#pragma mark Game Loop

void MainScene::update(float dt)
{
    // update is called before every new frame is rendered
    // dt is the amount of time elapsed (in seconds) between this update call and the previous one
    
    // call the superclass method update
    Layer::update(dt);
    
    int random = rand() % 100;
    if (random == 0) {
        auto denshion = CocosDenshion::SimpleAudioEngine::getInstance();
        denshion->playEffect("bird.wav");
    }
    
    if (this->gameState == GameState::Ready) {
        this->countDown += dt;
        
        this->setCountDown(COUNT_DOWN_TIME - this->countDown + 1);
    
        if (this->countDown > COUNT_DOWN_TIME) {
            this->gameState = GameState::Playing;
            
            // load and run the title animation
            ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
            this->runAction(titleTimeline);
            titleTimeline->play("countDown", false);
        }
    }
    if (this->gameState == GameState::Playing) {
        int random = rand() % 60;
        if (random == 0) {
            this->dropObstacles();
        }
        
        this->countDown += dt;
        if (this->character->getNen() == Nen::Ken) {
            setRemainingAura(auraLeft - dt);
        }
        if (this->gettingHit == true) {
            this->gettingHitCount += dt;
            if (this->gettingHitCount >= 1.0f) {
                this->gettingHit = false;
                this->gettingHitCount = 0.0f;
            }
        }
        // if the timer is less than or equal to 0, the game is over
        if (this->auraLeft <= 0.0f)
        {
            std::string scoreString = StringUtils::toString(this->countDown - 3.0f);
            std::string messageContent = "Your score is " + scoreString + "sec!";
            MessageBox(messageContent.c_str(), "Game Over");
            
            this->triggerGameOver();
        }
    }
}

void MainScene::setCountDown(int timeLeft)
{
    // update the score instance variable
    this->timeLeft = timeLeft;
    
    // update the score label
    this->countDownLabel->setString(std::to_string(this->timeLeft));
}

void MainScene::dropObstacles() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // default obstacle
    Sprite* obstacle = Sprite::create("FallenRock.png");
    Obstacle obstacleType = Obstacle::Rock;
    
    // sometimes recovery item
    int randomNum = rand() % 10;
    if (randomNum <= 1) {
        obstacle = Sprite::create("heart.png");
        obstacleType = Obstacle::Heart;
    }
    
    obstacle->setScale(0.5f);
    obstacle->setZOrder(-1);
    obstacle->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 1.2f));
    
    auto waterfall = rootNode->getChildByName("waterfall");
    auto intoWater          = MoveTo::create(1.0f, waterfall->getPosition() - Vec2(0, 100));
    auto getCloser          = ScaleTo::create(0.0f, 1.0);
    auto upAboveWater       = MoveTo::create(0.5f, waterfall->getPosition() - Vec2(0, 30));
    auto downToCharacter    = MoveBy::create(0.8f, Vec2(0, -530));
    auto easeInDown         = EaseIn::create(downToCharacter, 4);
    
    auto denshion = CocosDenshion::SimpleAudioEngine::getInstance();
    obstacle->runAction(Sequence::create(
                                     intoWater,
                                     // Enlarge the obstacle
                                     getCloser,
                                     // Splash Sound
                                     CallFunc::create(
                                                      [denshion]() {
                                                          denshion->playEffect("splash_rock.wav");
                                                      }
                                                      ),
                                     // Half above the water
                                     upAboveWater,
                                     // Change Z order into front
                                     CallFunc::create(
                                                      [obstacle,this]() {
                                                          obstacle->setZOrder(0);
                                                      }
                                                      ),
                                     // Ease In Down
                                     easeInDown,
                                     CallFunc::create([this, denshion, obstacleType]() {
                                                            if (this->gameState == GameState::Playing) {
                                                                // While not touching the screen
                                                                if (this->character->getNen() == Nen::Ten) {
                                                                    if (obstacleType == Obstacle::Rock) {
                                                                        this->gotHit();
                                                                    } else if (obstacleType == Obstacle::Heart) {
                                                                        float remainingAura = this->auraLeft + RECOVERY;
                                                                        this->setRemainingAura(remainingAura);
                                                                        denshion->playEffect("heart.wav");
                                                                    }
                                                                // While "TOUCHING" the screen
                                                                } else if (this->character->getNen() == Nen::Ken) {
                                                                    if (obstacleType == Obstacle::Rock) {
                                                                        denshion->playEffect("break.wav");
                                                                        int combo = this->comboCount++;
                                                                        this->setComboCount(combo);
                                                                    } else if (obstacleType == Obstacle::Heart) {
                                                                        denshion->playEffect("break.wav");
                                                                    }
                                                                }
                                                            }
                                                            }),
                                     // Remove from Parent
                                     CallFunc::create([obstacle](){obstacle->removeFromParent();}),
                                     NULL));
    
    this->rootNode->addChild(obstacle);
}

void MainScene::gotHit() {
    if (this->gettingHit == false) {
        this->gettingHit = true;
        auto yoko = ScaleBy::create(0.1f, 4, 0.25);
        auto tate = ScaleBy::create(0.1f, 0.25, 4.0);
        auto yoko2 = ScaleBy::create(0.15f, 2, 0.5);
        auto tate2 = ScaleBy::create(0.15f, 0.5, 2);
        auto yoko3 = ScaleBy::create(0.3f, 2, 0.5);
        auto tate3 = CCEaseBackIn::create(ScaleBy::create(0.3f, 0.5, 2));
        this->character->runAction(Sequence::create(yoko,tate,yoko2,tate2,yoko3,tate3,NULL));
    }
    float remainingAura = this->auraLeft - HIT_DAMAGE;
    this->setRemainingAura(remainingAura);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gothit.wav");
    this->comboCount = 1;
}

void MainScene::setComboCount(int combo) {
    // update the score label
    this->scoreLabel->setString(std::to_string(combo));
    
    ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->runAction(titleTimeline);
    titleTimeline->play("playing", false);
}

#pragma mark -
#pragma mark Getters / Setters

void MainScene::setRemainingAura(float auraLeft)
{
    // clamp the time left timer to between 0 and 10 seconds
    this->auraLeft = clampf(auraLeft, 0.0f, PRESENT_OUTPUT_POTENTIAL);
    
    // update the UI to reflect the correct time left
    this->auraBar->setScaleX(this->auraLeft / PRESENT_OUTPUT_POTENTIAL);
}
void MainScene::resetGameState()
{
    // these variables must be reset every new game
    this->auraLeft = PRESENT_OUTPUT_POTENTIAL;
    this->countDown = 0.0f;
    this->comboCount = 1;
    this->gettingHit = false;
    this->gettingHitCount = 0.0f;
    this->auraBar->setScaleX(1.0f);
    if (this->playCount > 0) {
        this->character->setNen(Nen::Ten);
        this->playWeather();
    }
}

void MainScene::triggerTitle()
{
    this->gameState = GameState::Title;
    
    // load and run the title animation
    ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->runAction(titleTimeline);
    titleTimeline->play("title", false);
    
}

void MainScene::triggerReady() {
    // set the game state to Ready
    this->gameState = GameState::Ready;
    this->character->setNen(Nen::Ten);
    
    // load and run the ready animations
    ActionTimeline* readyTimeline = CSLoader::createTimeline("MainScene.csb");
    this->runAction(readyTimeline);
    readyTimeline->play("ready", false);
    
    auto background = this->rootNode->getChildByName("background");
    background->setZOrder(-1);
}

void MainScene::triggerGameOver()
{
    this->playCount++;
    
    this->gameState = GameState::GameOver;
    
    this->triggerTitle();
    
    this->resetGameState();
}

void MainScene::setupTouchHandling() {
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        // get the location of the touch in the MainScene's coordinate system
        Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
        
        // this code will get called every time the screen is touched
        
        switch (this->gameState)
        {
            case GameState::Title:
                break;
            case GameState::Ready:
                break;
            case GameState::Playing:
                if (this->gettingHit == false) {
                    this->character->setNen(Nen::Ken);
                    this->soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ken.wav", true);
                }
                break;
            case GameState::GameOver:
                break;
            default:
                break;
        }
        
        return true;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
        this->character->setNen(Nen::Ten);
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MainScene::singlePlayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        this->triggerReady();
    }
}

void MainScene::playWeather() {
    ActionTimeline* cloudsTimeline = CSLoader::createTimeline("Clouds.csb");
    this->runAction(cloudsTimeline);
    cloudsTimeline->play("icloud", true);
}

void MainScene::onEnterTransitionDidFinish() {
    auto backgroundMusic = CocosDenshion::SimpleAudioEngine::getInstance();
    backgroundMusic->playBackgroundMusic("waterfall.wav", true);
    backgroundMusic->setBackgroundMusicVolume(0.5f);
}