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
#include "bd.h"
#include "global_base.h"

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
    //Bd::m_instance(this->m_CurrentStimulus);
    int start_x,start_y,target_x,target_y;
    //on cree la base de donne unique
    cout << "Debut de selectResponse" << endl;
    GlobalBase& g_uniqueBase=GlobalBase::Instance();
    cout << "etape 1 de selectResponse" << endl;
    g_uniqueBase.setBd(new Bd(this->m_CurrentStimulus));
    cout << "etape 2 de selectResponse" << endl;
    //trouvons quelle est le robot qui doit bouger en premier via la cible
    start_x=g_uniqueBase.getBd()->getRobot_Target_Coord().getX();
    start_y=g_uniqueBase.getBd()->getRobot_Target_Coord().getY();
    cout << "etape 3 de selectResponse" << endl;
  /*  int TargetID = m_CurrentStimulus[4];  Déjà fait dans la base de donnée.... il manquait juste les getters
    if(TargetID>=0 &&TargetID <5)
    {
        //c'est le robot bleu ou la spirale (on ignore la spirale pour le moment) qui est designé
        start_x = (int)m_CurrentStimulus[5];
        start_y = (int)m_CurrentStimulus[6];
    }
    else if(TargetID>=5 &&TargetID <9)
    {
        //robot vert
        start_x = (int)m_CurrentStimulus[7];
        start_y = (int)m_CurrentStimulus[8];
    }
    else if(TargetID>=9 &&TargetID <13)
    {
        //jaune
        start_x = (int)m_CurrentStimulus[9];
        start_y = (int)m_CurrentStimulus[10];
    }
    else if(TargetID>=13 &&TargetID <17)
    {
        //rouge
        start_x = (int)m_CurrentStimulus[11];
        start_y = (int)m_CurrentStimulus[12];
    }*/
    //generons le graphe
    std::vector<P> discover;
    cout << "etape 4 de selectResponse start_x:" << start_x << " y:" << start_y << endl;
    Noeud *n = new Noeud(0,start_x,start_y,discover); //unused -> bug ici


 /*   //on trouve les coordonné du but grace à la base de dudul (déjà fait ça aussi)
    target_x = g_uniqueBase.getBd()->getlist_target(TargetID).getX(); //sublime comme appel
    target_y = g_uniqueBase.getBd()->getlist_target(TargetID).getY(); */

    //cherchons une solution au but et retournons là
    cout << "etape 5 de selectResponse" << endl;
    cout << "=================================================Projet IA41 : Astar" << endl;
    return n->astar(target_x,target_y);

    /*
    m_NextResponse.setDimension( 4 );
    m_NextResponse[0] = 1;

    m_NextResponse[1] = 2;

    m_NextResponse[2] = 1;

    m_NextResponse[3] = 1;



    return m_NextResponse;*/
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



