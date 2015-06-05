/*
 * $Id$
 *
 * Ipseity is an open-source platform dedicated to the development and
 * validation of Artificial Intelligence techniques in Multiagent Systems.
 * It is developed in C++ with the Qt framework (http://qt-project.org).
 * More details on <http://www.ipseity-project.com>
 * Copyright (C) 2015, 2014, 2013 Ipseity Core Developers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "IpseityTalker.h"


#include "Math/RandomNumberGenerator.h"


#include <ostream>
#include <QDebug>


//const int32 SHIFT = 1;
//const int32 NBR_DECISIONS = 12;


IpseityTalker::IpseityTalker()
{
    //RandomNumberGenerator::initSeed( 0 );
    cout << "=================================================Projet IA41 Constructed" << endl;
    //m_NextResponse.setDimension( 1 );

}

IpseityTalker::~IpseityTalker()
{
}


const char*
IpseityTalker::getBaseName() const
{
    return "IpseityTalker";
}


const char*
IpseityTalker::getDescription() const
{
    return "";
}


const char*
IpseityTalker::getAuthors() const
{
    return "Name1, Name2";
}


void
IpseityTalker::defineParameters()
{
}


bool
IpseityTalker::attachView( uint32 view_id, QWidget* widget )
{
    return true;
}


//*****************************************************************************


bool
IpseityTalker::init( const char* base_path, const char* file_name, const Taxon & taxon, AbstractInputManager*  )
{
    return true;
}


void
IpseityTalker::setMode( bool learning_mode )
{
}


bool
IpseityTalker::canReset() const
{
    return true;
}


void
IpseityTalker::reset()
{
}


void
IpseityTalker::startNewSimulation()
{
}

void
IpseityTalker::endSimulation()
{
}


void
IpseityTalker::startNewEpisode( uint64 scenario_uid )
{
}

void
IpseityTalker::endEpisode( bool is_success, uint32 nbr_decisions )
{
}


void
IpseityTalker::observe( const Sensation & x )
{
    m_CurrentStimulus = x;
    cout << "=================================================Projet IA41 Recuperation Sensation" << endl;
    cout << m_CurrentStimulus << endl;
}


const Response &
IpseityTalker::selectResponse()
{
    int robot_target;
    int target=m_CurrentStimulus[4];
    Coordonnees robot_target_coord;
    Coordonnees target_coord;
    Coordonnees list_target[17];

    robot_target=floor((target-1)/4);     // prolog : move([_,_,_,_,TargetId|_],[Robot,1]):-Robot is floor((TargetId-1)/4).
    cout << robot_target << endl;
    switch(robot_target){
        case 0:
            robot_target_coord=Coordonnees(m_CurrentStimulus[5],m_CurrentStimulus[6]);
        break;
        case 1:
            robot_target_coord=Coordonnees(m_CurrentStimulus[7],m_CurrentStimulus[8]);
        break;
        case 2:
            robot_target_coord=Coordonnees(m_CurrentStimulus[9],m_CurrentStimulus[10]);
        break;
        case 3:
            robot_target_coord=Coordonnees(m_CurrentStimulus[11],m_CurrentStimulus[12]);
        break;
    default:
            robot_target_coord=Coordonnees(m_CurrentStimulus[0],m_CurrentStimulus[0]);
    }




    /* Base de connaissances
     où sont placés les murs et les target ?
     Target [Scenario,liste des targets (dans l'ordre)]*/

    if(m_CurrentStimulus[0]){
        list_target[0]=Coordonnees(3,7);
        list_target[1]=Coordonnees(5,6);
        list_target[6]=Coordonnees(1,3);
        list_target[12]=Coordonnees(6,4);
        list_target[15]=Coordonnees(2,1);
    }else{
        list_target[0]=Coordonnees(7,5);
        list_target[1]=Coordonnees(6,1);
        list_target[6]=Coordonnees(5,4);
        list_target[12]=Coordonnees(1,3);
        list_target[15]=Coordonnees(2,5);
    }
    if(m_CurrentStimulus[1]){
        list_target[3]=Coordonnees(11,2);
        list_target[5]=Coordonnees(13,6);
        list_target[10]=Coordonnees(10,7);
        list_target[16]=Coordonnees(14,1);
    }else{
        list_target[3]=Coordonnees(13,5);
        list_target[5]=Coordonnees(11,2);
        list_target[10]=Coordonnees(9,1);
        list_target[16]=Coordonnees(10,7);
    }
    if(m_CurrentStimulus[2]){
        list_target[4]=Coordonnees(3,9);
        list_target[7]=Coordonnees(6,14);
        list_target[9]=Coordonnees(1,13);
        list_target[14]=Coordonnees(5,11);
    }else{
        list_target[4]=Coordonnees(6,13);
        list_target[7]=Coordonnees(1,10);
        list_target[9]=Coordonnees(4,9);
        list_target[14]=Coordonnees(2,14);
    }
    if(m_CurrentStimulus[3]){
        list_target[2]=Coordonnees(12,9);
        list_target[11]=Coordonnees(9,12);
        list_target[13]=Coordonnees(11,14);
    }else{
        list_target[2]=Coordonnees(9,10);
        list_target[11]=Coordonnees(9,14);
        list_target[13]=Coordonnees(12,9);
    }
    list_target[8]=Coordonnees(14,13);
    target_coord=list_target[target];

