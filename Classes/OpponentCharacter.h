//
//  OpponentCharacter.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/04.
//
//

#ifndef __Takigyo__OpponentCharacter__
#define __Takigyo__OpponentCharacter__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Globals.h"

class OpponentCharacter : public cocos2d::Node
{
public:
    CREATE_FUNC(OpponentCharacter);
    
    bool init() override;
    void setNen(Nen nen);
    Nen getNen();
    
protected:
    Nen nen;
    
};

#endif /* defined(__Takigyo__OpponentCharacter__) */
