//
//  OpponentCharacterReader.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/04.
//
//

#include "OpponentCharacterReader.h"
#include "OpponentCharacter.h"

using namespace cocos2d;

static OpponentCharacterReader* _instanceOpponentCharacterReader = nullptr;

OpponentCharacterReader* OpponentCharacterReader::getInstance()
{
    if (!_instanceOpponentCharacterReader)
    {
        _instanceOpponentCharacterReader = new OpponentCharacterReader();
    }
    return _instanceOpponentCharacterReader;
}

void OpponentCharacterReader::purge()
{
    CC_SAFE_DELETE(_instanceOpponentCharacterReader);
}

Node* OpponentCharacterReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    OpponentCharacter* node = OpponentCharacter::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}