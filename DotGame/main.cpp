#include <SFML/Graphics.hpp>
#include <iostream>
#include "classes.h"

//const int PARAM = 5;
const int LARGEUR_CASE = 15;
const int LARGEUR_ESPACE = 3;
const int NOMBRE_LIGNES = 30;
const int NOMBRE_COLONNES = 35;
const int LARGEUR_ECRAN = (NOMBRE_COLONNES)*(LARGEUR_CASE+LARGEUR_ESPACE)+LARGEUR_ESPACE;
const int LONGUEUR_ECRAN = (NOMBRE_LIGNES)*(LARGEUR_CASE+LARGEUR_ESPACE)+LARGEUR_ESPACE;
sf::Color gray = sf::Color(31,31,31);
sf::Color orange = sf::Color(255,128,0);
sf::Color gray2 = sf::Color(171,171,171);
sf::Color gray3 = sf::Color(140,140,140);
sf::Color gray4 = sf::Color(105,105,105);
const sf::Color whiteColor[] = {gray,gray4,gray3,gray2,sf::Color::White};
const sf::Color wallColor[] = {gray,sf::Color::Cyan,sf::Color::Green,sf::Color::Yellow,sf::Color::Magenta,orange};
int x0,y0;
int level = 1;
bool destwall[] = {false,false,false,false,false};
int const NOMBRE_POLICIERS =10 ;
int nbHP = 0 , nbVP = 0, nbRP = 0,nbF=0;
int xHP[NOMBRE_POLICIERS], yHP[NOMBRE_POLICIERS],xVP[NOMBRE_POLICIERS], yVP[NOMBRE_POLICIERS],pasx[NOMBRE_POLICIERS],pasy[NOMBRE_POLICIERS];
int xRP[NOMBRE_POLICIERS], yRP[NOMBRE_POLICIERS],x1RP[NOMBRE_POLICIERS], y1RP[NOMBRE_POLICIERS],x2RP[NOMBRE_POLICIERS], y2RP[NOMBRE_POLICIERS];
int xF[NOMBRE_POLICIERS],yF[NOMBRE_POLICIERS];
bool horaire[NOMBRE_POLICIERS];

Grid grid = Grid(NOMBRE_COLONNES,NOMBRE_LIGNES);

void newHorizontalWall(int x1, int x2,int y,int value){
    for (int i = x1 ; i< x2+1 ; i++){
        grid.getCase(i,y)->setWall(value);
    }
}

void newVerticalWall(int y1, int y2,int x, int value){
    for (int i = y1 ; i< y2+1 ; i++){
        grid.getCase(x,i)->setWall(value);
    }
}

void newRectangularWall(int x1, int x2,int y1,int y2,int value){
    newHorizontalWall(x1,x2,y1,value);
    newHorizontalWall(x1,x2,y2,value);
    newVerticalWall(y1,y2,x1,value);
    newVerticalWall(y1,y2,x2,value);
}

