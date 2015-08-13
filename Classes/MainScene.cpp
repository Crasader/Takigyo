#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MainScene.h"
#include "Character.h"
#include "CharacterReader.h"
#include "OpponentCharacter.h"
#include "OpponentCharacterReader.h"
#include "SimpleAudioEngine.h"
#include "LevelInfo.h"
#include "PatternList.h"
#include "NetworkingWrapper.h"
#include "GameCenterWrapper.h"
#include "JSONPacker.h"
#include "Utility.h"
#include "UserDataManager.h"
#include "RankInfo.h"
#include <random>

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
    
    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("OpponentCharacterReader", (ObjectFactory::Instance) OpponentCharacterReader::getInstance);
    
    this->rootNode = CSLoader::createNode("MainScene.csb");
    ui::Helper::doLayout(this->rootNode);
    
    this->visibleSize = Director::getInstance()->getVisibleSize();
    setContentSize(this->visibleSize);
    ui::Helper::doLayout(this);
    this->rootNode->setContentSize(this->visibleSize);
    

    this->waterfall         = rootNode->getChildByName("waterfall");
    this->bottomRock        = waterfall->getChildByName("bottomRock");
    this->bottomRock2       = waterfall->getChildByName("bottomRock2");
    this->character         = bottomRock->getChildByName<Character*>("Character");
    this->opponentCharacter = bottomRock2->getChildByName<OpponentCharacter*>("OpponentCharacter");
    this->levelNode         = waterfall->getChildByName("level");
    this->waiting           = waterfall->getChildByName("waiting");
    this->lifeBG            = rootNode->getChildByName("lifeBG");
    this->auraBar           = lifeBG->getChildByName<Sprite*>("lifeBar");
    this->lifeBG2           = rootNode->getChildByName("lifeBG2");
    this->auraBar2          = lifeBG2->getChildByName<Sprite*>("lifeBar2");
    this->countDownLabel    = rootNode->getChildByName<cocos2d::ui::Text*>("countDownLabel");
    this->cloudsNode        = rootNode->getChildByName("clouds");
    
    this->titleTimeline     = CSLoader::createTimeline("MainScene.csb");
    this->rootNode->runAction(this->titleTimeline);
    
    // NEW Label
    auto jumpAction = CCJumpBy::create(1, Vec2(0, 0), 20, 1);
    auto spawn = CCSpawn::create(jumpAction, NULL);
    auto repeatForever = CCRepeatForever::create(spawn);
    auto resultRightRaft        = this->rootNode->getChildByName("rightRaft");
    auto newLabel               = resultRightRaft->getChildByName<Sprite*>("newLabel");
    newLabel->runAction(repeatForever);
    
    // Recovery particle effect
    this->splashEffect = ParticleSystemQuad::create("splash2.plist");
    splashEffect->setScale(0.36f);
    splashEffect->setPosition(Vec2(this->visibleSize.width * 0.5f, bottomRock->getPositionY()+this->character->getScaleY()-32));
    this->rootNode->addChild(splashEffect);
    this->splashEffect2 = ParticleSystemQuad::create("splash2.plist");
    splashEffect2->setScale(0.36f);
    splashEffect2->setPosition(Vec2(this->visibleSize.width * 2.0f, bottomRock->getPositionY()+this->character->getScaleY()-32));
    this->rootNode->addChild(splashEffect2);
    
    this->playCount = 0;
    this->replayButtonPressing = false;
    this->onMultiPlayerMode = false;
    
    lifeBG->setZOrder(1);
    lifeBG2->setZOrder(1);
   
    this->netWorkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->netWorkingWrapper->setDelegate(this);
   
    ui::Button* playButton = this->rootNode->getChildByName<ui::Button*>("PlayButton");
    playButton->addTouchEventListener(CC_CALLBACK_2(MainScene::singlePlayerPressed, this));
    
    ui::Button* vsButton = this->rootNode->getChildByName<cocos2d::ui::Button*>("VersusButton");
    vsButton->addTouchEventListener(CC_CALLBACK_2(MainScene::multiPlayerPressed, this));
    
    ui::Button* RankingButton = this->rootNode->getChildByName<cocos2d::ui::Button*>("RankingButton");
    RankingButton->addTouchEventListener(CC_CALLBACK_2(MainScene::rankingButtonPressed, this));
    
    // GameCenter
    networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    networkingWrapper->setDelegate(this);
    
    gameCenterWrapper = std::unique_ptr<GameCenterWrapper>(new GameCenterWrapper());
    
    leaderBoardWrapper = std::unique_ptr<LeaderBoardWrapper>(new LeaderBoardWrapper());
    
    this->resetGameState();
    
    addChild(this->rootNode);
    
    return true;
}

