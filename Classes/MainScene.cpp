#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Initialize State
    this->gameState = GameState::Title;
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);

    addChild(rootNode);
    
    auto background = rootNode->getChildByName("background");
    background->setZOrder(-1);
    
    Sprite* cloud = Sprite::create("cloud.png");
    cloud->setZOrder(0);
    cloud->setScale(2.0f);
    cloud->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.9f));
    rootNode->addChild(cloud);
    
    Sprite* rock = Sprite::create("FallenRock.png");
    rock->setScale(0.5f);
    rock->setZOrder(-1);
    rock->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 1.2f));
    auto big        = ScaleTo::create(0.0f, 1.0);
    auto moveDown   = MoveBy::create(1.5f, Vec2(0,-760));
    auto moveDown2  = MoveBy::create(0.5f, Vec2(0,-650));
    auto moveUp     = MoveBy::create(1.5f, Vec2(0,300));
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
                                     NULL));
    
    rootNode->addChild(rock);
    
    // load and run the title animation
    cocostudio::timeline::ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->stopAllActions();
    this->runAction(titleTimeline);
    titleTimeline->play("title", false);
    
    return true;
}

void MainScene::onEnter() {
    Layer::onEnter();
    
    
}