void recdestroyWall(int x, int y, int value){
    destwall[value] = true;
    if (y<NOMBRE_LIGNES){
        if (grid.getCase(x,y+1)->getWall() == value){
            grid.getCase(x,y+1)->setWall(4);
            grid.getCase(x,y+1)->setAnimation(value);
        }
        if (grid.getCase(x,y+1)->getWall()== 0){
            grid.getCase(x,y+1)->setWall(4);
            recdestroyWall(x,y+1,value);
        }
        if (x<NOMBRE_COLONNES){
            if (grid.getCase(x+1,y+1)->getWall() == value)
                grid.getCase(x+1,y+1)->setWall(4);
            if (grid.getCase(x+1,y+1)->getWall()== 0){
                grid.getCase(x+1,y+1)->setWall(4);
                recdestroyWall(x+1,y+1,value);
            }
        }
        if (x>0){
            if (grid.getCase(x-1,y+1)->getWall() == value)
                grid.getCase(x-1,y+1)->setWall(4);
            if (grid.getCase(x-1,y+1)->getWall()== 0){
                grid.getCase(x-1,y+1)->setWall(4);
                recdestroyWall(x-1,y+1,value);
            }
        }
    }
    if (x<NOMBRE_COLONNES){
        if (grid.getCase(x+1,y)->getWall() == value)
            grid.getCase(x+1,y)->setWall(4);
        if (grid.getCase(x+1,y)->getWall()== 0){
            grid.getCase(x+1,y)->setWall(4);
            recdestroyWall(x+1,y,value);
        }
    }
    if (x>0){
        if (grid.getCase(x-1,y)->getWall() == value)
            grid.getCase(x-1,y)->setWall(4);
        if (grid.getCase(x-1,y)->getWall()== 0){
            grid.getCase(x-1,y)->setWall(4);

            recdestroyWall(x-1,y,value);
        }
    }
    if (y>0){
        if (grid.getCase(x,y-1)->getWall() == value)
            grid.getCase(x,y-1)->setWall(4);
        if (grid.getCase(x,y-1)->getWall()== 0){
            grid.getCase(x,y-1)->setWall(4);
            recdestroyWall(x,y-1,value);
        }
        if (x<NOMBRE_COLONNES){
            if (grid.getCase(x+1,y-1)->getWall() == value)
                grid.getCase(x+1,y-1)->setWall(4);
            if (grid.getCase(x+1,y-1)->getWall()== 0){
                grid.getCase(x+1,y-1)->setWall(4);
                recdestroyWall(x+1,y-1,value);
            }
        }
        if (x>0){
            if (grid.getCase(x-1,y-1)->getWall() == value)
                grid.getCase(x-1,y-1)->setWall(4);
            if (grid.getCase(x-1,y-1)->getWall()== 0){
                grid.getCase(x-1,y-1)->setWall(4);
                recdestroyWall(x-1,y-1,value);
            }
        }
    }


}


void destroyWall(int value){
    //recdestroyWall(x,y,value);
    //destwall = false;
    for (int i =0; i< NOMBRE_COLONNES ; i++){
        for (int j = 0 ; j< NOMBRE_LIGNES ; j++)
            if (grid.getCase(i,j)->getWall() == 4)
                grid.getCase(i,j)->setWall(0);
    }
}

void setPolice(int nbp, int px[], int py[], bool horizontal){
    if (horizontal){
        for (int i=0; i<nbp; i++){
            xHP[i] = px[i];
            yHP[i] = py[i];
            pasx[i] = 1;
        }
    }
    else {
        for (int i=0; i<nbp; i++){
            xVP[i] = px[i];
            yVP[i] = py[i];
            pasy[i] = 1;
        }
    }

}

void level1(){
    
    x0 = 9; y0=15;
    grid = Grid(NOMBRE_COLONNES,NOMBRE_LIGNES);
//    grid.getCase(0,0)->getWall();
    newRectangularWall(5, 30, 10, 20, 1);
    grid.getCase(27,15)->setAction(4);
    nbF = 1;
    xF[0]=26;
    yF[0]=15;
    
}

void level2(){
    x0 = 15; y0=15;
    grid = Grid(NOMBRE_COLONNES,NOMBRE_LIGNES);
    
    newRectangularWall(5, 30, 10, 20, 1);
    grid.getCase(27,15)->setAction(4);
    newVerticalWall(11, 19, 24,2);
    grid.getCase(8,15)->setAction(2);
    
    nbVP=0;
    xVP[0] = 9; yVP[0] = 15;
    pasy[0] = 1;
    
    nbRP =3;
    xRP[0] = 9; yRP[0] = 15;
    x1RP[0] = 7; y1RP[0] = 13;
    x2RP[0] = 9; y2RP[0] = 17;
    horaire[0] = true;
    xRP[1] = 9; yRP[1] = 15;
    x1RP[1] = 7; y1RP[1] = 13;
    x2RP[1] = 9; y2RP[1] = 17;
    horaire[1] = false;
    xRP[2] = 28; yRP[2] = 15;
    x1RP[2] = 26; y1RP[2] = 13;
    x2RP[2] = 28; y2RP[2] = 17;
    horaire[2] = false;


}

