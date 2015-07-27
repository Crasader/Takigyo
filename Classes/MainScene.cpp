#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MainScene.h"
#include "Character.h"
#include "CharacterReader.h"
#include "SimpleAudioEngine.h"
#include "LevelInfo.h"
#include "PatternList.h"

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
    this->comboLabel     = rootNode->getChildByName<cocos2d::ui::Text*>("comboLabel");
    this->levelLabel     = rootNode->getChildByName<cocos2d::ui::Text*>("levelLabel");
    this->cloudsNode = rootNode->getChildByName("clouds");
    this->playCount = 0;
    this->isEvening = false;
    this->isIntro = false;
    
    ui::Button* playButton = this->rootNode->getChildByName<ui::Button*>("PlayButton");
    playButton->addTouchEventListener(CC_CALLBACK_2(MainScene::singlePlayerPressed, this));
    
    this->resetGameState();
    
    addChild(this->rootNode);
    
    return true;
}

void MainScene::onEnter() {
    Layer::onEnter();
    
    // schedule the update method to be called every frame
    this->scheduleUpdate();
    
    this->triggerTitle();
    
    this->setupTouchHandling();
    
    this->playWeather();
    //test
    //this->setGameActive();
}

#pragma mark -
#pragma mark Game Loop

// パターンを開始する
void MainScene::setGameActive(bool active) {
    this->active = active;
    
//    if (this->active) {
//        this->schedule(CC_SCHEDULE_SELECTOR(MainScene::step), this->stepInterval);
//        this->scheduleUpdate();
//    } else {
//        this->unschedule(CC_SCHEDULE_SELECTOR(MainScene::step));
//        this->unscheduleUpdate();
//    }
    
    // TODO: パターン通りに岩を降らす処理
    
    // パターンが終わったタイミングで次のパターンを開始する
//    float duration = pattern->duration;
//    this->runAction(Sequense::create(
//                                     DelayTime::create(duration),
//                                     CallFunc::create([this](){
//                                        this->startNewRound();
//                                     }),
//                                     NULL
//                                     ));
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
    
    if (this->gameState == GameState::Ready) {
        this->isIntro = true;
    }
    if (this->gameState == GameState::Playing && this->isIntro == false) {
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
//                CCLOG("BEFORE:%d", this->beforeLevel);
//                CCLOG("CURRENT:%d", this->currentLevel);
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
//                    CCLOG("timing:%f", nextTiming);
                    this->dropObstacles(nextObstacle, this->currentTempo);
                }
            }
            if (timingList.empty() && patternPlayTime >= this->currentDuration) {
//                CCLOG("FINISH PATTERN");
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
        // if the timer is less than or equal to 0, the game is over
        if (this->auraLeft <= 0.0f)
        {
            CCLOG("MAX:%d", this->maxComboCount);
            std::string scoreString = StringUtils::toString(this->playingTime);
            std::string messageContent = "Your earned " + scoreString + " Meditation Points! (Time)";
            MessageBox(messageContent.c_str(), "Game Over");
            
            this->triggerGameOver();
        }
    }
}

