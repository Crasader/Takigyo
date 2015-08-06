//
//  OpponentCharacterReader.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/04.
//
//

#ifndef __Takigyo__OpponentCharacterReader__
#define __Takigyo__OpponentCharacterReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class OpponentCharacterReader : public cocostudio::NodeReader
{
public:
    static OpponentCharacterReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__Takigyo__OpponentCharacterReader__) */
