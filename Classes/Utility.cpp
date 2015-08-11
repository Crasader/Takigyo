//
//  Utility.cpp
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/28.
//
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Utility.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

std::string Utility::getTimeString(int timeSec)
{
    int minute = timeSec / 60;
    int second = timeSec % 60;
    
    std::ostringstream minute_out, second_out;
    minute_out << std::setfill('0') << std::setw(2) << minute;
    second_out << std::setfill('0') << std::setw(2) << second;
    
    return std::string(minute_out.str() + ":" + second_out.str());
};

std::string Utility::getScoreString(int score, int numCount = 7) {
    std::ostringstream score_out;
    score_out << std::setfill('0') << std::setw(numCount) << score;
    
    return std::string(score_out.str());
};

std::string Utility::getFromTopString(int rank) {
    std::ostringstream fromTop;
    if (rank == 2 || rank == 22) {
        fromTop << "THE " << rank << "ND FROM TOP";
    } else if (rank == 3  || rank == 23) {
        fromTop << "THE " << rank << "RD FROM TOP";
    } else if (rank == 21) {
        fromTop << "THE " << rank << "ST FROM TOP";
    } else if (rank == 1) {
        fromTop << "THE TOP MONK";
    } else {
        fromTop << "THE " << rank << "TH FROM TOP";
    }
    
    return std::string(fromTop.str());
};

std::string Utility::getGaugeString(int current, int next) {
    std::ostringstream gaugeString;
    
    gaugeString << current << " / " << next;
    
    return std::string(gaugeString.str());
};

void Utility::_printNodeRecursive(Node* node, int count, std::function<void (Node*)> func)
{
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
    if (count != 0) {
        printf("┣");
    }
    printf("name = %s, class = %s, ", node->getName().c_str(), typeid(*node).name());
    if (func) {
        func(node);
    }
    printf("\n");
    
    for (auto child : node->getChildren()) {
        _printNodeRecursive(child, count + 1, func);
    }
};

void Utility::printNode(Node* node)
{
    _printNodeRecursive(node, 0, NULL);
};

void Utility::printNode(Node* node, std::function<void (Node* node)> func)
{
    _printNodeRecursive(node, 0, func);
};