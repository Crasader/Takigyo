//
//  GameCenterWrapper.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/10.
//
//

#ifndef Takigyo_GameCenterWrapper_h
#define Takigyo_GameCenterWrapper_h

#include "NetworkManagerDelegate.h"

#ifdef __OBJC__
@class GameCenterManager;
#else
typedef struct objc_object GameCenterManager;
#endif

class NetworkingDelegate;
enum class SendDataMode;

class GameCenterDelegate
{
public:
    virtual void startOnlineGame() = 0;
    virtual void didLoggedIn() = 0;
};

class GameCenterWrapper : public NetworkManagerDelegate, GameCenterManagerDelegate
{
public:
    GameCenterWrapper();
    ~GameCenterWrapper();
    
    void setDelegates(NetworkingDelegate* delegate1, GameCenterDelegate* delegate2);
    
    void loginGameCenter();
    bool isLoggedIn();
    void startRequestMatching();
    void sendData(const void* data, unsigned long length, SendDataMode mode);
    
private:
    GameCenterManager* gameCenterManager;
    NetworkingDelegate* networkingDelegate;
    GameCenterDelegate* gameCenterDelegate;
    
    void receivedData(const void* data, unsigned long length) override;
    void stateChanged(ConnectionState state) override;
    void startOnlineGame() override;
    void didLoggedIn() override;
};

#endif