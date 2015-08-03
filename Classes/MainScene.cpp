#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MainScene.h"
#include "Character.h"
#include "CharacterReader.h"
#include "SimpleAudioEngine.h"
#include "LevelInfo.h"
#include "PatternList.h"
#include "NetworkingWrapper.h"
#include "JSONPacker.h"
#include "Utility.h"

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
    auto waterfall       = rootNode->getChildByName("waterfall");
    auto bottomRock      = waterfall->getChildByName("bottomRock");
    this->character      = bottomRock->getChildByName<Character*>("Character");
    this->levelNode      = waterfall->getChildByName("level");
    auto lifeBG          = rootNode->getChildByName("lifeBG");
    this->auraBar        = lifeBG->getChildByName<Sprite*>("lifeBar");
    this->countDownLabel = rootNode->getChildByName<cocos2d::ui::Text*>("countDownLabel");
    this->comboLabel     = rootNode->getChildByName<cocos2d::ui::Text*>("comboLabel");
    this->cloudsNode     = rootNode->getChildByName("clouds");
    this->playCount = 0;
    this->isEvening = false;
    this->replayButtonPressing = false;
    this->onMultiPlayerMode = false;
    
    lifeBG->setZOrder(1);
   
    this->netWorkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->netWorkingWrapper->setDelegate(this);
   
    ui::Button* playButton = this->rootNode->getChildByName<ui::Button*>("PlayButton");
    playButton->addTouchEventListener(CC_CALLBACK_2(MainScene::singlePlayerPressed, this));
    
    ui::Button* vsButton = this->rootNode->getChildByName<cocos2d::ui::Button*>("VersusButton");
    vsButton->addTouchEventListener(CC_CALLBACK_2(MainScene::multiPlayerPressed, this));
    
    this->resetGameState();
    
    addChild(this->rootNode);
    
    return true;
}

void MainScene::onEnter() {
    Layer::onEnter();
    
    this->netWorkingWrapper->startAdvertisingAvailability();
    
    // schedule the update method to be called every frame
    this->scheduleUpdate();
    
    this->triggerTitle();
    
    this->playWeather();
    
    this->setupTouchHandling();
}

void MainScene::onEnterTransitionDidFinish() {
    CCLOG("onEnterTransitionDidFinish");
    auto backgroundMusic = CocosDenshion::SimpleAudioEngine::getInstance();
    backgroundMusic->playBackgroundMusic("waterfall.wav", true);
    backgroundMusic->setBackgroundMusicVolume(0.5f);
}

#pragma mark -
#pragma mark Game Loop