void level3(){
    x0 = 7; y0=15;
    grid = Grid(NOMBRE_COLONNES,NOMBRE_LIGNES);
    
    newVerticalWall(10, 20, 4,1);
    newVerticalWall(20, 28, 10,1);
    newVerticalWall(2, 10, 10,1);
    newVerticalWall(20, 28, 20,1);
    newVerticalWall(2, 10, 20,1);
    newVerticalWall(10, 20, 26,1);
    
    newHorizontalWall(4, 10, 10, 1);
    newHorizontalWall(4, 10, 20, 1);
    newHorizontalWall(10, 20, 28, 1);
    newHorizontalWall(10, 20, 2, 1);
    newHorizontalWall(20, 26, 10, 1);
    newHorizontalWall(20, 26, 20, 1);
    
    newRectangularWall(12,18,22,26,2);
    newRectangularWall(12,18,4,8,3);
    
    grid.getCase(15,6)->setAction(4);
    grid.getCase(15,24)->setAction(3);
    grid.getCase(23,15)->setAction(2);

    
    nbHP = 4 ;
    nbVP = 7;
    int horizontalpolicesX[] = {12,14,16,11};
    int horizontalpolicesY[] = {12,14,16,10};
    int verticalpolicesX[] = {10,12,14,16,18,20,22};
    int verticalpolicesY[] = {12,14,16,16,14,12,10};
    
    setPolice(nbHP,horizontalpolicesX, horizontalpolicesY, true);
    setPolice(nbVP,verticalpolicesX, verticalpolicesY, false);
}


void level4(){
    x0 = 9; y0=15;
    grid = Grid(NOMBRE_COLONNES,NOMBRE_LIGNES);
    
    newRectangularWall(5, 30, 10, 20, 1);
    newVerticalWall(11, 19, 20,2);
    newVerticalWall(11, 19, 24,3);
    
    grid.getCase(9,12)->setAction(2);
    grid.getCase(9,18)->setAction(3);
    grid.getCase(28,15)->setAction(4);
    
    nbF = 1;
    xF[0]=26;
    yF[0]=15;
    
}

void level5(){
    x0 = 9; y0=15;
    grid = Grid(NOMBRE_COLONNES,NOMBRE_LIGNES);
    
    newHorizontalWall(4, 12, 10,1);
    newVerticalWall(10, 20, 4,1);
    newHorizontalWall(4, 12, 20,1);
    newVerticalWall(18, 20, 12,1);
    newHorizontalWall(12, 22, 18,1);
    newVerticalWall(18, 20, 22,1);
    newHorizontalWall(22, 30, 20,1);
    newVerticalWall(10, 20, 30,1);
    newVerticalWall(11, 19, 28,2);
    newVerticalWall(11, 19, 25,3);
    newVerticalWall(11, 19, 27,2);
    newVerticalWall(11, 19, 25,3);
    newVerticalWall(11, 19, 24,3);
    newVerticalWall(10, 20, 30,1);
    newHorizontalWall(22, 30, 10,1);
    newVerticalWall(10, 12, 22,1);
    newHorizontalWall(12, 22, 12,1);
    newVerticalWall(10, 12, 12,1);
    

    grid.getCase(9,12)->setAction(2);
    grid.getCase(9,18)->setAction(3);
    grid.getCase(7,12)->setAction(3);
    grid.getCase(7,18)->setAction(2);
    grid.getCase(29,15)->setAction(4);
    
    nbHP = 7 ;
    nbVP = 3;
    int horizontalpolicesX[] = {12,26,26,26,26,26,12};
    int horizontalpolicesY[] = {12,13,14,15,16,17,18};
    int verticalpolicesX[] = {18,20,22};
    int verticalpolicesY[] = {12,14,16};
    
    setPolice(nbHP,horizontalpolicesX, horizontalpolicesY, true);
    setPolice(nbVP,verticalpolicesX, verticalpolicesY, false);
    
}

