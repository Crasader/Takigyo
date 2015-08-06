//
//  OpponentCharacter.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/08/04.
//
//

#include "OpponentCharacter.h"

USING_NS_TIMELINE

bool OpponentCharacter::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    // Always keep on madicated with ten
    this->nen = Nen::Ten;
    
    // load the character animation timeline
    // this->timeline = CSLoader::createTimeline("OpponentCharacter.csb");
    
    // retain the character animation timeline so it doesn't get deallocated
    // this->timeline->retain();
    
    return true;
}

Nen OpponentCharacter::getNen()
{
    return this->nen;
}

void OpponentCharacter::setNen(Nen nen)
{
    this->nen = nen;
    
    ActionTimeline* opponentCharacterTimeline = CSLoader::createTimeline("OpponentCharacter.csb");
    this->runAction(opponentCharacterTimeline);
    if (this->nen == Nen::Ken)
    {
        opponentCharacterTimeline->play("Ken", false);
    }
    else
    {
        opponentCharacterTimeline->play("Ten", false);
    }
}