// パターンを開始する
void MainScene::setGameActive(bool active) {
    this->active = active;
}

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
    
    if (this->gameState == GameState::Playing) {
        this->playingTime += dt;
        this->patternPlayTime += dt;
        if (this->loadNext == true) {
            LevelInfo* levelInfo = LevelInfo::createPatternWithRound(this->gameRound);
            this->currentPattern = levelInfo->getCurrentPattern();
            this->currentLevel = levelInfo->getCurrentLevel();
            this->currentDuration = levelInfo->getCurrentDuration();
            this->currentTempo = levelInfo->getCurrentTempo();
            
            CCLOG("ROUND:%d", this->gameRound);
            CCLOG("currentLevel:%d", this->currentLevel);
//            CCLOG("currentDuration:%f", this->currentDuration);
//            CCLOG("currentTempo:%f", this->currentTempo);
            
            if (this->beforeLevel < this->currentLevel) {
                this->setLevelCount();
                this->beforeLevel = this->currentLevel;
            }
            
            this->loadNext = false;
            this->patternPlayTime = 0.0f;
            for (auto newObstacle : currentPattern) {
                this->timingList.push_back(newObstacle.timing);
                this->obstacleList.push_back(newObstacle.type);
            }
        } else if (loadNext == false) {
            if (!timingList.empty()) {
                float nextTiming = this->timingList.front();
                if (nextTiming <= patternPlayTime) {
                    ObstacleType nextObstacle = this->obstacleList.front();
                    this->timingList.erase(this->timingList.begin());
                    this->obstacleList.erase(this->obstacleList.begin());
                    this->dropObstacles(nextObstacle, this->currentTempo);
                }
            }
            if (timingList.empty() && patternPlayTime >= this->currentDuration) {
                loadNext = true;
                this->gameRound++;
            }
        }
        
        if (this->character->getNen() == Nen::Ken) {
            this->touchingTime += dt;
            setRemainingAura(auraLeft - dt);
        }
        if (this->gettingHit == true) {
            this->gettingHitCount += dt;
            if (this->gettingHitCount >= RECOVERY) {
                this->gettingHit = false;
                this->gettingHitCount = 0.0f;
            }
        }
        
        if (this->auraLeft <= 0.0f)
        {
            int totalScoreString = (this->totalPerfectCount * 3 + this->totalGreatCount * 2 + this->totalGoodCount) + this->maxComboCount;
            std::string playTimeString = StringUtils::toString(this->playingTime);
            std::string totalGreatString = StringUtils::toString(this->totalGreatCount);
            std::string totalGoodString = StringUtils::toString(this->totalGoodCount);
            std::string maxComboString = StringUtils::toString(this->maxComboCount);
            
            auto resultLeftRaft         = this->rootNode->getChildByName("leftRaft");
            auto resultRightRaft        = this->rootNode->getChildByName("rightRaft");
            auto totalPerfectScoreLabel = resultRightRaft->getChildByName<cocos2d::ui::Text*>("perfectScoreLabel");
            auto totalGreatScoreLabel   = resultRightRaft->getChildByName<cocos2d::ui::Text*>("greatScoreLabel");
            auto totalGoodScoreLabel    = resultRightRaft->getChildByName<cocos2d::ui::Text*>("goodScoreLabel");
            auto maxComboLabel          = resultRightRaft->getChildByName<cocos2d::ui::Text*>("maxComboLabel");
            auto totalScoreLabel        = resultRightRaft->getChildByName<cocos2d::ui::Text*>("totalScoreLabel");
            totalPerfectScoreLabel->setString(Utility::getScoreString(this->totalPerfectCount));
            totalGreatScoreLabel->setString(Utility::getScoreString(this->totalGreatCount));
            totalGoodScoreLabel->setString(Utility::getScoreString(this->totalGoodCount));
            maxComboLabel->setString(Utility::getScoreString(this->maxComboCount));
            totalScoreLabel->setString(Utility::getScoreString(totalScoreString));
            
            resultLeftRaft->setZOrder(1);
            resultRightRaft->setZOrder(1);
            
            ui::Button* replayButton = resultRightRaft->getChildByName<ui::Button*>("replayButton");
            replayButton->addTouchEventListener(CC_CALLBACK_2(MainScene::replayButtonPressed, this));
            replayButton->setOpacity(0);
            
            this->rootNode->runAction(Sequence::create(
                CallFunc::create(
                    [this]() {
                        // load and run the title animation
                        ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
                        this->rootNode->runAction(titleTimeline);
                        titleTimeline->play("result", false);
                    }
                    ),
                DelayTime::create(1.0f),
                CallFunc::create(
                    [replayButton]() {
                        replayButton->setOpacity(255);
                    }
                    ),
                NULL
                )
            );
            this->triggerGameOver();
        }
    }
}

void MainScene::dropObstacles(ObstacleType obstacleType, float tempo) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Node* obstacle;
    switch (obstacleType) {
        case ObstacleType::Rock:
        {
            obstacle = CSLoader::createNode("Rock.csb");
            ActionTimeline* rockTimeline = CSLoader::createTimeline("Rock.csb");
            obstacle->runAction(rockTimeline);
            rockTimeline->play("fallingRock", true);
            break;
        }
        case ObstacleType::Heart:
        {
            obstacle = CSLoader::createNode("Heart.csb");
            ActionTimeline* heartTimeline = CSLoader::createTimeline("Heart.csb");
            obstacle->runAction(heartTimeline);
            heartTimeline->play("fallingHeart", true);
            break;
        }
        default:
            break;
    }
    
    obstacle->setScale(0.5f);
    obstacle->setZOrder(-1);
    obstacle->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 1.2f));
    
    auto defaultSpeed       = 1.0f;
    auto fallSpeed          = defaultSpeed * tempo;
    auto waterfall          = this->rootNode->getChildByName("waterfall");
    auto intoWater          = MoveTo::create(fallSpeed, waterfall->getPosition() - Vec2(0, 100));
    auto getCloser          = ScaleTo::create(0.0f, 1.0f);
    auto upAboveWater       = MoveTo::create(fallSpeed, waterfall->getPosition() - Vec2(0, 30));
    auto downToCharacter    = MoveBy::create(fallSpeed, Vec2(0, -530));
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
        CallFunc::create([this, denshion, obstacleType, obstacle]() {
        if (this->gameState == GameState::Playing) {
            // While not touching the screen
            if (this->character->getNen() == Nen::Ten) {
                if (obstacleType == ObstacleType::Rock) {
                    this->gotHit();
                    obstacle->stopAllActions();
                    ActionTimeline* rockTimeline = CSLoader::createTimeline("Rock.csb");
                    obstacle->runAction(rockTimeline);
                    rockTimeline->play("rollingRock", false);
                } else if (obstacleType == ObstacleType::Heart) {
                    float remainingAura = this->auraLeft + RECOVERY;
                    this->setRemainingAura(remainingAura);
                    denshion->playEffect("heart.wav");
                    obstacle->setVisible(false);
                    
                    // Recovery particl effect
                    auto hitEffect = ParticleSystemQuad::create("recover.plist");
                    hitEffect->setAutoRemoveOnFinish(true);
                    hitEffect->setScale(0.5f);
                    hitEffect->setPosition(obstacle->getPosition());
                    this->rootNode->addChild(hitEffect);
                }
                // While "TOUCHING" the screen
            } else if (this->character->getNen() == Nen::Ken) {
                if (obstacleType == ObstacleType::Rock) {
                    denshion->playEffect("break.wav");
                    int combo = this->comboCount++;
                    this->setComboCount(combo);
                    if (this->touchingTime > 0) {
                        this->touchingCount++;
                    }
                    this->playTimingAnimation();
                    
                    obstacle->stopAllActions();
                    ActionTimeline* rockTimeline = CSLoader::createTimeline("Rock.csb");
                    obstacle->runAction(rockTimeline);
                    rockTimeline->play("breakingRock", false);
                } else if (obstacleType == ObstacleType::Heart) {
                    // Opps, you break your heart
                    denshion->playEffect("break.wav");
                    obstacle->stopAllActions();
                    ActionTimeline* heartTimeline = CSLoader::createTimeline("Heart.csb");
                    obstacle->runAction(heartTimeline);
                    heartTimeline->play("breakingHeart", false);
                }
            }
        }
    }),
    DelayTime::create(1.0f),
    // Remove from Parent
    CallFunc::create([obstacle](){obstacle->removeFromParent();}),
    NULL));
    
    this->rootNode->addChild(obstacle);
}