void level6(){
    x0 = 25;
    y0 = 15;
    grid = Grid(NOMBRE_COLONNES,NOMBRE_LIGNES);
    
    newVerticalWall(9, 21, 5,1);
    newVerticalWall(9, 14, 17,1);
    newVerticalWall(16, 21, 17,1);
    newVerticalWall(9, 14, 19,1);
    newVerticalWall(16, 21, 19,1);
    newVerticalWall(9, 21, 31,1);
    
    newHorizontalWall(5, 17, 9,1);
    newHorizontalWall(5, 17, 21,1);
    newHorizontalWall(5, 17, 9,1);
    newHorizontalWall(17, 19, 14,1);
    newHorizontalWall(17, 19, 16,1);
    newHorizontalWall(19, 31, 21,1);
    newHorizontalWall(19, 31, 9,1);
    
    newRectangularWall(6, 16, 10, 20, 2);
    newRectangularWall(7, 15, 11, 19, 3);
    newRectangularWall(8, 14, 12, 18, 2);
    newRectangularWall(9, 13, 13, 17, 3);
    
    grid.getCase(11,15)->setAction(4);
    grid.getCase(24,14)->setAction(3);
    grid.getCase(23,18)->setAction(2);
    grid.getCase(27,13)->setAction(3);
    grid.getCase(27,17)->setAction(2);
    
    nbHP = 8 ;
    nbVP = 8 ;
    int horizontalpolicesX[] = {20,20,20,20,30,30,30,30};
    int horizontalpolicesY[] = {12,14,16,18,12,14,16,18};
    int verticalpolicesX[] = {22,24,26,28,22,24,26,28};
    int verticalpolicesY[] = {10,10,10,10,20,20,20,20};
    setPolice(nbHP,horizontalpolicesX, horizontalpolicesY, true);
    setPolice(nbVP,verticalpolicesX, verticalpolicesY, false);

}


void execute(int level){
    if (level ==1)
        level1();
    if (level ==2)
        level2();
    if (level ==3)
        level3();
    if (level ==4)
        level4();
    if (level ==5)
        level5();
    if (level ==6)
        level6();
}

void horizontalPolice(int *x, int *y, int *pasx, int level){
        if (grid.getCase(*x + *pasx,*y)->getWall())
            *pasx = -1**pasx;
        else
            *x += *pasx;
        if (x0==*x && y0 == *y){
            execute(level);
        }
}

void verticalPolice(int *x, int *y, int *pasy, int level){
        if (grid.getCase(*x,*y + *pasy)->getWall())
            *pasy = -1*(*pasy);
        else
            *y += *pasy;
        if (x0==*x && y0 == *y){
            execute(level);
        }
}


void rectangularPolice(int *x, int *y, int x1, int y1, int x2, int y2,bool *horaire, int level){
    int pas1 = 1, pas2 = -1;
    bool b = true;
        if (*x == x1){
            if (*horaire & (*y< y2)){
                verticalPolice(x, y, &pas1, level);
                b = false;
            }
            else if (!*horaire & (*y> y1)){
                verticalPolice(x, y, &pas2, level);
                b = false;
            }
        }
        if ((*y == y2) && b){
            if (*horaire & (*x< x2)){
                horizontalPolice(x, y, &pas1,level);
                b = false;
            }
            else if (!*horaire & (*x> x1)){
                horizontalPolice(x, y, &pas2,level);
                b = false;
            }
        }
        if ((*x == x2) && b){
            if (*horaire & (*y> y1)){
                verticalPolice(x, y, &pas2,level);
                b = false;
            }
            else if (!*horaire & (*y< y2)){
                verticalPolice(x, y, &pas1,level);
                b = false;
            }
        }
        if ((*y == y1) && b){
            if (*horaire & (*x> x1)){
                horizontalPolice(x, y, &pas2,level);
                b = false;
            }
            else if (!*horaire & (*x< x2)){
                horizontalPolice(x, y, &pas1,level);
                b = false;
            }
        }
    
}

int nextpas(int a,int b){
    if (a> b)
        return 1;
    else if (a == b)
        return 0;
    else return -1;
}


void followerexe(int *a, int *b, int c, int d){
    *a += nextpas(c,*a);
    *b += nextpas(d,*b);
}

bool police(int x, int y, int x1, int y1){
    return (x == x1 && y== y1);
}

