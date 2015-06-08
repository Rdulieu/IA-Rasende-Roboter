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
#include "noeud.h"
#include "arc.h"
#include "coordonnees.h"


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
    Noeud *n = new Noeud(); //unused

    int robot_target;
    int target=m_CurrentStimulus[4];
    Coordonnees robot_target_coord;
    Coordonnees target_coord;
    Coordonnees list_target[17];
    bool list_murH[15][16];
    bool list_murV[16][15];

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

    /*
        Construction de la list_murV qui contient les Coordonnées de chaque mur
        en fonction de des 4 variables définissant le plateau. Ce sont bien les coordonnées des murs et non des cases*/
    for(int i=0;i<16;++i){
        for(int j=0;j<15;++j){
            list_murH[i][j]=list_murV[j][i]=false;
        }
    }


    /* Base de connaissances
        Construction de la list_target qui contient les Coordonnées de chaque cible
        en fonction de des 4 variables définissant le plateau*/


    //carré du centre
    list_murH[6][7]=true;
    list_murH[8][7]=true;
    list_murH[6][8]=true;
    list_murH[8][8]=true;
    list_murV[7][6]=true;
    list_murV[8][6]=true;
    list_murV[7][8]=true;
    list_murV[8][8]=true;

    if(m_CurrentStimulus[0]){
        list_target[0]=Coordonnees(3,7);
        list_target[1]=Coordonnees(5,6);
        list_target[6]=Coordonnees(1,3);
        list_target[12]=Coordonnees(6,4);
        list_target[15]=Coordonnees(2,1);

        list_murH[4][0]=true;
        list_murH[2][1]=true;
        list_murH[0][3]=true;
        list_murH[5][4]=true;
        list_murH[5][6]=true;
        list_murH[3][7]=true;

        list_murV[0][2]=true;
        list_murV[0][4]=true;
        list_murV[1][3]=true;
        list_murV[2][1]=true;
        list_murV[3][7]=true;
        list_murV[5][5]=true;
        list_murV[6][3]=true;
    }else{
        list_target[0]=Coordonnees(7,5);
        list_target[1]=Coordonnees(6,1);
        list_target[6]=Coordonnees(5,4);
        list_target[12]=Coordonnees(1,3);
        list_target[15]=Coordonnees(2,5);

        list_murH[3][0]=true;
        list_murH[5][1]=true;
        list_murH[1][3]=true;
        list_murH[4][4]=true;
        list_murH[7][5]=true;
        list_murH[2][5]=true;

         list_murV[0][3]=true;
         list_murV[0][6]=true;
         list_murV[1][2]=true;
         list_murV[2][5]=true;
         list_murV[5][3]=true;
         list_murV[6][1]=true;
         list_murV[7][5]=true;
    }
    if(m_CurrentStimulus[1]){
        list_target[3]=Coordonnees(11,2);
        list_target[5]=Coordonnees(13,6);
        list_target[10]=Coordonnees(10,7);
        list_target[16]=Coordonnees(14,1);

        list_murH[9][0]=true;
        list_murH[13][1]=true;
        list_murH[10][2]=true;
        list_murH[13][6]=true;
        list_murH[10][7]=true;

        list_murV[10][6]=true;
        list_murV[11][2]=true;
        list_murV[13][6]=true;
        list_murV[14][0]=true;
        list_murV[15][1]=true;
        list_murV[15][3]=true;
    }else{
        list_target[3]=Coordonnees(13,5);
        list_target[5]=Coordonnees(11,2);
        list_target[10]=Coordonnees(9,1);
        list_target[16]=Coordonnees(10,7);

        list_murH[10][0]=true;
        list_murH[9][1]=true;
        list_murH[11][2]=true;
        list_murH[12][5]=true;
        list_murH[9][7]=true;


        list_murV[1][9]=true;
        list_murV[2][14]=true;
        list_murV[4][9]=true;
        list_murV[6][12]=true;
    }
    if(m_CurrentStimulus[2]){
        list_target[4]=Coordonnees(3,9);
        list_target[7]=Coordonnees(6,14);
        list_target[9]=Coordonnees(1,13);
        list_target[14]=Coordonnees(5,11);

        list_murH[3][9]=true;
        list_murH[4][11]=true;
        list_murH[0][13]=true;
        list_murH[6][14]=true;
        list_murH[4][15]=true;

        list_murV[1][14]=true;
        list_murV[3][9]=true;
        list_murV[5][10]=true;
        list_murV[6][14]=true;
    }else{
        list_target[4]=Coordonnees(6,13);
        list_target[7]=Coordonnees(1,10);
        list_target[9]=Coordonnees(4,9);
        list_target[14]=Coordonnees(2,14);

        list_murH[3][9]=true;
        list_murH[1][10]=true;
        list_murH[5][13]=true;
        list_murH[2][14]=true;
        list_murH[3][15]=true;

        list_murV[9][0]=true;
        list_murV[10][6]=true;
        list_murV[11][2]=true;
        list_murV[13][5]=true;
        list_murV[15][3]=true;
    }
    if(m_CurrentStimulus[3]){
        list_target[2]=Coordonnees(12,9);
        list_target[11]=Coordonnees(9,12);
        list_target[13]=Coordonnees(11,14);

        list_murH[12][9]=true;
        list_murH[8][12]=true;
        list_murH[13][13]=true;
        list_murH[11][14]=true;
        list_murH[13][15]=true;

        list_murV[9][11]=true;
        list_murV[11][14]=true;
        list_murV[12][8]=true;
        list_murV[14][13]=true;
    }else{
        list_target[2]=Coordonnees(9,10);
        list_target[11]=Coordonnees(9,14);
        list_target[13]=Coordonnees(12,9);

        list_murH[12][9]=true;
        list_murH[8][10]=true;
        list_murH[14][13]=true;
        list_murH[8][14]=true;
        list_murH[10][15]=true;

        list_murV[9][10]=true;
        list_murV[9][13]=true;
        list_murV[12][8]=true;
        list_murV[14][13]=true;
        list_murV[15][9]=true;
    }
    list_target[8]=Coordonnees(14,13);
    target_coord=list_target[target];



    m_NextResponse.setDimension( 4 );
    m_NextResponse[0] = 1;

    m_NextResponse[1] = 2;

    m_NextResponse[2] = 1;

    m_NextResponse[3] = 1;


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