void MainScene::resetGameState()
{
    // these variables must be reset every new game
    this->auraLeft = PRESENT_OUTPUT_POTENTIAL;
    this->comboCount = 1;
    this->maxComboCount = 0;
    this->gettingHit = false;
    this->gettingHitCount = 0.0f;
    this->auraBar->setScaleX(1.0f);
    if (this->playCount > 0) {
        this->character->setNen(Nen::Ten);
    }
    this->loadNext = true;
    this->gameRound = 1;
    this->beforeLevel = 0;
    this->touchingTime = 0.0;
    this->touchingCount = 0;
    this->timingList = {};
    this->currentPattern = {};
    
    this->totalGoodCount = 0;
    this->totalGreatCount = 0;
    this->totalPerfectCount = 0;
}

void MainScene::triggerTitle()
{
    this->gameState = GameState::Title;
    
    // load and run the title animation
    ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->rootNode->runAction(titleTimeline);
    titleTimeline->play("title", false);
}

void MainScene::triggerReady() {
    // set the game state to Ready
    this->gameState = GameState::Playing;
    this->character->setNen(Nen::Ten);
    
    // load and run the ready animations
    ActionTimeline* readyTimeline = CSLoader::createTimeline("MainScene.csb");
    this->rootNode->runAction(readyTimeline);
    readyTimeline->play("ready", false);
    
    auto background     = this->rootNode->getChildByName<Sprite*>("background");
    
    int random = rand() % 5;
    if (random == 0) {
        this->isEvening = true;
        background->setTexture("eveningBackground.png");
    } else {
        this->isEvening = false;
        background->setTexture("sky.png");
    }
    background->setZOrder(-1);
    
}

void MainScene::triggerGameOver()
{
    this->playCount++;
    
    this->gameState = GameState::GameOver;
}

void MainScene::playTimingAnimation() {
    if (touchingCount > 0) {
        if (this->touchingTime < 0.1) {
            auto perfectLabel = this->rootNode->getChildByName("perfect");
            ActionTimeline* perfect = CSLoader::createTimeline("Timing/TimingPerfect.csb");
            perfectLabel->runAction(perfect);
            perfect->play("playPerfect", false);
            this->totalPerfectCount++;
        } else if (this->touchingTime < 0.3) {
            auto greatLabel = this->rootNode->getChildByName("great");
            ActionTimeline* great = CSLoader::createTimeline("Timing/TimingGreat.csb");
            greatLabel->runAction(great);
            great->play("playGreat", false);
            this->totalGreatCount++;
        } else if (this->touchingTime >= 0.3) {
            auto goodLabel = this->rootNode->getChildByName("good");
            ActionTimeline* good = CSLoader::createTimeline("Timing/TimingGood.csb");
            goodLabel->runAction(good);
            good->play("playGood", false);
            this->totalGoodCount++;
        }
    }
}