void MainScene::onEnter() {
    Layer::onEnter();
    
    this->scheduleUpdate();
    
    this->login();
    
    this->netWorkingWrapper->startAdvertisingAvailability();
    
    this->triggerTitle();
    
    this->playWeather();
    
    this->setupTouchHandling();
}

void MainScene::onEnterTransitionDidFinish() {
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
    if (onMultiPlayerMode) {
        this->timeForMulti += dt;
        if (this->timeForMulti > 0.2) {
            this->timeForMulti = 0.0f;
            this->sendDataOverNetwork();
        }
    }
    
    if (this->gameState == GameState::MultiPreparation) {
        if (this->userId > 0 && this->opponentUserId > 0) {
            this->isHost = (this->userId > this->opponentUserId) ? true : false;
            this->gameState = GameState::WAITING;
            if (isHost) {
//                CCLOG("-------------YOU ARE HOST---------------");
            } else {
//                CCLOG("-------------YOU ARE CLIENT-------------");
            }
            this->sendDataOverNetwork();
        }
    } else if (this->gameState == GameState::WAITING && this->opponentGameState == GameState::MultiResult) {
        this->timeForWaiting += dt;
        if (this->timeForWaiting > 2.0) {
            this->timeForWaiting = 0.0f;
            this->sendDataOverNetwork();
            ActionTimeline* waitingTimeline = CSLoader::createTimeline("Waiting.csb");
            this->waiting->runAction(waitingTimeline);
            waitingTimeline->play("waiting", false);
        }
    } else if (this->isHost == true
               && this->gameState == GameState::WAITING
               && this->opponentGameState == GameState::WAITING) {
        if (this->nextRound == this->gameRound) {
            this->nextRound = this->gameRound + 1;
                              
            LevelInfo* levelInfo = LevelInfo::createPatternWithRound(this->gameRound);
            this->currentPatternId  = levelInfo->getCurrentPatternId();
            this->currentPattern    = levelInfo->getCurrentPattern();
            this->currentLevel      = levelInfo->getCurrentLevel();
            this->currentDuration   = levelInfo->getCurrentDuration();
            this->currentTempo      = levelInfo->getCurrentTempo();
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
            if (this->opponentGameState == GameState::GameOver) {
                this->triggerMultiGameOver();
            }
            // ホストはクライアントに、新しいパターンIDを送信（WAITING状態）
            this->sendDataOverNetwork();
            if (this->gameRound == 1) {
                this->triggerReady();
//                CCLOG("------------------");
//                CCLOG("HOST GAME READY!!!");
//                CCLOG("------------------");
            } else if (this->gameRound >= 2) {
                this->gameState = GameState::Playing;
            }
        }
    // クライアント、
    } else if (isHost == false && this->nextRound > this->gameRound && this->pastRound < this->gameRound && this->receivedPatternId > 0) {
        LevelInfo* levelInfo = LevelInfo::createPatternWithRoundAndPatternId(this->gameRound, this->receivedPatternId);
        this->currentPatternId  = levelInfo->getCurrentPatternId();
        this->currentPattern    = levelInfo->getCurrentPattern();
        this->currentLevel      = levelInfo->getCurrentLevel();
        this->currentDuration   = levelInfo->getCurrentDuration();
        this->currentTempo      = levelInfo->getCurrentTempo();
        if (this->beforeLevel < this->currentLevel) {
            this->setLevelCount();
            this->beforeLevel = this->currentLevel;
        }
        this->loadNext = false;
        this->patternPlayTime = 0.0f;
        this->pastRound = this->gameRound;
        for (auto newObstacle : currentPattern) {
            this->timingList.push_back(newObstacle.timing);
            this->obstacleList.push_back(newObstacle.type);
        }
        // 待機中にゲームオーバー
        if (this->opponentGameState == GameState::GameOver) {
            this->triggerMultiGameOver();
        }
        if (this->auraLeft <= 0.0f) {
            this->triggerMultiGameOver();
        }
        // ゲームスタート
        if (this->gameRound == 1) {
            this->triggerReady();
//            CCLOG("------------------");
//            CCLOG("CLIENT GAME READY!!!");
//            CCLOG("------------------");
        } else if (this->gameRound >= 2) {
            this->gameState = GameState::Playing;
        }
        this->sendDataOverNetwork();
    } else if (this->gameState == GameState::Playing) {
        this->playingTime += dt;
        this->patternPlayTime += dt;
        if (this->loadNext == true && this->onMultiPlayerMode == false) {
            LevelInfo* levelInfo    = LevelInfo::createPatternWithRound(this->gameRound);
            this->currentPattern    = levelInfo->getCurrentPattern();
            this->currentLevel      = levelInfo->getCurrentLevel();
            this->currentDuration   = levelInfo->getCurrentDuration();
            this->currentTempo      = levelInfo->getCurrentTempo();
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
                    if (this->onMultiPlayerMode) {
                        this->dropOpponentObstacles(nextObstacle, this->currentTempo);
                    }
                }
            }
            if (timingList.empty() && this->patternPlayTime >= this->currentDuration) {
                if (onMultiPlayerMode) {
                    loadNext = true;
                    this->gameRound++;
                    this->gameState = GameState::WAITING;
                    this->sendDataOverNetwork();
                } else {
                    loadNext = true;
                    this->gameRound++;
                }
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
        
        // 自分がプレイ中に対戦相手がゲームオーバー
        if (this->onMultiPlayerMode == true && this->opponentGameState == GameState::GameOver) {
            this->triggerMultiGameOver();
        }
        if (this->auraLeft <= 0.0f) {
            if (this->onMultiPlayerMode) {
                this->triggerMultiGameOver();
            } else {
                this->triggerGameOver();
            }
        }
    } else if (this->onMultiPlayerMode == true
               && this->gameState == GameState::GameOver
               && (this->opponentGameState == GameState::GameOver || this->opponentGameState == GameState::MultiResult)) {
        this->triggerMultiResult();
    } else if (this->gameState == GameState::MultiResult && this->opponentGameState == GameState::MultiResult) {
    }
}

