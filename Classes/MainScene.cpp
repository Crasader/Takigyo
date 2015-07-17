#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MainScene.h"
#include "Globals.h"
#include "Character.h"
#include "CharacterReader.h"

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
    this->scoreLabel = rootNode->getChildByName<cocos2d::ui::Text*>("scoreLabel");
    this->countDown = 0.0f;
    
    ui::Button* playButton = this->rootNode->getChildByName<ui::Button*>("PlayButton");
    playButton->addTouchEventListener(CC_CALLBACK_2(MainScene::singlePlayerPressed, this));
    
    this->resetGameState();
    
    addChild(this->rootNode);
    
    return true;
}

void MainScene::onEnter() {
    Layer::onEnter();
    
    this->triggerTitle();
    
    this->setupTouchHandling();
    
    // schedule the update method to be called every frame
    this->scheduleUpdate();
}

#pragma mark -
#pragma mark Game Loop

void MainScene::update(float dt)
{
    // update is called before every new frame is rendered
    // dt is the amount of time elapsed (in seconds) between this update call and the previous one
    
    // call the superclass method update
    Layer::update(dt);
    
    if (this->gameState == GameState::Ready) {
        this->countDown += dt;
        
        this->setCountDown(COUNT_DOWN_TIME - this->countDown + 1);
    
        if (this->countDown > COUNT_DOWN_TIME) {
            this->gameState = GameState::Playing;
            this->dropObstacles();
            
            // load and run the title animation
            ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
            this->stopAllActions();
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
    this->scoreLabel->setString(std::to_string(this->timeLeft));
}

void MainScene::dropObstacles() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* rock = Sprite::create("FallenRock.png");
    rock->setScale(0.5f);
    rock->setZOrder(-1);
    rock->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 1.2f));
    
    auto big        = ScaleTo::create(0.0f, 1.0);
    auto moveDown   = MoveBy::create(1.0f, Vec2(0,-760));
    auto moveDown2  = MoveBy::create(0.8f, Vec2(0,-680));
    auto moveUp     = MoveBy::create(0.5f, Vec2(0,300));
    auto easeIn     = EaseIn::create(moveDown2, 4);
    rock->runAction(Sequence::create(moveDown,
                                     big,
                                     moveUp,
                                     CallFunc::create(
                                                      [rock,this]() {
                                                          rock->setZOrder(0);
                                                      }
                                                      ),
                                     easeIn,
                                     CallFunc::create([this]() {
                                                            if (this->gameState == GameState::Playing) {
                                                                if (this->character->getNen() == Nen::Ten) {
                                                                    float decreaceAura = this->auraLeft - HIT_DAMAGE;
                                                                    this->setRemainingAura(decreaceAura);
                                                                }
                                                            }
                                                            }),
                                     CallFunc::create([rock](){rock->removeFromParent();}),
                                     NULL));
    
    this->rootNode->addChild(rock);
}

#pragma mark -
#pragma mark Getters / Setters

void MainScene::setRemainingAura(float auraLeft)
{
    // clamp the time left timer to between 0 and 10 seconds
    this->auraLeft = clampf(auraLeft, 0.0f, PRESENT_OUTPUT_POTENTIAL);
    
    // update the UI to reflect the correct time left
    this->auraBar->setScaleX(auraLeft / PRESENT_OUTPUT_POTENTIAL);
}
void MainScene::resetGameState()
{
    // these variables must be reset every new game
    this->auraLeft = PRESENT_OUTPUT_POTENTIAL;
    this->countDown = 0.0f;
    this->auraBar->setScaleX(1.0f);
    // BAD
    //this->character->setNen(Nen::Ten);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* cloud = Sprite::create("cloud.png");
    cloud->setZOrder(-1);
    cloud->setScale(2.0f);
    cloud->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.9f));
    this->rootNode->addChild(cloud);
}

void MainScene::triggerTitle()
{
    this->gameState = GameState::Title;
    
    // load and run the title animation
    ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->stopAllActions();
    this->runAction(titleTimeline);
    titleTimeline->play("title", false);
    
}

void MainScene::triggerReady() {
    // set the game state to Ready
    this->gameState = GameState::Ready;
    
    // load and run the ready animations
    ActionTimeline* readyTimeline = CSLoader::createTimeline("MainScene.csb");
    this->stopAllActions();
    this->runAction(readyTimeline);
    readyTimeline->play("ready", false);
    
    auto background = this->rootNode->getChildByName("background");
    background->setZOrder(-1);
}

void MainScene::triggerGameOver()
{
    // set the game state to Game Over
    this->gameState = GameState::GameOver;
    
    this->triggerTitle();
    
    this->resetGameState();
    
    // set the timer to 0
    //this->setTimeLeft(0.0f);
    
    /*
    // get a reference to the top-most node
    auto scene = this->getChildByName("Scene");
    
    // get a reference to tha mat sprite
    auto mat = scene->getChildByName("mat");
    
    // get a reference to the game over score label
    cocos2d::ui::Text* gameOverScoreLabel = mat->getChildByName<cocos2d::ui::Text*>("gameOverScoreLabel");
    
    // set the score label to the user's score
    gameOverScoreLabel->setString(std::to_string(this->score));
    
    // load and run the game over animations
    cocostudio::timeline::ActionTimeline* gameOverTimeline = CSLoader::createTimeline("MainScene.csb");
    this->stopAllActions();
    this->runAction(gameOverTimeline);
    gameOverTimeline->play("gameOver", false);
     */
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
                //this->triggerReady();
                this->character->setNen(Nen::Ten);
                break;
                
            case GameState::Ready:
                //this->triggerPlaying();
                // no break here!
                // if we're in the playing state, use the touch to chop the sushi roll
                break;
            case GameState::Playing:
                this->character->setNen(Nen::Ken);
                break;
            case GameState::GameOver:
                //this->resetGameState();
                //this->triggerTitle();
                //this->gameState = GameState::Title;
                break;
            default:
                break;
        }
        
        return true;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
        this->character->setNen(Nen::Ten);
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MainScene::singlePlayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        this->triggerReady();
    }
}