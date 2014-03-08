//
//  effect.h
//  Match
//
//  Created by 程小二 on 14-3-5.
//
//

#ifndef Match_effect_h
#define Match_effect_h

#include "cocos2d.h"
#include "util.h"

using namespace cocos2d;

class effect : public Node
{
public:
    effect();
    ~effect();
    static effect* create();
    bool init();
    
    
    void boxDeadEffect(const std::vector<coord>& vecs,  std::vector<FiniteTimeAction*>& actions);
    void boxDead(int r, int c);
    
    void crossBoomb(const std::vector<coord>& colVecs,
                    const std::vector<coord>& rowVecs);
    
    void crossBoombAnimation(Point pos);
private:
};

#endif