void MainScene::dropObstacles(ObstacleType obstacleType, float tempo) {
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
    obstacle->setPosition(Vec2(this->visibleSize.width * 0.5f, this->visibleSize.height * 1.2f));
    
    auto rockXPosition = 0;
    if (this->onMultiPlayerMode) {
        rockXPosition = 100;
    }
    
    auto defaultSpeed       = 1.0f;
    auto fallSpeed          = defaultSpeed * tempo;
    auto waterfall          = this->rootNode->getChildByName("waterfall");
    auto intoWater          = MoveTo::create(fallSpeed, waterfall->getPosition() - Vec2(0, 100));
    auto getCloser          = ScaleTo::create(0.0f, 1.0f);
    auto upAboveWater       = MoveTo::create(fallSpeed, waterfall->getPosition() - Vec2(rockXPosition, 30));
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
        if (this->gameState == GameState::Playing || this->gameState == GameState::WAITING) {
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
                    this->sendDataOverNetwork();
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
        } else {
            obstacle->removeFromParent();
        }
    }),
    DelayTime::create(1.0f),
    // Remove from Parent
    CallFunc::create([obstacle](){obstacle->removeFromParent();}),
    NULL));
    
    this->rootNode->addChild(obstacle);
}

void MainScene::dropOpponentObstacles(ObstacleType obstacleType, float tempo) {
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
    obstacle->setPosition(Vec2(this->visibleSize.width * 0.5f, this->visibleSize.height * 1.2f));
    
    auto defaultSpeed       = 1.0f;
    auto fallSpeed          = defaultSpeed * tempo;
    auto waterfall          = this->rootNode->getChildByName("waterfall");
    auto intoWater          = MoveTo::create(fallSpeed, waterfall->getPosition() - Vec2(0, 100));
    auto getCloser          = ScaleTo::create(0.0f, 1.0f);
    auto upAboveWater       = MoveTo::create(fallSpeed, waterfall->getPosition() - Vec2(-100, 30));
    auto downToCharacter    = MoveBy::create(fallSpeed, Vec2(0, -530));
    auto easeInDown         = EaseIn::create(downToCharacter, 4);
    
    obstacle->runAction(Sequence::create(
        intoWater,
        // Enlarge the obstacle
        getCloser,
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
        // Remove from Parent
        CallFunc::create([obstacle](){obstacle->removeFromParent();}),
        NULL
    ));
    
    this->rootNode->addChild(obstacle);
}

