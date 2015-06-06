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
    Noeud *n = new Noeud();
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
