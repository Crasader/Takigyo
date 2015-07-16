//
//  Character.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/15.
//
//

#ifndef __Takigyo__Character__
#define __Takigyo__Character__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Globals.h"

class Character : public cocos2d::Node
{
public:
    CREATE_FUNC(Character);
    
    bool init() override;
    void setNen(Nen nen);
    Nen getNen();
    
protected:
    Nen nen;
    
};

#endif /* defined(__Takigyo__Character__) */