/*
    target([0,0,0,0],[[7,5],[6,1],[9,10],[13,5],[6,13],[11,2],[5,4],[1,10],[14,13],[4,9],[9,1],[9,14],[1,3],[12,9],[2,14],[2,5],[10,7]]).
    target([0,0,0,1],[[7,5],[6,1],[12,9],[13,5],[6,13],[11,2],[5,4],[1,10],[14,13],[4,9],[9,1],[9,12],[1,3],[11,14],[2,14],[2,5],[10,7]]).
    target([0,0,1,0],[[7,5],[6,1],[9,10],[13,5],[3,9],[11,2],[5,4],[6,14],[14,13],[1,13],[9,1],[9,14],[1,3],[12,9],[5,11],[2,5],[10,7]]).
    target([0,0,1,1],[[7,5],[6,1],[12,9],[13,5],[3,9],[11,2],[5,4],[6,14],[14,13],[1,13],[9,1],[9,12],[1,3],[11,14],[5,11],[2,5],[10,7]]).
    target([0,1,0,0],[[7,5],[6,1],[9,10],[11,2],[6,13],[13,6],[5,4],[1,10],[14,13],[4,9],[10,7],[9,14],[1,3],[12,9],[2,14],[2,5],[14,1]]).
    target([0,1,0,1],[[7,5],[6,1],[12,9],[11,2],[6,13],[13,6],[5,4],[1,10],[14,13],[4,9],[10,7],[9,12],[1,3],[11,14],[2,14],[2,5],[14,1]]).
    target([0,1,1,0],[[7,5],[6,1],[9,10],[11,2],[3,9],[13,6],[5,4],[6,14],[14,13],[1,13],[10,7],[9,14],[1,3],[12,9],[5,11],[2,5],[14,1]]).
    target([0,1,1,1],[[7,5],[6,1],[12,9],[11,2],[3,9],[13,6],[5,4],[6,14],[14,13],[1,13],[10,7],[9,12],[1,3],[11,14],[5,11],[2,5],[14,1]]).
    target([1,0,0,0],[[3,7],[5,6],[9,10],[13,5],[6,13],[11,2],[1,3],[1,10],[14,13],[4,9],[9,1],[9,14],[6,4],[12,9],[2,14],[2,1],[10,7]]).
    target([1,0,0,1],[[3,7],[5,6],[12,9],[13,5],[6,13],[11,2],[1,3],[1,10],[14,13],[4,9],[9,1],[9,12],[6,4],[11,14],[2,14],[2,1],[10,7]]).
    target([1,0,1,0],[[3,7],[5,6],[9,10],[13,5],[3,9],[11,2],[1,3],[6,14],[14,13],[1,13],[9,1],[9,14],[6,4],[12,9],[5,11],[2,1],[10,7]]).
    target([1,0,1,1],[[3,7],[5,6],[12,9],[13,5],[3,9],[11,2],[1,3],[6,14],[14,13],[1,13],[9,1],[9,12],[6,4],[11,14],[5,11],[2,1],[10,7]]).
    target([1,1,0,0],[[3,7],[5,6],[9,10],[11,2],[6,13],[13,6],[1,3],[1,10],[14,13],[4,9],[10,7],[9,14],[6,4],[12,9],[2,14],[2,1],[14,1]]).
    target([1,1,0,1],[[3,7],[5,6],[12,9],[11,2],[6,13],[13,6],[1,3],[1,10],[14,13],[4,9],[10,7],[9,12],[6,4],[11,14],[2,14],[2,1],[14,1]]).
    target([1,1,1,0],[[3,7],[5,6],[9,10],[11,2],[3,9],[13,6],[1,3],[6,14],[14,13],[1,13],[10,7],[9,14],[6,4],[12,9],[5,11],[2,1],[14,1]]).
    target([1,1,1,1],[[3,7],[5,6],[12,9],[11,2],[3,9],[13,6],[1,3],[6,14],[14,13],[1,13],[10,7],[9,12],[6,4],[11,14],[5,11],[2,1],[14,1]]).




    // murhaut [Scenario,liste des murs]
    murdroite([0,0,0,0], [[3,0],[10,0],[9,1],[5,1],[11,2],[1,3],[2,5],[4,4],[7,5],[12,5],[12,9],[9,7],[6,7],[6,8],[8,7],[8,8],[8,10],[3,9],[1,10],[2,14],[3,15],[5,13],[8,14],[10,15],[14,13]]).
    murdroite([0,0,0,1], [[3,0],[5,1],[9,1],[10,0],[11,2],[1,3],[4,4],[12,5],[7,5],[2,5],[6,7],[6,8],[8,7],[8,8],[9,7],[12,9],[3,9],[1,10],[5,13],[2,14],[3,15],[8,12],[11,14],[13,13],[13,15]]).
    murdroite([0,0,1,0], [[3,0],[5,1],[9,1],[10,0],[11,2],[1,3],[4,4],[2,5],[12,5],[9,7],[8,7],[8,8],[6,7],[6,8],[3,9],[4,11],[0,13],[4,15],[6,14],[8,14],[10,15],[8,10],[12,9],[14,13],[7,5]]).
    murdroite([0,0,1,1], [[3,0],[10,0],[9,1],[5,1],[1,3],[4,4],[2,5],[7,5],[11,2],[12,5],[9,7],[8,7],[8,8],[6,7],[6,8],[12,9],[3,9],[4,11],[0,13],[4,15],[6,14],[8,12],[13,13],[13,15],[11,14]]).
    murdroite([0,1,0,0], [[3,0],[9,0],[13,1],[10,2],[5,1],[1,3],[4,4],[2,5],[7,5],[10,7],[13,6],[8,7],[8,8],[6,7],[6,8],[3,9],[1,10],[2,14],[3,15],[5,13],[8,14],[10,15],[8,10],[14,13],[12,9]]).
    murdroite([0,1,0,1], [[3,0],[9,0],[13,1],[10,2],[5,1],[1,3],[4,4],[2,5],[7,5],[6,7],[6,8],[8,7],[8,8],[10,7],[13,6],[12,9],[13,13],[13,15],[11,14],[8,12],[5,13],[3,15],[2,14],[1,10],[3,9]]).
    murdroite([0,1,1,0], [[3,0],[5,1],[9,0],[10,2],[13,1],[1,3],[2,5],[4,4],[7,5],[6,7],[6,8],[8,7],[8,8],[10,7],[13,6],[12,9],[8,10],[3,9],[4,11],[0,13],[6,14],[8,14],[14,13],[4,15],[10,15]]).
    murdroite([0,1,1,1], [[3,0],[5,1],[9,0],[10,2],[13,1],[13,6],[10,7],[12,9],[8,7],[8,8],[6,7],[6,8],[7,5],[4,4],[1,3],[2,5],[3,9],[4,11],[0,13],[6,14],[8,12],[11,14],[13,13],[13,15],[4,15]]).
    murdroite([1,0,0,0], [[4,0],[10,0],[11,2],[12,5],[5,4],[2,1],[0,3],[6,7],[6,8],[5,6],[8,7],[8,8],[3,7],[3,9],[1,10],[2,14],[3,15],[5,13],[10,15],[8,14],[14,13],[12,9],[8,10],[9,7],[9,1]]).
    murdroite([1,0,0,1], [[4,0],[2,1],[0,3],[5,4],[5,6],[3,7],[3,9],[1,10],[2,14],[3,15],[5,13],[8,12],[6,8],[6,7],[8,7],[8,8],[9,7],[9,1],[10,0],[11,2],[12,5],[12,9],[13,13],[13,15],[11,14]]).
    murdroite([1,0,1,0], [[4,0],[10,0],[9,1],[11,2],[12,5],[5,4],[2,1],[0,3],[3,7],[5,6],[6,7],[6,8],[8,7],[8,8],[9,7],[12,9],[8,10],[4,11],[3,9],[0,13],[4,15],[6,14],[8,14],[10,15],[14,13]]).
    murdroite([1,0,1,1], [[4,0],[10,0],[9,1],[11,2],[12,5],[5,4],[5,6],[0,3],[3,7],[3,9],[0,13],[4,11],[6,14],[8,12],[13,13],[13,15],[11,14],[12,9],[9,7],[8,7],[8,8],[6,7],[6,8],[4,15],[2,1]]).
    murdroite([1,1,0,0], [[4,0],[9,0],[10,2],[13,1],[13,6],[10,7],[8,7],[8,8],[6,7],[6,8],[5,6],[5,4],[0,3],[3,7],[3,9],[1,10],[2,14],[3,15],[5,13],[8,14],[10,15],[14,13],[12,9],[8,10],[2,1]]).
    murdroite([1,1,0,1], [[4,0],[9,0],[10,2],[13,1],[13,6],[10,7],[5,4],[0,3],[5,6],[3,7],[3,9],[1,10],[2,14],[3,15],[5,13],[8,12],[11,14],[13,15],[13,13],[12,9],[6,7],[6,8],[8,7],[8,8],[2,1]]).
    murdroite([1,1,1,0], [[4,0],[2,1],[0,3],[5,4],[5,6],[3,7],[3,9],[0,13],[4,15],[6,14],[4,11],[8,10],[8,14],[10,15],[14,13],[12,9],[10,7],[13,6],[13,1],[10,2],[9,0],[6,7],[6,8],[8,7],[8,8]]).
    murdroite([1,1,1,1], [[2,1],[4,0],[0,3],[5,4],[5,6],[9,0],[10,2],[13,1],[13,6],[10,7],[12,9],[13,13],[13,15],[11,14],[8,12],[6,14],[4,15],[4,11],[3,9],[0,13],[3,7],[6,7],[6,8],[8,7],[8,8]]).


    // murdroite [Scenario,liste des murs]
    murhaut([0,0,0,0], [[0,3],[0,6],[1,2],[6,1],[9,0],[11,2],[15,3],[13,5],[15,9],[10,6],[12,8],[7,5],[5,3],[2,5],[4,9],[9,10],[14,13],[9,13],[6,12],[2,14],[1,9],[7,6],[8,6],[7,8],[8,8]]).
    murhaut([0,0,0,1], [[9,0],[15,1],[6,1],[11,2],[15,3],[5,3],[0,3],[1,2],[2,5],[7,5],[13,5],[10,6],[8,6],[7,6],[0,6],[7,8],[8,8],[12,8],[4,9],[1,9],[2,14],[6,12],[9,11],[11,14],[14,13]]).
    murhaut([0,0,1,0], [[6,1],[9,0],[11,2],[15,3],[13,5],[7,5],[5,3],[1,2],[0,2],[2,5],[0,6],[7,6],[8,6],[7,8],[8,8],[9,10],[15,9],[12,8],[10,6],[14,13],[9,13],[6,13],[5,10],[3,9],[1,13]]).
    murhaut([0,0,1,1], [[6,1],[9,0],[11,2],[15,1],[15,3],[5,3],[1,2],[0,2],[0,6],[2,5],[7,5],[13,5],[10,6],[8,6],[7,6],[7,8],[8,8],[12,8],[9,11],[5,10],[3,9],[14,13],[11,14],[6,13],[1,13]]).
    murhaut([0,1,0,0], [[6,1],[11,2],[14,0],[15,3],[7,5],[5,3],[1,2],[0,3],[0,6],[2,5],[4,9],[1,9],[7,6],[8,6],[7,8],[8,8],[10,6],[12,8],[15,9],[13,6],[14,13],[9,10],[9,13],[6,12],[2,14]]).
    murhaut([0,1,0,1], [[6,1],[14,0],[15,1],[15,3],[11,2],[13,6],[10,6],[8,6],[7,6],[7,8],[8,8],[7,5],[5,3],[2,5],[1,2],[0,3],[0,6],[4,9],[1,9],[2,14],[6,12],[9,11],[11,14],[14,13],[12,8]]).
    murhaut([0,1,1,0], [[0,2],[1,2],[6,1],[11,2],[14,0],[15,3],[10,6],[13,6],[7,5],[5,3],[2,5],[0,6],[7,6],[8,6],[7,8],[8,8],[9,10],[3,9],[5,10],[1,13],[6,13],[9,13],[15,9],[12,8],[14,13]]).
    murhaut([0,1,1,1], [[0,2],[1,2],[6,1],[5,3],[11,2],[15,1],[15,3],[14,0],[13,6],[10,6],[8,6],[7,6],[7,5],[7,8],[8,8],[12,8],[14,13],[11,14],[9,11],[5,10],[6,13],[1,13],[3,9],[0,6],[2,5]]).
    murhaut([1,0,0,0], [[0,3],[1,3],[0,4],[2,1],[6,3],[9,0],[11,2],[15,3],[13,5],[12,8],[15,9],[10,6],[8,6],[7,6],[7,8],[8,8],[9,10],[4,9],[5,5],[3,7],[1,9],[2,14],[6,12],[9,13],[14,13]]).
    murhaut([1,0,0,1], [[2,1],[0,3],[1,3],[0,4],[6,3],[9,0],[15,1],[15,3],[11,2],[13,5],[10,6],[12,8],[7,6],[8,6],[7,8],[8,8],[5,5],[4,9],[3,7],[1,9],[2,14],[6,12],[9,11],[14,13],[11,14]]).
    murhaut([1,0,1,0], [[0,2],[1,3],[2,1],[6,3],[9,0],[11,2],[15,3],[13,5],[15,9],[12,8],[10,6],[8,6],[7,6],[7,8],[8,8],[5,5],[0,4],[3,7],[3,9],[5,10],[1,13],[6,13],[9,13],[9,10],[14,13]]).
    murhaut([1,0,1,1], [[2,1],[0,2],[1,3],[0,4],[6,3],[5,5],[3,7],[3,9],[1,13],[5,10],[6,13],[9,11],[11,14],[14,13],[12,8],[10,6],[13,5],[15,3],[15,1],[11,2],[9,0],[8,6],[7,6],[7,8],[8,8]]).
    murhaut([1,1,0,0], [[2,1],[0,3],[1,3],[0,4],[6,3],[5,5],[7,6],[8,6],[7,8],[8,8],[10,6],[13,6],[15,3],[14,0],[11,2],[15,9],[12,8],[9,10],[14,13],[9,13],[6,12],[4,9],[2,14],[1,9],[3,7]]).
    murhaut([1,1,0,1], [[0,3],[1,3],[0,4],[2,1],[6,3],[11,2],[15,1],[15,3],[14,0],[13,6],[10,6],[12,8],[14,13],[11,14],[9,11],[6,12],[4,9],[1,9],[2,14],[3,7],[5,5],[7,6],[8,6],[7,8],[8,8]]).
    murhaut([1,1,1,0], [[7,8],[8,8],[7,6],[8,6],[2,1],[0,2],[1,3],[0,4],[6,3],[11,2],[14,0],[15,3],[15,9],[12,8],[13,6],[10,6],[14,13],[9,13],[9,10],[6,13],[5,10],[1,13],[3,7],[3,9],[5,5]]).
    murhaut([1,1,1,1], [[0,2],[1,3],[2,1],[6,3],[0,4],[3,7],[5,5],[3,9],[5,10],[1,13],[6,13],[9,11],[11,14],[14,13],[12,8],[10,6],[13,6],[15,3],[15,1],[14,0],[11,2],[7,6],[8,6],[7,8],[8,8]]).



     move([TL,TR,BL,BR, TargetId, BlueRobotPosition, GreenRobotPosition,
YellowRobotPosition, RedRobotPosition ],ActionId):-
%	Calculer l'ID du robot qui doit atteindre la cible.
            Robot is floor((TargetId-1)/4), robotC(Robot,CoordR, BlueRobotPosition, GreenRobotPosition,
YellowRobotPosition, RedRobotPosition),
%	Calculer les coordonnées de la target -> CoordT
            target([TL,TR,BL,BR],L),nth0(TargetId,L,CoordT),*/


    m_NextResponse.setDimension( 4 );
    m_NextResponse[0] = 1;

    m_NextResponse[1] = 2;

    m_NextResponse[2] = 2;

    m_NextResponse[3] = 2;

    cout << "=================================================Projet IA41 Retour de la reponse" << endl;
    return m_NextResponse;
}


void
IpseityTalker::suggestResponse( const Response & response )
{
}


void
IpseityTalker::loadMemory()
{
}

void
IpseityTalker::saveMemory()
{
}


void
IpseityTalker::loadStats()
{
}

void
IpseityTalker::saveStats()
{
}


//*****************************************************************************

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