void MainScene::resetGameState()
{
    // these variables must be reset every new game
    this->auraLeft = PRESENT_OUTPUT_POTENTIAL;
    this->auraLeft2 = PRESENT_OUTPUT_POTENTIAL;
    this->comboCount = 1;
    this->maxComboCount = 0;
    this->gettingHit = false;
    this->gettingHitCount = 0.0f;
    this->auraBar->setScaleX(1.0f);
    this->character->setNen(Nen::Ten);
    this->loadNext = true;
    this->gameRound = 1;
    this->pastRound = 0;
    this->beforeLevel = 0;
    this->touchingTime = 0.0;
    this->touchingCount = 0;
    this->timingList = {};
    this->currentPattern = {};
    this->playingTime = 0.0f;
    this->currentPatternId = 0;
    this->receivedPatternId = 0;
    
    if (this->onMultiPlayerMode) {
        this->opponentCharacter->setNen(Nen::Ten);
        this->isOpponentGameOver = false;
        this->opponentPlayingTime = 0.0f;
        this->nextRound = 1;
        this->receivedPatternId = 0;
        this->timeForWaiting = 0.0f;
    }
    
    this->totalGoodCount = 0;
    this->totalGreatCount = 0;
    this->totalPerfectCount = 0;
}


void MainScene::triggerTitle()
{
    // load and run the title animation
    titleTimeline->play("title", false);
    
    this->winScore = 0;
    this->opponentWinScore = 0;
    if (this->onMultiPlayerMode) {
        this->onMultiPlayerMode = false;
        this->netWorkingWrapper->disconnect();
        this->netWorkingWrapper->startAdvertisingAvailability();
        this->resetGameState();
        MessageBox("Disconnected...", "Network");
    }
    this->gameState = GameState::Title;
}

void MainScene::triggerReady() {
    // set the game state to Ready
    this->gameState = GameState::Playing;
    this->character->setNen(Nen::Ten);
    if (onMultiPlayerMode) {
        this->opponentCharacter->setNen(Nen::Ten);
    }
    
    // load and run the ready animations
    if (this->onMultiPlayerMode) {
        titleTimeline->play("readyMulti", false);
    } else {
        titleTimeline->play("ready", false);
    }
    
    auto background     = this->rootNode->getChildByName<Sprite*>("background");
    
    int random = rand() % 5;
    if (random == 0) {
        background->setTexture("eveningBackground.png");
    } else {
        background->setTexture("sky.png");
    }
    background->setZOrder(-1);
    
}

void MainScene::triggerMultiPreparation() {
    this->gameState = GameState::MultiPreparation;
    // 被決定的な乱数生成器でシード生成器を生成
    std::random_device rnd;
    // メルセンヌ・ツイスタ 引数は初期シード値 ファンクタを渡す
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> rand5(1,INT_MAX);
    this->userId = rand5(mt);
//    this->userId = 1;
    this->sendDataOverNetwork();
}

