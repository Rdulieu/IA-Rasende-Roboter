#include "coordonnees.h"

//***Coordonnees Class***//
Coordonnees::Coordonnees(){
    x=0;
    y=0;
}

Coordonnees::Coordonnees(int px,int py){
    x=px;
    y=py;
}

void Coordonnees::setX(int px){
    x=px;
}

void Coordonnees::setY(int py){
    y=py;
}

int Coordonnees::getX(){
    return x;
}

int Coordonnees::getY(){
    return y;
}


//***Coordonnees mur ***//
/*
Coord_mur::Coord_mur(){
    orientation="NOT";
}

Coord_mur::Coord_mur(string porientation){
    orientation=porientation;
}

string Coord_mur::getOrientation(){
    return orientation;
}

void Coord_mur::setOrientation(string porientation){
    orientation=porientation;
}*/
