//
//  Prop.cpp
//  Match
//
//  Created by 程小二 on 14-2-25.
//
//

#include "Prop.h"
#include "matchAlgorithm.h"

Prop::Prop()
{}

Prop::~Prop() {}

Prop* Prop::create()
{
    Prop *pret = new Prop;
    pret->init();
    pret->autorelease();
    return pret;
}

bool Prop::init()
{
    return true;
}

void Prop::setupProp()
{
    auto sprite = Sprite::create("animation/energy_ball01.png");
    this->addChild(sprite);
    this->setContentSize(sprite->getContentSize());
    
    sprite->setPosition(Point(getContentSize().width/2, getContentSize().height/2));
    
    Animation* animation = Animation::create();
    for(int i=1;i<4;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "animation/energy_ball%02d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    //should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(0.08);
    animation->setRestoreOriginalFrame(true);
    Animate* action = Animate::create(animation);
    sprite->runAction(RepeatForever::create(action));
    return;
}

void Prop::propAutoBoomb(const colorSpriteEnum rc[ROW][COL], std::vector<coord>& vecs)
{
    bool boxes[ROW][COL];
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            boxes[r][c] = false;
        }
    }
    
    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            if(!boxes[r][c])
            {
                std::vector<coord> collection;
                matchAlgorithm::findSameColorsSprite(rc,r,c,collection);
                
                if(collection.size() >= 3)
                    std::copy(std::begin(collection), std::end(collection), std::back_inserter(vecs));
                
                for(int i=0; i<collection.size(); i++)
                {
                    coord co = collection[i];
                    boxes[co.r][co.c] = true;
                }
            }
        }
    }
}

void Prop::propBoomb(const colorSpriteEnum rc[ROW][COL], std::vector<coord>& vecs, int r, int c)
{
    for(int x=0; x<ROW; x++)
    {
        coord cd;
        cd.r = x;
        cd.c = c;
        if(!isProp(rc, cd.r, cd.c))
           vecs.push_back(cd);
    }
    return;
}

void Prop::propSameColorBoomb(const colorSpriteEnum rc[ROW][COL], std::vector<coord>& vecs)
{
    colorSpriteEnum  arr[5] = {kA,kB,kC,kD,kE};
    
    int max = 0;
    int cnt = 0;
    colorSpriteEnum max_cs = kA;
    
    //找到数量最多的某一种元素
    for(int i=0; i<sizeof arr / sizeof arr[0]; i++){
        colorSpriteEnum cs = arr[i];
        cnt = 0;
        for(int r=0; r<ROW; r++){
            for(int c=0; c<COL; c++){
                if(rc[r][c] == cs)
                    cnt = cnt+1;
            }
        }
        
        if(cnt >= max){
            max = cnt;
            max_cs = cs;
        }
    }
    
    for(int r = 0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            if(max_cs == rc[r][c])
            {
                coord cd;
                cd.r = r;
                cd.c = c;
                vecs.push_back(cd);
            }
        }
    }
}

void Prop::propCrossBooomb(const colorSpriteEnum rc[ROW][COL], int r, int c, std::vector<coord>& rowVecs,std::vector<coord>& colVecs)
{
    //collect row
    for(int i=0; i<ROW; i++)
    {
        coord cd;
        cd.r = i;
        cd.c = c;
        
        if(!(cd.r == r && cd.c == c))
            if(!isProp(rc, cd.r, cd.c))
              colVecs.push_back(cd);
    }
    
    //collect col
    for(int i=0; i<COL; i++)
    {
        coord cd;
        cd.r = r;
        cd.c = i;
        
        if(!(cd.r == r && cd.c == c))
            if(!isProp(rc, cd.r, cd.c))
              rowVecs.push_back(cd);
    }
    return;
}