void MainScene::triggerMultiResult() {
    this->gameState = GameState::MultiResult;
    
    this->playCount++;
    
    // SCORE
    std::string playTimeString = StringUtils::toString(this->playingTime);
    std::string totalGreatString = StringUtils::toString(this->totalGreatCount);
    std::string totalGoodString = StringUtils::toString(this->totalGoodCount);
    std::string maxComboString = StringUtils::toString(this->maxComboCount);
    
    auto resultMultiLeftRaft         = this->rootNode->getChildByName("multiLeftRaft");
    auto resultMultiRightRaft        = this->rootNode->getChildByName("multiRightRaft");
    // Left Label
    auto winScoreLabel          = resultMultiLeftRaft->getChildByName<cocos2d::ui::Text*>("winScoreLabel");
    // Right Label
    auto totalPerfectScoreLabel = resultMultiRightRaft->getChildByName<cocos2d::ui::Text*>("perfectScoreLabel");
    auto totalGreatScoreLabel   = resultMultiRightRaft->getChildByName<cocos2d::ui::Text*>("greatScoreLabel");
    auto totalGoodScoreLabel    = resultMultiRightRaft->getChildByName<cocos2d::ui::Text*>("goodScoreLabel");
    auto maxComboLabel          = resultMultiRightRaft->getChildByName<cocos2d::ui::Text*>("maxComboLabel");
    auto opponentWinScoreLabel  = resultMultiRightRaft->getChildByName<cocos2d::ui::Text*>("opponentWinScoreLabel");
    auto winLoseLabel           = resultMultiRightRaft->getChildByName<cocos2d::ui::Text*>("winLoseLabel");
    totalPerfectScoreLabel->setString(Utility::getScoreString(this->totalPerfectCount, 0));
    totalGreatScoreLabel->setString(Utility::getScoreString(this->totalGreatCount, 0));
    totalGoodScoreLabel->setString(Utility::getScoreString(this->totalGoodCount, 0));
    maxComboLabel->setString(Utility::getScoreString(this->maxComboCount, 0));
    
    resultMultiLeftRaft->setZOrder(1);
    resultMultiRightRaft->setZOrder(1);
    
    ui::Button* replayButton = resultMultiRightRaft->getChildByName<ui::Button*>("replayButton");
    replayButton->addTouchEventListener(CC_CALLBACK_2(MainScene::replayMultiButtonPressed, this));
    
    ui::Button* topButton = resultMultiRightRaft->getChildByName<ui::Button*>("topButton");
    topButton->addTouchEventListener(CC_CALLBACK_2(MainScene::topButtonPressed, this));
    
    ui::Button* RankingButton = resultMultiLeftRaft->getChildByName<cocos2d::ui::Button*>("rankingButton");
    RankingButton->addTouchEventListener(CC_CALLBACK_2(MainScene::rankingButtonPressed, this));
    
    titleTimeline->play("multiResult", false);
    
    if (this->playingTime > this->opponentPlayingTime) {
        this->winScore++;
//        CCLOG("win:%d", this->winScore);
        winScoreLabel->setString(Utility::getScoreString(this->winScore, 3));
        opponentWinScoreLabel->setString(Utility::getScoreString(this->opponentWinScore, 3));
        winLoseLabel->setString("win");
    } else {
        this->opponentWinScore++;
//        CCLOG("oppowin:%d", this->opponentWinScore);
        winScoreLabel->setString(Utility::getScoreString(this->winScore, 3));
        opponentWinScoreLabel->setString(Utility::getScoreString(this->opponentWinScore, 3));
        winLoseLabel->setString("lose");
    }
    
}

void MainScene::triggerMultiGameOver() {
    this->gameState = GameState::GameOver;
    this->nextRound = 1;
    this->sendDataOverNetwork();
}

