//
//  CharacterReader.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/15.
//
//

#ifndef __Takigyo__CharacterReader__
#define __Takigyo__CharacterReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class CharacterReader : public cocostudio::NodeReader
{
public:
    static CharacterReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__Takigyo__CharacterReader__) */
