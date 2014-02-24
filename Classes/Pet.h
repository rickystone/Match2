//
//  Pet.h
//  Match
//
//  Created by 程小二 on 14-2-17.
//
//

#ifndef Match_Pet_h
#define Match_Pet_h

#include "cocos2d.h"
using namespace cocos2d;

class Pet : public Node
{
public:
    Pet();
    ~Pet();
    static Pet* create();
    bool init();
    
    void removePet();
    void setupPet();
};


#endif
