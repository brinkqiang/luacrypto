
#ifndef luamodule_h
#define luamodule_h

#define LUA_LIB

#include "lprefix.h"


#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
** This file uses only the official API of Lua.
** Any function declared here could be written as an application function.
*/

#include "lua.h"

#include "lauxlib.h"

#if defined(LUA_COMPAT_5_1) /* { */

/* Incompatibilities from 5.2 -> 5.3 */
#define LUA_COMPAT_MATHLIB
#define LUA_COMPAT_APIINTCASTS

/*
@@ LUA_COMPAT_UNPACK controls the presence of global 'unpack'.
** You can replace it with 'table.unpack'.
*/
#define LUA_COMPAT_UNPACK

/*
@@ LUA_COMPAT_LOADERS controls the presence of table 'package.loaders'.
** You can replace it with 'package.searchers'.
*/
#define LUA_COMPAT_LOADERS

/*
@@ macro 'lua_cpcall' emulates deprecated function lua_cpcall.
** You can call your C function directly (with light C functions).
*/
#define lua_cpcall(L,f,u)  \
    (lua_pushcfunction(L, (f)), \
     lua_pushlightuserdata(L,(u)), \
     lua_pcall(L,1,0,0))


/*
@@ LUA_COMPAT_LOG10 defines the function 'log10' in the math library.
** You can rewrite 'log10(x)' as 'log(x, 10)'.
*/
#define LUA_COMPAT_LOG10

/*
@@ LUA_COMPAT_LOADSTRING defines the function 'loadstring' in the base
** library. You can rewrite 'loadstring(s)' as 'load(s)'.
*/
#define LUA_COMPAT_LOADSTRING

/*
@@ LUA_COMPAT_MAXN defines the function 'maxn' in the table library.
*/
#define LUA_COMPAT_MAXN

/*
@@ The following macros supply trivial compatibility for some
** changes in the API. The macros themselves document how to
** change your code to avoid using them.
*/
#define lua_strlen(L,i)     lua_rawlen(L, (i))

#define lua_objlen(L,i)     lua_rawlen(L, (i))

#define lua_equal(L,idx1,idx2)      lua_compare(L,(idx1),(idx2),LUA_OPEQ)
#define lua_lessthan(L,idx1,idx2)   lua_compare(L,(idx1),(idx2),LUA_OPLT)

/*
@@ LUA_COMPAT_MODULE controls compatibility with previous
** module functions 'module' (Lua) and 'luaL_register' (C).
*/
#define LUA_COMPAT_MODULE

#endif              /* } */


/*
** {======================================================
** Compatibility with 5.1 module functions
** =======================================================
*/
#if defined(LUA_COMPAT_MODULE)

LUALIB_API const char* luaL_findtable( lua_State* L, int idx, const char* fname, int szhint );
LUALIB_API int libsize( const luaL_Reg* l );
LUALIB_API void luaL_pushmodule( lua_State* L, const char* modname,
                                 int sizehint );
LUALIB_API void luaL_openlib( lua_State* L, const char* libname,
                              const luaL_Reg* l, int nup );

#endif

#endif
