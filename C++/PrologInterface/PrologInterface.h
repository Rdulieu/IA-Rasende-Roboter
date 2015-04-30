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


#ifndef PrologInterface_h
#define PrologInterface_h


#include <SWI-Prolog.h>

#include "Types.h"

//#include "IO/Plugin.h"

#ifndef Plugin_h
  #include <QLibrary>
#endif


#include <vector>


#ifdef Plugin_h
class PrologInterface : private Plugin<int>
#else
class PrologInterface
#endif
{
    public:
		PrologInterface();
        ~PrologInterface();

#ifdef Plugin_h
        void setParent( AbstractPlugin* parent );
#endif

        bool init( const char* program_name );
        void free();

        bool start( const char* predicate, uint32 nbr_params );
        bool call();
        void finish();

        void putList( term_t & l, int32 n, int32* tab );
        bool getList( term_t l, std::vector<int32> & tab );

        void putList( term_t & l, int32 n, float64* tab );
        bool getList( term_t l, std::vector<float64> & tab );

		void cleanList( term_t & l );
		void consList( term_t & l, term_t e );

        typedef bool (__cdecl* lpFunc1) ( int n, char** m );
        lpFunc1 funcInit;

        typedef int (__cdecl* lpFunc2) ( int status );
        lpFunc2 funcCleanup;

        typedef term_t (__cdecl* lpFunc3) ();
        lpFunc3 funcNewTermRef;

        typedef term_t (__cdecl* lpFunc4) ( term_t );
        lpFunc4 funcCopyTermRef;

        typedef bool (__cdecl* lpFunc5) ( term_t );
        lpFunc5 funcGetNil;

        typedef void (__cdecl* lpFunc6) ( term_t );
        lpFunc6 funcPutNil;

        typedef int (__cdecl* lpFunc7) ( term_t, int* );
        lpFunc7 funcGetInteger;

        typedef void (__cdecl* lpFunc8) ( term_t, int );
        lpFunc8 funcPutInteger;

        typedef int (__cdecl* lpFuncGetFloat) ( term_t, float64* );
        lpFuncGetFloat funcGetFloat;

        typedef void (__cdecl* lpFuncPutFloat) ( term_t, float64 );
        lpFuncPutFloat funcPutFloat;

        typedef void (__cdecl* lpFunc9) ( term_t, term_t, term_t );
        lpFunc9 funcConsList;

        typedef bool (__cdecl* lpFunc10) ( term_t, term_t, term_t );
        lpFunc10 funcGetList;

        typedef int (__cdecl* lpFunc16) ( term_t, char**, unsigned int );
        lpFunc16 funcGetListChars;

    protected:
        typedef predicate_t (__cdecl* lpFunc13) ( const char*, int, const char* );
        lpFunc13 funcPredicate;

        typedef fid_t (__cdecl* lpFunc11) ();
        lpFunc11 funcOpenForeignFrame;

        typedef void (__cdecl* lpFunc12) ( fid_t );
        lpFunc12 funcDiscardForeignFrame;

        typedef term_t (__cdecl* lpFunc14) ( int );
        lpFunc14 funcNewTermRefs;

        typedef int (__cdecl* lpFunc15) ( module_t, int, predicate_t, term_t );
        lpFunc15 funcCallPredicate;

    protected:
        bool onLoadingLibrary( const char* );


    public:
        predicate_t Predicate;
        term_t FirstTerm;

    protected:
#ifndef Plugin_h
        QLibrary m_Library;
#endif
        bool m_Initialized;

        fid_t m_Fid;
};


#endif
