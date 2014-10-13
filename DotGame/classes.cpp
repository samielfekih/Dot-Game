//
//  classes.cpp
//  Fractal
//
//  Created by Sami El Fekih on 27/09/2014.
//  Copyright (c) 2014 Sami El Fekih. All rights reserved.
//

#include <cmath>
#include "classes.h"

using namespace std;

Case::Case(int x, int y){
    positionX = x;
    positionY = y;
    wall = 0;
    action = 0;
    white = 0;
    animation = 0;
}

int Case::getX(){
    return positionX;
}

int Case::getY(){
    return positionY;
}

int Case::getWall(){
    return wall;
}

void Case::setWall(int w){
    wall = w;
}


int Case::getAction(){
    return action;
}

void Case::setAction(int a){
    action = a;
}

int Case::getWhite(){
    return white;
}

void Case::setWhite(){
    white = 4;
}

void Case::unwhite(){
    if (white>0)
        white --;
}

void Case::setAnimation(int a){
    animation = a;
}

void Case::stopAnimation(){
    animation = 0;
}

int Case::getAnimation(){
    return animation;
}

Grid::Grid(){
    width = 0;
    height = 0;
    cases = std::map<int,Case*>();
}

Grid::Grid(int i, int j){
    width = i;
    height = j;
    Case * ptr(0);
    cases = std::map<int,Case*>();
    for (int a = 0; a< i; a++){
        for (int b=0; b<j; b++){
            ptr = new Case(a,b);
            cases[a*width+b]=ptr;
        }
    }
}


Case* Grid::getCase(int x, int y){
    return cases[x*width+y];
}

/*Kill::Kill(int x, int y){
    
}*/