void MainScene::triggerGameOver()
{
    int totalScore = (this->totalPerfectCount * 3 + this->totalGreatCount * 2 + this->totalGoodCount) + this->maxComboCount + this->currentLevel;
    // 遊んだ回数を加算する
    UserDataManager* udm = UserDataManager::getInstance();
    udm->setPlayTimes(udm->getPlayTimes() + 1);
    
    int overallScoreBefore  = udm->getPlayerExp();
    int overallScoreAfter   = overallScoreBefore + totalScore;
    udm->setPlayerExp(overallScoreAfter);
    
    // 新記録かどうか
    int highScore  = udm->getPlayerHighScore();
    bool isHighScore = false;
    if (totalScore > highScore) {
        udm->setPlayerHighScore(totalScore);
        isHighScore = true;
    }
    
    // GameCenterに送信
    if (this->isLoggedIn()) {
        this->reportHighScore(totalScore);
        this->reportTotalScore(overallScoreAfter);
    }
    
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
    auto maxLevelLabel          = resultRightRaft->getChildByName<cocos2d::ui::Text*>("maxLevelLabel");
    auto totalScoreLabel        = resultRightRaft->getChildByName<cocos2d::ui::Text*>("totalScoreLabel");
    auto bestScoreLabel         = resultRightRaft->getChildByName<cocos2d::ui::Text*>("bestScoreLabel");
    auto newLabel               = resultRightRaft->getChildByName<Sprite*>("newLabel");
    totalPerfectScoreLabel->setString(Utility::getScoreString(this->totalPerfectCount, 6));
    totalGreatScoreLabel->setString(Utility::getScoreString(this->totalGreatCount, 6));
    totalGoodScoreLabel->setString(Utility::getScoreString(this->totalGoodCount, 6));
    maxComboLabel->setString(Utility::getScoreString(this->maxComboCount, 3));
    maxLevelLabel->setString(Utility::getScoreString(this->currentLevel, 3));
    totalScoreLabel->setString(Utility::getScoreString(totalScore, 6));
    bestScoreLabel->setString(Utility::getScoreString(highScore, 6));
    if (isHighScore == true) {
        newLabel->setVisible(true);
    } else {
        newLabel->setVisible(false);
    }
    
    resultLeftRaft->setZOrder(1);
    resultRightRaft->setZOrder(1);
    
    RankInfo* rankInfo = RankInfo::createPatternWithExp(overallScoreAfter);
    auto currentRankName    = rankInfo->getCurrentRankName();
    auto currentRank      = rankInfo->getCurrentRank();
    
    auto rankLabel = resultRightRaft->getChildByName<cocos2d::ui::Text*>("rankLabel");
    rankLabel->setString(currentRankName.c_str());
    
    auto fromTopLabel = resultRightRaft->getChildByName<cocos2d::ui::Text*>("fromTopLabel");
    auto fromTopString = Utility::getFromTopString(currentRank);
    fromTopLabel->setString(fromTopString);
    
    // 経験値ゲージ作成
    auto expBG                  = resultLeftRaft->getChildByName("expBG");
    auto expBar                 = expBG->getChildByName<Sprite*>("expBar");
    auto expLeft                = clampf(rankInfo->getExpWidth(), 0.0f, rankInfo->getGaugeWidth());
    expBar->setScaleX(expLeft / rankInfo->getGaugeWidth());
    
    auto expLabel               = resultLeftRaft->getChildByName<cocos2d::ui::Text*>("expLabel");
    expLabel->setString(Utility::getGaugeString(expLeft, rankInfo->getGaugeWidth()));
    
    ui::Button* replayButton = resultRightRaft->getChildByName<ui::Button*>("replayButton");
    replayButton->addTouchEventListener(CC_CALLBACK_2(MainScene::replayButtonPressed, this));
    
    ui::Button* topButton = resultRightRaft->getChildByName<ui::Button*>("topButton");
    topButton->addTouchEventListener(CC_CALLBACK_2(MainScene::topButtonPressed, this));
    
    ui::Button* RankingButton = resultLeftRaft->getChildByName<cocos2d::ui::Button*>("rankingButton");
    RankingButton->addTouchEventListener(CC_CALLBACK_2(MainScene::rankingButtonPressed, this));
    
    titleTimeline->play("resultRaft", false);
    
    this->playCount++;
    this->gameState = GameState::GameOver;
}