void Prop::propFiveColorSpace(colorSpriteEnum newRc[ROW][COL])
{
//    colorSpriteEnum csarray[] = {kA,kB,kC,kD,kE};
//    bool boolbxo[ROW][COL];
//    for(int r=0; r<ROW; r++)
//    {
//        for(int c=0; c<COL; c++)
//        {
//            boolbxo[r][c] = false;
//        }
//    }
//    int avg = ROW*COL/5;
//    int avg_least = ROW*COL%5;
//    
//    ////////all do that is fresh rc, and born new rc
//    //////////////kA//////////////
//    int r = CCRANDOM_0_1()*(ROW-1);
//    int c = CCRANDOM_0_1()*(COL-1);
//    while(boolbxo[r][c])
//    {
//        r = CCRANDOM_0_1()*(ROW-1);
//        c = CCRANDOM_0_1()*(COL-1);
//    }
//    WalkSameColor(r, c, boolbxo, newRc, csarray[0], avg);
    ////////////////////////////////////////////
    
    newRc[ROW-1][0] = kA;
    newRc[ROW-1][1] = kA;
    newRc[ROW-1][2] = kA;
    
    newRc[ROW-2][0] = kA;
    newRc[ROW-2][1] = kA;
    newRc[ROW-2][2] = kA;
    
    newRc[ROW-3][0] = kA;
    newRc[ROW-3][1] = kA;
    newRc[ROW-3][2] = kA;
    newRc[ROW-3][3] = kA;
    
    newRc[1][ROW-4] = kA;
    
    
    newRc[0][0] = kB;
    newRc[1][0] = kB;
    newRc[2][0] = kB;
    newRc[3][0] = kB;
    
    newRc[1][1] = kB;
    newRc[2][1] = kB;
    
    newRc[2][2] = kB;
    newRc[3][2] = kB;
    
    
    newRc[0][1] = kC;
    newRc[0][2] = kC;
    newRc[0][3] = kC;
    
    newRc[1][2] = kC;
    newRc[1][3] = kC;
    newRc[1][4] = kC;
    newRc[1][5] = kC;
    
    newRc[2][5] = kC;
    
    
    newRc[0][4] = kD;
    newRc[0][5] = kD;
    newRc[0][6] = kD;
    newRc[1][6] = kD;
    newRc[2][6] = kD;
    newRc[3][6] = kD;
    newRc[4][6] = kD;
    newRc[5][6] = kD;
    newRc[6][6] = kD;
    
    newRc[2][3] = kE;
    newRc[2][4] = kE;
    
    newRc[3][3] = kE;
    newRc[3][4] = kE;
    newRc[3][5] = kE;
    
    newRc[4][4] = kE;
    newRc[4][5] = kE;
    
    newRc[5][3] = kE;
    newRc[5][4] = kE;
    newRc[5][5] = kE;
    
    newRc[6][3] = kE;
    newRc[6][4] = kE;
    newRc[6][5] = kE;
    
    return;
}


void Prop::propRandomBoomNBoxes(const colorSpriteEnum rc[ROW][COL], std::vector<coord>& vecs)
{
    bool boolbox[ROW][COL];
    for(int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            boolbox[i][j] = false;
        }
    }
    
    int n = 20;
    for(int i=0; i<n; i++)
    {
        int x = CCRANDOM_0_1()*(ROW-1);
        int y = CCRANDOM_0_1()*(COL-1);
        
        while(boolbox[x][y] && !isProp(rc, x, y))
        {
            x = CCRANDOM_0_1()*(ROW-1);
            y = CCRANDOM_0_1()*(COL-1);
        }
        
        coord cd;
        cd.r = x;
        cd.c = y;
        vecs.push_back(cd);
    }
}

void Prop::WalkSameColor(int r, int c, bool boolbxo[ROW][COL], colorSpriteEnum newRc[ROW][COL], colorSpriteEnum curCS, int cnt)
{
    std::vector<coord> vecs;
    std::queue<coord> queues;
    coord co;
    co.r = r;
    co.c = c;
    
    queues.push(co);
    vecs.push_back(co);
    newRc[r][c] = curCS;
    boolbxo[r][c] = true;
    
    while (queues.size() > 0 && vecs.size() < cnt) {
        coord co = queues.front();
        queues.pop();
        int r = co.r;
        int c = co.c;
        
        //down
        if(r-1 >= 0 && !boolbxo[r-1][c] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r-1;
            cd.c = c;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r-1][c] = curCS;
            boolbxo[r-1][c] = true;
        }
        
        //up
        if(r+1 < ROW && !boolbxo[r+1][c] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r+1;
            cd.c = c;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r+1][c] = curCS;
            boolbxo[r+1][c] = true;
        }
        
        //left
        if(c-1 >= 0 && !boolbxo[r][c-1] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r;
            cd.c = c-1;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r][c-1] = curCS;
            boolbxo[r][c-1] = true;
        }
        
        //right
        if(c+1 < COL-1 && !boolbxo[r][c+1] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r;
            cd.c = c+1;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r][c+1] = curCS;
            boolbxo[r][c+1] = true;
        }
        
        //left top
        if(c-1 >=0 && r+1 <ROW && !boolbxo[r+1][c-1] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r+1;
            cd.c = c-1;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r+1][c-1] = curCS;
            boolbxo[r+1][c-1] = true;
        }
        
        if(c+1 >=0 && r+1 <ROW && !boolbxo[r+1][c+1] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r+1;
            cd.c = c+1;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r+1][c+1] = curCS;
            boolbxo[r+1][c+1] = true;
        }

        if(c-1 >=0 && r-1 <ROW && !boolbxo[r-1][c-1] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r-1;
            cd.c = c-1;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r-1][c-1] = curCS;
            boolbxo[r-1][c-1] = true;
        }
        
        if(c+1 >=0 && r-1 <ROW && !boolbxo[r-1][c+1] && vecs.size() < cnt)
        {
            coord cd;
            cd.r = r-1;
            cd.c = c+1;
            
            queues.push(cd);
            vecs.push_back(cd);
            newRc[r-1][c+1] = curCS;
            boolbxo[r-1][c+1] = true;
        }

    }
}

bool Prop::isProp(const colorSpriteEnum rc[ROW][COL], int r, int c)
{
    assert(r>=0 && r<ROW);
    assert(c>=0 && c<COL);
    colorSpriteEnum cs = rc[r][c];
    if(cs == kA || cs == kB || cs == kC || cs == kD || cs == kE)
        return false;
    return true;
}













