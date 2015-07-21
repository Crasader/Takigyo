//
//  JSONPacker.h
//  Takigyo
//
//  Created by Shota Oiyama on 2015/07/21.
//
//

#ifndef __Takigyo__JSONPacker__
#define __Takigyo__JSONPacker__

namespace JSONPacker{
    //    struct GameState {
    //        std::string name;
    //        bool gameOver;
    //        int score;
    //        std::vector<std::vector<cocos2d::Color3B>> board;
    //    };
    
    struct LevelInfo {
        int level;
        float tempo;
        std::vector<int> patternRate;
    };
    
    LevelInfo unpackLevelInfoJSON(std::string json, int round);
    //    GameState unpackGameStateJSON(std::string json);
    //    std::string packGameState(const GameState data);
    
}

#endif /* defined(__Takigyo__JSONPacker__) */