void MainScene::playTimingAnimation() {
    if (this->touchingTime < 0.1) {
        auto perfect = Sprite::create("perfect.png");
        perfect->setPosition(Vec2(this->visibleSize.width * 0.29f, this->visibleSize.height * 0.5f));
        perfect->setScale(2.0f, 2.0f);
        auto comboUp          = MoveBy::create(0.3f, Vec2(0,60));
        auto comboFade        = FadeTo::create(0.3f, 0.0f);
        auto comboScale       = ScaleTo::create(0.1f, 0.1f);
        auto easeIn           = EaseIn::create(comboScale, 4);
        perfect->runAction(Sequence::create(
                                            comboUp,
                                            comboFade,
                                            easeIn,
                                            CallFunc::create([perfect](){perfect->removeFromParent();}),
                                            NULL));
        this->rootNode->addChild(perfect);
        this->totalPerfectCount++;
    } else if (this->touchingTime < 0.3) {
        auto great = Sprite::create("great.png");
        great->setPosition(Vec2(this->visibleSize.width * 0.29f, this->visibleSize.height * 0.5f));
        great->setScale(2.0f, 2.0f);
        auto comboUp          = MoveBy::create(0.3f, Vec2(0,60));
        auto comboFade        = FadeTo::create(0.3f, 0.0f);
        auto comboScale       = ScaleTo::create(0.1f, 0.1f);
        auto easeIn           = EaseIn::create(comboScale, 4);
        great->runAction(Sequence::create(
                                          comboUp,
                                          comboFade,
                                          easeIn,
                                          CallFunc::create([great](){great->removeFromParent();}),
                                          NULL));
        this->rootNode->addChild(great);
        this->totalGreatCount++;
    } else if (this->touchingTime >= 0.3) {
        auto good = Sprite::create("good.png");
        good->setPosition(Vec2(this->visibleSize.width * 0.29f, this->visibleSize.height * 0.5f));
        good->setScale(2.0f, 2.0f);
        auto comboUp          = MoveBy::create(0.3f, Vec2(0,65));
        auto comboFade        = FadeTo::create(0.3f, 0.0f);
        auto comboScale       = ScaleTo::create(0.1f, 0.1f);
        auto easeIn           = EaseIn::create(comboScale, 4);
        good->runAction(Sequence::create(
                                         comboUp,
                                         comboFade,
                                         easeIn,
                                         CallFunc::create([good](){good->removeFromParent();}),
                                         NULL));
        this->rootNode->addChild(good);
        this->totalGoodCount++;
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
    this->sendDataOverNetwork();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gothit.wav");
    this->comboCount = 1;
}


#pragma mark -
#pragma mark Getters / Setters
void MainScene::setRemainingAura(float auraLeft)
{
    this->auraLeft = clampf(auraLeft, 0.0f, PRESENT_OUTPUT_POTENTIAL);
    this->auraBar->setScaleX(this->auraLeft / PRESENT_OUTPUT_POTENTIAL);
}

void MainScene::setOpponentRemainingAura(float auraLeft)
{
    this->auraLeft2 = clampf(auraLeft, 0.0f, PRESENT_OUTPUT_POTENTIAL);
    this->auraBar2->setScaleX(this->auraLeft2 / PRESENT_OUTPUT_POTENTIAL);
}

void MainScene::setComboCount(int combo) {
    if (this->maxComboCount < combo) {
        this->maxComboCount = combo;
    }
    
    auto comboLabel = Label::createWithTTF("0", "Game of Three.ttf", 72);
    comboLabel->setString(std::to_string(combo));
    comboLabel->setPosition(Vec2(this->visibleSize.width * 0.29f, this->visibleSize.height * 0.4f));
    comboLabel->setColor(Color3B::WHITE);
    comboLabel->enableShadow(Color4B::GRAY,Size(1,1),2);
    comboLabel->enableOutline(Color4B::BLACK,5);
    auto comboUp          = MoveBy::create(0.5f, Vec2(0,120));
    auto comboFade          = FadeTo::create(0.5f, 0.0f);
    comboLabel->runAction(Sequence::create(
                                           comboUp,comboFade,
                                           CallFunc::create([comboLabel](){comboLabel->removeFromParent();}),
    NULL));
    this->rootNode->addChild(comboLabel);
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
                this->character->setNen(Nen::Ken);
                break;
            case GameState::Ready:
            {
                break;
            }
            case GameState::Playing:
                if (this->gettingHit == false) {
                    this->character->setNen(Nen::Ken);
                    this->soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("woosh.wav", true);
                    this->sendDataOverNetwork();
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
        this->sendDataOverNetwork();
        this->touchingTime = 0.0f;
        CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
    };
    touchListener->onTouchCancelled = [&](Touch* touch, Event* event) {
        this->character->setNen(Nen::Ten);
        this->sendDataOverNetwork();
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
        this->resetGameState();
    }
}

void MainScene::multiPlayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        this->netWorkingWrapper->showPeerList();
    }
}

void MainScene::rankingButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        this->showLeaderBoard();
    }
}