int main()
{
   // Wall::wallNumber=1;
	// crÈation de la fenÍtre
	sf::RenderWindow window(sf::VideoMode(LARGEUR_ECRAN, LONGUEUR_ECRAN), "My window");
    int timer = 0;
    level1();
    window.clear(sf::Color::Black);
    
    
    while (window.isOpen())
    {
        // on traite tous les ÈvËnements de la fenÍtre qui ont ÈtÈ gÈnÈrÈs depuis la derniËre itÈration de la boucle
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            // fermeture de la fenÍtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        
        
        // effacement de la fenÍtre en noir
        window.clear(sf::Color::Black);
        
        sf::sleep(sf::milliseconds(5));
        timer ++;
        
        if (timer%40==0){
            for (int i = 0; i< 4; i++){
                if (destwall[i]){
                    destroyWall(i);
                    destwall[i] = false;
                }
            }
        }
        
        if (timer%20==0){
            for (int i = 0; i< nbF ; i ++){
                followerexe(&xF[i],&yF[i],x0,y0);
                if (police(x0,y0,xF[i],yF[i]))
                    execute(level);
            }
        }
        
        if (timer%7==0){
            
            for (int i =0; i<NOMBRE_COLONNES;i++){
                for (int j=0; j<NOMBRE_LIGNES;j++){
                    grid.getCase(i,j)->unwhite();
                }
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && y0>0 && !grid.getCase(x0,y0-1)->getWall()){
                y0--;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && y0<NOMBRE_LIGNES && !grid.getCase(x0,y0+1)->getWall()){
                y0++;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x0>0 && !grid.getCase(x0-1,y0)->getWall()){
                x0--;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x0<NOMBRE_COLONNES && !grid.getCase(x0+1,y0)->getWall()){
                x0++;
            }
            grid.getCase(x0,y0)->setWhite();

        if (grid.getCase(x0,y0)->getAction()){
            if (grid.getCase(x0,y0)->getAction()==4){
                nbHP = 0;
                nbVP = 0;
                nbRP = 0;
                nbF = 0;
                level ++;
                execute(level);
            }
            else{
                recdestroyWall(x0,y0,grid.getCase(x0,y0)->getAction());
            }
            grid.getCase(x0,y0)->setAction(0);
        }
        for (int i = 0; i< nbHP ; i ++){
            if (police(x0,y0,xHP[i],yHP[i]))
                execute(level);
        }
        for (int i = 0; i< nbVP ; i ++){
            if (police(x0,y0,xVP[i],yVP[i]))
                execute(level);
        }
        for (int i = 0; i< nbRP ; i ++){
            if (police(x0,y0,xRP[i],yRP[i]))
                execute(level);
        }
        for (int i = 0; i< nbF ; i ++){
            if (police(x0,y0,xF[i],yF[i]))
                execute(level);
        }
            
        }
        
        if (timer%10==0){
        
            for (int i = 0; i< nbHP ; i ++){
                horizontalPolice(&(xHP[i]),&(yHP[i]),&(pasx[i]),level);
            }
            for (int i = 0; i< nbVP ; i ++){
                verticalPolice(&(xVP[i]),&(yVP[i]),&(pasy[i]),level);
            }
            for (int i = 0; i< nbRP ; i ++){
                rectangularPolice(&(xRP[i]),&(yRP[i]), x1RP[i], y1RP[i], x2RP[i], y2RP[i], &(horaire[i]),level);
            }
                    }
        
        
        sf::RectangleShape rectangle(sf::Vector2f(LARGEUR_CASE, LARGEUR_CASE));
        //rectangle.setFillColor(gray);
        int x =0, y=0;
        rectangle.setPosition(LARGEUR_ESPACE+x*(LARGEUR_CASE+LARGEUR_ESPACE), LARGEUR_ESPACE+y*(LARGEUR_CASE+LARGEUR_ESPACE));
        rectangle.setFillColor(whiteColor[grid.getCase(x,y)->getWhite()]);

        if (grid.getCase(x,y)->getWall())
            rectangle.setFillColor(wallColor[grid.getCase(x,y)->getWall()]);
        for (int i = 0; i< 4; i++){
                if (destwall[i]){
                    if (grid.getCase(x,y)->getWall()==4)
                        rectangle.setFillColor(wallColor[i]);
                }
        }
        if (grid.getCase(x,y)->getAction())
            rectangle.setFillColor(wallColor[grid.getCase(x,y)->getAction()]);
        
        grid.getCase(x0,y0)->setWhite();
        
        for (int i = 0; i< nbF ; i ++){
            if (police(x,y,xF[i],yF[i]))
                rectangle.setFillColor(orange);
        }
        for (int i = 0; i< nbHP ; i ++){
            if (police(x,y,xHP[i],yHP[i]))
                rectangle.setFillColor(sf::Color::Red);
        }
        for (int i = 0; i< nbVP ; i ++){
            if (police(x,y,xVP[i],yVP[i]))
                rectangle.setFillColor(sf::Color::Red);
        }
        for (int i = 0; i< nbRP ; i ++){
            if (police(x,y,xRP[i],yRP[i]))
                rectangle.setFillColor(sf::Color::Red);
        }
   
        window.draw(rectangle);
        //rectangle.setFillColor(gray);
       // rectangle.setFillColor(whiteColor[grid.getCase(x,y)->getWhite()]);
        
        // fin de la frame courante, affichage de tout ce qu'on a dessinÈ
        while (y<NOMBRE_LIGNES){
            x=0;
            rectangle.setPosition(LARGEUR_ESPACE+x*(LARGEUR_CASE+LARGEUR_ESPACE), LARGEUR_ESPACE+y*(LARGEUR_CASE+LARGEUR_ESPACE));
            rectangle.setFillColor(whiteColor[grid.getCase(x,y)->getWhite()]);
            if (grid.getCase(x,y)->getWall())
                rectangle.setFillColor(wallColor[grid.getCase(x,y)->getWall()]);
            for (int i = 0; i< 4; i++){
                if (destwall[i]){
                    if (grid.getCase(x,y)->getWall()==4)
                        rectangle.setFillColor(wallColor[i]);
                }
            }
            if (grid.getCase(x,y)->getAction())
                rectangle.setFillColor(wallColor[grid.getCase(x,y)->getAction()]);
            grid.getCase(x0,y0)->setWhite();
            for (int i = 0; i< nbF ; i ++){
                if (police(x,y,xF[i],yF[i]))
                    rectangle.setFillColor(orange);
            }
            for (int i = 0; i< nbHP ; i ++){
                if (police(x,y,xHP[i],yHP[i]))
                    rectangle.setFillColor(sf::Color::Red);
            }
            for (int i = 0; i< nbVP ; i ++){
                if (police(x,y,xVP[i],yVP[i]))
                    rectangle.setFillColor(sf::Color::Red);
            }
            for (int i = 0; i< nbRP ; i ++){
                if (police(x,y,xRP[i],yRP[i]))
                    rectangle.setFillColor(sf::Color::Red);
            }

            window.draw(rectangle);
                        //rectangle.setFillColor(gray);
            while (x<NOMBRE_COLONNES-1){
                x++;
                rectangle.setFillColor(whiteColor[grid.getCase(x,y)->getWhite()]);
                rectangle.setPosition(LARGEUR_ESPACE+x*(LARGEUR_CASE+LARGEUR_ESPACE), LARGEUR_ESPACE+y*(LARGEUR_CASE+LARGEUR_ESPACE));
                if (grid.getCase(x,y)->getWall())
                    rectangle.setFillColor(wallColor[grid.getCase(x,y)->getWall()]);
                for (int i = 0; i< 4; i++){
                    if (destwall[i]){
                        if (grid.getCase(x,y)->getWall()==4)
                            rectangle.setFillColor(wallColor[i]);
                    }
                }
                if (grid.getCase(x,y)->getAction())
                    rectangle.setFillColor(wallColor[grid.getCase(x,y)->getAction()]);
                for (int i = 0; i< nbF ; i ++){
                    if (police(x,y,xF[i],yF[i]))
                        rectangle.setFillColor(orange);
                }
                for (int i = 0; i< nbHP ; i ++){
                    if (police(x,y,xHP[i],yHP[i]))
                        rectangle.setFillColor(sf::Color::Red);
                }
                for (int i = 0; i< nbVP ; i ++){
                    if (police(x,y,xVP[i],yVP[i]))
                        rectangle.setFillColor(sf::Color::Red);
                }
                for (int i = 0; i< nbRP ; i ++){
                    if (police(x,y,xRP[i],yRP[i]))
                        rectangle.setFillColor(sf::Color::Red);
                }
         

                window.draw(rectangle);
                //rectangle.setFillColor(gray);
             //   rectangle.setFillColor(whiteColor[grid.getCase(x,y)->getWhite()]);
            }
            y ++;
        }
        

        window.display();
    }
    
	return 0;
}
