//
//  Utility.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/28.
//
//

#ifndef __Takigyo__Utility__
#define __Takigyo__Utility__

class Utility : public cocos2d::Layer{
public:
    static std::string getScoreString (int score, int numCount);
    static std::string getTimeString (int timeSec);
    static void _printNodeRecursive(Node* node, int count, std::function<void (Node*)> func);
    static void printNode(Node* node);
    static void printNode(Node* node, std::function<void (Node* node)> func);
};

#endif /* defined(__Takigyo__Utility__) */
