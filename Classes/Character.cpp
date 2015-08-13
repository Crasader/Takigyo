//
//  Character.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/15.
//
//

#include "Character.h"

USING_NS_TIMELINE

bool Character::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    // Always keep on madicated with ten
    this->nen = Nen::Ten;
    
    // load the character animation timeline
    // this->timeline = CSLoader::createTimeline("Character.csb");
    
    // retain the character animation timeline so it doesn't get deallocated
    // this->timeline->retain();
    
    return true;
}

Nen Character::getNen()
{
    return this->nen;
}

void Character::setNen(Nen nen)
{
    this->nen = nen;
    
    ActionTimeline* characterTimeline = CSLoader::createTimeline("Character.csb");
    this->runAction(characterTimeline);
    if (this->nen == Nen::Ken)
    {
        characterTimeline->play("Ken", true);
    }
    else
    {
        characterTimeline->play("Ten", false);
    }
}