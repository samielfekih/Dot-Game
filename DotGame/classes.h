//
//  classes.h
//  SFML
//
//  Created by Sami El Fekih on 27/09/2014.
//  Copyright (c) 2014 Sami El Fekih. All rights reserved.
//

#ifndef __SFML__classes__
#define __SFML__classes__

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>

class Map;

class Case{
    
    public :
    Case(int x, int y);
    int getX();
    int getY();
    void setWall(int w);
    void setAction (int a);
    void setWhite();
    void unwhite();
    int getWhite();
    int getWall();
    int getAction();
    void setAnimation(int a);
    void stopAnimation();
    int getAnimation();
    
    private :
    int positionX;
    int positionY;
    int wall;
    int action;
    int white;
    int animation;
};

class Grid{
    public :
    Grid();
    Grid(int i, int j);
    Case* getCase(int x, int y);
    
    private :
    int width;
    int height;
    std::map<int,Case*> cases;
};

class Actor{
    
};

class Wall{
    public :
    Wall(int a1, int a2, int b1, int b2);
    void destroyWall();
    
    private :
    std::vector<Case*> cases;
};

class Policeman{
    
};

class Action {
    
public:
    Action();
    void execute();
};

class Kill: Action{
public:
    Kill(int x, int y);
    void execute();
    
private:
    
};

class Follow : Action{
    
};

class DestroyWall : Action{
    
};

class Patrol : Action {
    
};

class FindTarget : Action{
    
};


class Move : Action {
    
};


class Level {
    
};


#endif /* defined(__SFML__classes__) */