void MainScene::gotHit() {
    if (this->gettingHit == false) {
        this->gettingHit = true;
        auto yoko = ScaleBy::create(0.2f, 2, 0.5);
        auto tate = CCEaseBackIn::create(ScaleBy::create(0.3f, 0.5, 2));
        this->character->runAction(Sequence::create(yoko,tate,NULL));
    }
    float remainingAura = this->auraLeft - HIT_DAMAGE;
    this->setRemainingAura(remainingAura);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gothit.wav");
    this->comboCount = 1;
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

void MainScene::setComboCount(int combo) {
    if (this->maxComboCount < combo) {
        this->maxComboCount = combo;
    }
    // update the score label
    this->comboLabel->setString(std::to_string(combo));
    
    ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->rootNode->runAction(titleTimeline);
    titleTimeline->play("combo", false);
    
}

void MainScene::setLevelCount() {
    auto level = this->levelNode->getChildByName<cocos2d::ui::Text*>("Level");
    level->setString(std::to_string(this->currentLevel));
    
    ActionTimeline* levelTimeline = CSLoader::createTimeline("LevelNode.csb");
    this->levelNode->runAction(levelTimeline);
    levelTimeline->play("levelUp", false);
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
            {
                break;
            }
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
        this->touchingCount = 0;
        this->touchingTime = 0.0f;
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
    };
    touchListener->onTouchCancelled = [&](Touch* touch, Event* event) {
        this->character->setNen(Nen::Ten);
        this->touchingCount = 0;
        this->touchingTime = 0.0f;
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

#pragma mark -
#pragma mark ButtonPressed

void MainScene::singlePlayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        this->triggerReady();
    }
}

void MainScene::multiPlayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        this->netWorkingWrapper->showPeerList();
    }
}

void MainScene::replayButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED && this->replayButtonPressing == false) {
        this->replayButtonPressing = true;
        this->rootNode->runAction(
        Sequence::create(
              CallFunc::create(
                               [this]() {
                                   auto resultLeftRaft = this->rootNode->getChildByName<Sprite*>("leftRaft");
                                   auto resultRightRaft = this->rootNode->getChildByName<Sprite*>("rightRaft");
                                   auto resultLeft          = ScaleTo::create(0.5f, 0.33f);
                                   auto resultRight         = ScaleTo::create(0.5f, 0.33f);
                                   resultLeftRaft->runAction(resultLeft);
                                   resultRightRaft->runAction(resultRight);
                                   
                                   // Byebye Button
                                   ui::Button* replayButton = resultRightRaft->getChildByName<ui::Button*>("replayButton");
                                   auto replayButtonPosition = replayButton->getPosition();
                                   auto moveSomewhere   = MoveTo::create(.8f, Vec2(6.22f, 5000));
                                   auto moveBack        = MoveTo::create(1.0f, replayButtonPosition);
                                   auto rotate          = RotateBy::create(1.0f, 720.0f);
                                   auto byebye          = CCSpawn::createWithTwoActions(moveSomewhere, rotate);
                                   replayButton->runAction(
                                                           Sequence::create(
                                                                            byebye,
                                                                            DelayTime::create(5.0f),
                                                                            moveBack,
                                                                            NULL
                                                                            )
                                                           );
                               }
                               ),
              DelayTime::create(0.5f),
              CallFunc::create(
                               [this]() {
                                   this->character->setNen(Nen::Ken);
                                   this->soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ken.wav", true);
                                   ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
                                   this->rootNode->runAction(titleTimeline);
                                   titleTimeline->play("endResult", false);
                                   
                               }
                               ),
              DelayTime::create(0.3f),
              CallFunc::create(
                               [this]() {
                                   CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("break.wav");
                               }
                               ),
              DelayTime::create(0.7f),
              CallFunc::create(
                               [this]() {
                                   this->character->setNen(Nen::Ten);
                                   this->gameState = GameState::Playing;
                                   CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
                                   this->triggerReady();
                                   this->resetGameState();
                               }
                               ),
              DelayTime::create(3.0f),
              CallFunc::create(
                               [this]() {this->replayButtonPressing = false;}
                               ),
              NULL
              )
         );
    }
}

void MainScene::playWeather() {
    ActionTimeline* Timeline = CSLoader::createTimeline("Clouds.csb");
    this->rootNode->runAction(Timeline);
    Timeline->play("icloud", true);
}

#pragma mark -
#pragma mark Networking

void MainScene::receivedData(const void *data, unsigned long length) {
    const char* cstr = reinterpret_cast<const char*>(data);
    std::string json = std::string(cstr, length);
    
    CCLOG("%s", cstr);
    JSONPacker::GameState state = JSONPacker::unpackGameStateJSON(json);
    if (state.gameOver) {
        this->triggerGameOver();
    }
}

void MainScene::stateChanged(ConnectionState state) {
    switch (state) {
        case ConnectionState::CONNECTING:
            CCLOG("Connection...");
            break;
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
        case ConnectionState::CONNECTED:
            CCLOG("Connected");
            if (this->onMultiPlayerMode == false) {
                this->netWorkingWrapper->stopAdvertisingAvailability();
                this->triggerReady();
                this->onMultiPlayerMode = true;
            }
            break;
    }
}