void MainScene::replayMultiButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED && this->replayButtonPressing == false) {
        this->replayButtonPressing = true;
        this->rootNode->runAction(
        Sequence::create(
              CallFunc::create(
                               [this]() {
//                                   auto resultLeftRaft = this->rootNode->getChildByName<Sprite*>("leftRaft");
                                   auto resultRightRaft = this->rootNode->getChildByName<Sprite*>("rightRaft");
                                   
                                   // Byebye Button
                                   ui::Button* replayButton = resultRightRaft->getChildByName<ui::Button*>("replayButton");
                                   auto replayButtonPosition = replayButton->getPosition();
                                   auto moveSomewhere   = MoveTo::create(.8f, Vec2(3.22f, 2500));
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
              DelayTime::create(0.2f),
              CallFunc::create(
                               [this]() {
                                   this->character->setNen(Nen::Ken);
                                   this->soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ken.wav", true);
                                   titleTimeline->play("multiEndResult", false);
                                   
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
                                   this->resetGameState();
                                   this->gameState = GameState::WAITING;
                                   CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
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

void MainScene::replayButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED && this->replayButtonPressing == false) {
        this->replayButtonPressing = true;
        this->rootNode->runAction(
        Sequence::create(
              CallFunc::create(
                               [this]() {
//                                   auto resultLeftRaft = this->rootNode->getChildByName<Sprite*>("leftRaft");
                                   auto resultRightRaft = this->rootNode->getChildByName<Sprite*>("rightRaft");
                                   
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
              DelayTime::create(0.2f),
              CallFunc::create(
                               [this]() {
                                   this->character->setNen(Nen::Ken);
                                   this->soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ken.wav", true);
                                   titleTimeline->play("endResultRaft", false);
                                   
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
                                   this->triggerReady();
                                   this->resetGameState();
                                   CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
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

void MainScene::topButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        this->triggerTitle();
//        this->resetGameState();
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
    
//    CCLOG("RECEIVED_DATA:%s", cstr);
    JSONPacker::UserData userData       = JSONPacker::unpackUserDataJSON(json);
    this->opponentGameState             = userData.state;
    this->opponentCharacter->setNen(userData.nen);
    this->setOpponentRemainingAura(userData.auraLeft);
    this->opponentPlayingTime           = userData.playTime;
    this->nextRound                     = this->isHost ? this->nextRound : userData.nextRound;
    this->receivedPatternId             = userData.patternId;
    this->opponentUserId                = userData.userId;
}

void MainScene::stateChanged(ConnectionState state) {
    switch (state) {
        case ConnectionState::CONNECTING:
//            CCLOG("Connection...");
            break;
        case ConnectionState::NOT_CONNECTED:
//            this->userId = 0;
//            this->opponentUserId = 0;
//            this->isHost = false;
//            
//            this->setSinglePlayMode();
            this->triggerTitle();
            break;
        case ConnectionState::CONNECTED:
//            CCLOG("------------");
//            CCLOG("OISHO:CONNECTED");
//            CCLOG("------------");
        
            this->onMultiPlayerMode = true;
            
            // 以下の変数はネットワーク開始時と終了時に初期化する
            this->userId = 0;
            this->opponentUserId = 0;
            this->isHost = false;
            
            this->resetGameState();
            this->setMultiPlayMode();
            this->triggerMultiPreparation();
//            CCLOG("Connected");
            break;
    }
}

void MainScene::sendDataOverNetwork() {
    if (onMultiPlayerMode) {
        JSONPacker::UserData data;
        data.state      = (GameState)this->gameState;
        data.nen        = this->character->getNen();
        data.auraLeft   = this->auraLeft;
        data.playTime   = this->playingTime;
        data.patternId  = this->isHost ? this->currentPatternId : this->receivedPatternId;
        data.userId     = this->userId;
        data.nextRound  = this->nextRound;
        
        std::string json = JSONPacker::packUserData(data);
        netWorkingWrapper->sendData(json.c_str(), json.length());
//        CCLOG("PACKED_DATA:%s", json.c_str());
    }
}

void MainScene::setSinglePlayMode() {
    splashEffect->setPosition(Vec2(this->visibleSize.width * 0.5f, bottomRock->getPositionY()+this->character->getScaleY()-32));
    splashEffect2->setPosition(Vec2(this->visibleSize.width * 2.0f, bottomRock2->getPositionY()+this->character->getScaleY()-32));
    bottomRock->setPositionX(this->visibleSize.width * 0.6f);
    bottomRock2->setPositionX(this->visibleSize.width * 1.5f);
}

void MainScene::setMultiPlayMode() {
    splashEffect->setPosition(Vec2(this->visibleSize.width * 0.36f, bottomRock->getPositionY()+this->character->getScaleY()-32));
    splashEffect2->setPosition(Vec2(this->visibleSize.width * 0.64f, bottomRock2->getPositionY()+this->character->getScaleY()-32));
    bottomRock->setPositionX(this->visibleSize.width * 0.46f);
    bottomRock2->setPositionX(this->visibleSize.width * .75f);
}

#pragma mark - GameCenter Methods

void MainScene::login()
{
    gameCenterWrapper->loginGameCenter();
}

bool MainScene::isLoggedIn()
{
    return gameCenterWrapper->isLoggedIn();
}

void MainScene::showLeaderBoard()
{
    leaderBoardWrapper->showRanking();
}

void MainScene::reportHighScore(int score)
{
    leaderBoardWrapper->reportHighScore(score);
}

void MainScene::reportTotalScore(int exp)
{
    leaderBoardWrapper->reportTotalScore(exp);
}