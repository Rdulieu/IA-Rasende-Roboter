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


#ifndef Types_h
#define Types_h


#include <stdio.h>      // for NULL pointer


#ifdef QT
#define DllCallConv
#else
#define DllCallConv __cdecl
#endif


typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef float float32;
typedef double float64;
typedef long double float80;


#define INT8_MIN_VALUE		-128
#define INT8_MAX_VALUE		127
#define UINT8_MAX_VALUE		0xFF

#define INT16_MIN_VALUE		-32768
#define INT16_MAX_VALUE		32767
#define UINT16_MAX_VALUE	0xFFFF

#define INT32_MIN_VALUE		-2147483648
#define INT32_MAX_VALUE		2147483647
#define UINT32_MAX_VALUE	0xFFFFFFFF

#define FLOAT32_MIN_VALUE 	-3.4e+38f
#define FLOAT32_MAX_VALUE 	3.4e+38f

#define FLOAT64_MIN_VALUE 	-1.7e+308
#define FLOAT64_MAX_VALUE 	1.7e+308


// Bit functions

#define SetBit( var, flag, val ) \
    var &= (0xFF ^ (val)); \
    if (flag) \
    { \
        var |= (val); \
    }


#endif
