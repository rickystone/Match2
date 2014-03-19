//
//  streamGame.h
//  Match
//
//  Created by 程小二 on 14-3-15.
//
//

#ifndef Match_streamGame_h
#define Match_streamGame_h

#include "util.h"

class streamGame
{
public:
    static void writeGame(const colorSpriteEnum rc[ROW][COL]);
    static void readGame(colorSpriteEnum rc[ROW][COL]);
};

#endif
