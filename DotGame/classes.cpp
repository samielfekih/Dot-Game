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
    prisoner = false;
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

bool Case::isPrisoner(){
    return prisoner;
}

void Case::prisonerIn(){
    prisoner = true;
}

void Case::prisonerOut(){
    prisoner = false;
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

Action::Action(){
    
}

Wall::Wall(int a, int b , int c, int d){
    vector<Case*> cases;
    //wallNumber ++;
    Case * ptr(0);
    if (a == b){
        for (int i= c; i<= d; i++){
            *ptr = Case(a,i);
            cases.push_back(ptr);
            //ptr->setWall(wallNumber);
        }
    }
    else if (c==d){
        for (int i= a; i<= b; i++){
            *ptr = Case(i,c);
            cases.push_back(ptr);
            //ptr->setWall(wallNumber);
        }
    }
}

void Wall::destroyWall(){
    for (Case* ptr :cases){
        ptr->setWall(0);
    }
}


DestroyWall::DestroyWall(Wall* w){
    wall = w;
}

void DestroyWall::execute(Button* b){
    if (b->getCase()->isPrisoner())
        wall->destroyWall();
}

Button::Button(){
    
}

Button::Button(Case* c, Action a){
    square = c;
    action = a;
}
Case* Button::getCase(){
    return square;
}

WallButton :: WallButton(Case* c, Wall* w){
    DestroyWall a = DestroyWall(w);
    Button (c,a);
}

WallButton::WallButton(Grid* g, int x, int y, Wall*w){
    WallButton (g->getCase(x,y),w);
}

WallButton::WallButton(Grid* g, int x, int y, int a, int b, int c, int d){
    Wall wall = Wall(a,b,c,d);
    WallButton(g,x,y,&wall);
}



/*Kill::Kill(int x, int y){
    
}*/
