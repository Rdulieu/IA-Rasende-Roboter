/*
 * $Id$
 *
 * Ipseity is a rich-client platform developed in C++ with the Qt
 * framework (http://qt-project.org).
 * More details on <http://www.ipseity-project.com>
 * Copyright (C) 2013 Ipseity Core Developers
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
 */


/*#########################################################################

    LIBRARY : PrologInterface

    Interface between SWI-Prolog and C++

    ---------------------------------------------------------------------

    Author(s) : Fabrice LAURI
    Creation Date : 2008/10/24
    Last Update : 2013/06/11

#########################################################################*/


#include "PrologInterface.h"


#include <stdio.h>
#include <iostream>


const char* g_PrologLibraryName = "libpl";


PrologInterface::PrologInterface()
{
    m_Initialized = false;
}


PrologInterface::~PrologInterface()
{
    if (m_Initialized)
    {
        (funcCleanup)( 1 );
    }

    free();
}


#ifdef Plugin_h
void
PrologInterface::setParent( AbstractPlugin* parent )
{
    m_Parent = parent;
}
#endif


bool
PrologInterface::init( const char* program_name )
{
#ifndef Plugin_h
    m_Library.setFileName( g_PrologLibraryName );
    m_Library.load();

    if (m_Library.isLoaded())
#else
    if (loadLibrary( g_PrologLibraryName ))
#endif
    {
        return onLoadingLibrary( program_name );
    }
    else
    {
        return false;
    }
}


void
PrologInterface::free()
{
#ifndef Plugin_h
    m_Library.unload();
#else
    freeLibrary();
#endif
}


bool
PrologInterface::start( const char* predicate, uint32 nbr_params )
{
    if (m_Initialized)
    {
        m_Fid = (funcOpenForeignFrame)();

        Predicate = funcPredicate( predicate, nbr_params, "user" );
        FirstTerm = funcNewTermRefs( nbr_params );

        return true;
    }
    else
    {
        return false;
    }
}

bool
PrologInterface::call()
{
    return (funcCallPredicate( NULL, PL_Q_NODEBUG, Predicate, FirstTerm ) > 0);
}

void
PrologInterface::finish()
{
    (funcDiscardForeignFrame)( m_Fid );
}


void
PrologInterface::putList( term_t & l, int32 n, int32* tab )
{
    term_t a = (funcNewTermRef)();

    (funcPutNil)( l );
    while( --n >= 0 )
    {
        (funcPutInteger)( a, tab[n] );
        (funcConsList)( l, a, l );
    }
}

void
PrologInterface::putList( term_t & l, int32 n, float64* tab )
{
    term_t a = (funcNewTermRef)();

    (funcPutNil)( l );
    while( --n >= 0 )
    {
        (funcPutFloat)( a, tab[n] );
        (funcConsList)( l, a, l );
    }
}


void
PrologInterface::cleanList( term_t & l )
{
    (funcPutNil)( l );
}

void
PrologInterface::consList( term_t & l, term_t e )
{
    (funcConsList)( l, e, l );
}


bool
PrologInterface::getList( term_t l, std::vector<int32> & tab )
{
    term_t head = (funcNewTermRef)();
    term_t list = (funcCopyTermRef)( l );

    int32 n;
    tab.clear();
    while( (funcGetList)(list, head, list) )
    {
        if ( (funcGetInteger)( head, &n ) )
        {
            tab.push_back( n );
        }
        else
        {
            return false;
        }
    }

    return ((funcGetNil)( list ) ? true : false);
}

bool
PrologInterface::getList( term_t l, std::vector<float64> & tab )
{
    term_t head = (funcNewTermRef)();
    term_t list = (funcCopyTermRef)( l );

    float64 n;
    tab.clear();
    while( (funcGetList)(list, head, list) )
    {
        if ( (funcGetFloat)( head, &n ) )
        {
            tab.push_back( n );
        }
        else
        {
            return false;
        }
    }

    return ((funcGetNil)( list ) ? true : false);
}


//******************************************************************************************


bool
PrologInterface::onLoadingLibrary( const char* name )
{
    funcInit = (lpFunc1) m_Library.resolve( "PL_initialise" );
    funcCleanup = (lpFunc2) m_Library.resolve( "PL_cleanup" );

    funcNewTermRef = (lpFunc3) m_Library.resolve( "PL_new_term_ref" );
    funcCopyTermRef = (lpFunc4) m_Library.resolve( "PL_copy_term_ref" );

    funcGetNil = (lpFunc5) m_Library.resolve( "PL_get_nil" );
    funcPutNil = (lpFunc6) m_Library.resolve( "PL_put_nil" );

    funcGetInteger = (lpFunc7) m_Library.resolve( "PL_get_integer" );
    funcPutInteger = (lpFunc8) m_Library.resolve( "PL_put_integer" );
    funcGetFloat = (lpFuncGetFloat) m_Library.resolve( "PL_get_float" );
    funcPutFloat = (lpFuncPutFloat) m_Library.resolve( "PL_put_float" );

    funcConsList = (lpFunc9) m_Library.resolve( "PL_cons_list" );

    funcGetList = (lpFunc10) m_Library.resolve( "PL_get_list" );

    funcOpenForeignFrame = (lpFunc11) m_Library.resolve( "PL_open_foreign_frame" );
    funcDiscardForeignFrame = (lpFunc12) m_Library.resolve( "PL_discard_foreign_frame" );

    funcPredicate = (lpFunc13) m_Library.resolve( "PL_predicate" );

    funcNewTermRefs = (lpFunc14) m_Library.resolve( "PL_new_term_refs" );

    funcCallPredicate = (lpFunc15) m_Library.resolve( "PL_call_predicate" );

    funcGetListChars = (lpFunc16) m_Library.resolve( "PL_get_list_chars" );

    char* module[4];

    module[0] = (char*) name;
    module[1] = NULL;

    if ((funcInit)( 1, module ))
    {
        m_Initialized = true;

        return true;
    }
    else
    {
        (funcCleanup)( 1 );

        return false;
    }
}