void MainScene::dropObstacles(ObstacleType obstacleType, float tempo) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // default obstacle
    Sprite* obstacle;
    switch (obstacleType) {
        case ObstacleType::Rock:
        {
            obstacle = Sprite::create("rock.png");
//            CCLOG("obstacle:%s", "rock");
            break;
        }
        case ObstacleType::Heart:
        {
            obstacle = Sprite::create("heart.png");
//            CCLOG("obstacle:%s", "heart");
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
                                     CallFunc::create([this, denshion, obstacleType]() {
                                                            if (this->gameState == GameState::Playing) {
                                                                // While not touching the screen
                                                                if (this->character->getNen() == Nen::Ten) {
                                                                    if (obstacleType == ObstacleType::Rock) {
                                                                        this->gotHit();
                                                                    } else if (obstacleType == ObstacleType::Heart) {
                                                                        float remainingAura = this->auraLeft + RECOVERY;
                                                                        this->setRemainingAura(remainingAura);
                                                                        denshion->playEffect("heart.wav");
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
                                                                    } else if (obstacleType == ObstacleType::Heart) {
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
        auto yoko = ScaleBy::create(0.2f, 2, 0.5);
        auto tate = CCEaseBackIn::create(ScaleBy::create(0.3f, 0.5, 2));
        this->character->runAction(Sequence::create(yoko,tate,NULL));
    }
    float remainingAura = this->auraLeft - HIT_DAMAGE;
    this->setRemainingAura(remainingAura);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gothit.wav");
    this->comboCount = 1;
}

void MainScene::setComboCount(int combo) {
    if (this->maxComboCount < combo) {
        this->maxComboCount = combo;
    }
    // update the score label
    this->comboLabel->setString(std::to_string(combo));
    
    ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->runAction(titleTimeline);
    titleTimeline->play("combo", false);
}

void MainScene::setLevelCount() {
    // update the level label
    this->levelLabel->setString(std::to_string(this->currentLevel));
    
    ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->runAction(titleTimeline);
    titleTimeline->play("levelUp", false);
    
//    CCLOG("LEVELUP");
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
    this->comboCount = 1;
    this->maxComboCount = 0;
    this->gettingHit = false;
    this->gettingHitCount = 0.0f;
    this->auraBar->setScaleX(1.0f);
    if (this->playCount > 0) {
        this->character->setNen(Nen::Ten);
    }
    this->isIntro = false;
    this->loadNext = true;
    this->gameRound = 1;
    this->beforeLevel = 0;
    this->touchingTime = 0.0;
    this->touchingCount = 0;
    this->timingList = {};
    this->currentPattern = {};
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
    
    this->runAction(Sequence::create(
                                     CallFunc::create(
                                                      [this]() {
                                                          // load and run the title animation
                                                          ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
                                                          this->runAction(titleTimeline);
                                                          titleTimeline->play("intro", false);
                                                      }
                                                      ),
                                     DelayTime::create(1.0f),
                                     CallFunc::create(
                                                      [this]() {
                                                          auto introLeftRaft = this->rootNode->getChildByName<Sprite*>("introLeftRaft");
                                                          auto introRightRaft = this->rootNode->getChildByName<Sprite*>("introRightRaft");
                                                          auto introLeft          = ScaleTo::create(0.5f, 2.0f);
                                                          auto introRight         = ScaleTo::create(0.5f, 2.0f);
                                                          introLeftRaft->runAction(introLeft);
                                                          introRightRaft->runAction(introRight);
                                                      }
                                                      ), NULL
                                     )
                    );
}

void MainScene::triggerGameOver()
{
    this->playCount++;
    
    this->gameState = GameState::GameOver;
    
    this->resetGameState();
    
    this->triggerTitle();
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
        if (touchingCount > 0) {
            ActionTimeline* timingTimeline = CSLoader::createTimeline("Timing.csb");
            this->runAction(timingTimeline);
            if (this->touchingTime < 0.1) {
                timingTimeline->play("perfect", false);
            } else if (this->touchingTime < 0.3) {
                timingTimeline->play("great", false);
            } else if (this->touchingTime < 0.5) {
                timingTimeline->play("good", false);
            } else {
                CCLOG("Hmm...");
            }
            this->touchingCount = 0;
        }
        this->touchingTime = 0;
        if (this->gameState == GameState::Ready) {
            // load and run the title animation
            this->runAction(Sequence::create(
                                             CallFunc::create(
                                                              [this]() {
                                                                  auto introLeftRaft = this->rootNode->getChildByName<Sprite*>("introLeftRaft");
                                                                  auto introRightRaft = this->rootNode->getChildByName<Sprite*>("introRightRaft");
                                                                  auto introLeft          = ScaleTo::create(0.5f, 1.0f);
                                                                  auto introRight         = ScaleTo::create(0.5f, 1.0f);
                                                                  introLeftRaft->runAction(introLeft);
                                                                  introRightRaft->runAction(introRight);
                                                              }
                                                              ),
                                             DelayTime::create(0.5f),
                                             CallFunc::create(
                                                              [this]() {
                                                                  this->character->setNen(Nen::Ken);
                                                                  this->soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ken.wav", true);
                                                                  ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
                                                                  this->runAction(titleTimeline);
                                                                  titleTimeline->play("endIntro", false);
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
                                                                  this->isIntro = false;
                                                                  this->gameState = GameState::Playing;
                                                                  CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
                                                              }
                                                              ), NULL
                                             )
                            );
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
    };
    touchListener->onTouchCancelled = [&](Touch* touch, Event* event) {
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
    ActionTimeline* Timeline = CSLoader::createTimeline("Clouds.csb");
    this->runAction(Timeline);
    Timeline->play("icloud", true);
}

void MainScene::onEnterTransitionDidFinish() {
    auto backgroundMusic = CocosDenshion::SimpleAudioEngine::getInstance();
    backgroundMusic->playBackgroundMusic("waterfall.wav", true);
    backgroundMusic->setBackgroundMusicVolume(0.5f);
}