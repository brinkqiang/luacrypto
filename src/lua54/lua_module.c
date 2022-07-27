
#include "lua_module.h"

#if defined(LUA_COMPAT_MODULE)

const char* luaL_findtable( lua_State* L, int idx,
                                   const char* fname, int szhint ) {
    const char* e;

    if ( idx ) {
        lua_pushvalue( L, idx );
    }

    do {
        e = strchr( fname, '.' );

        if ( e == NULL ) {
            e = fname + strlen( fname );
        }

        lua_pushlstring( L, fname, e - fname );

        if ( lua_rawget( L, -2 ) == LUA_TNIL ) { /* no such field? */
            lua_pop( L, 1 ); /* remove this nil */
            lua_createtable( L, 0, ( *e == '.' ? 1 : szhint ) ); /* new table for field */
            lua_pushlstring( L, fname, e - fname );
            lua_pushvalue( L, -2 );
            lua_settable( L, -4 ); /* set new table into field */
        }
        else if ( !lua_istable( L, -1 ) ) {   /* field has a non-table value? */
            lua_pop( L, 2 ); /* remove table and value */
            return fname;  /* return problematic part of the name */
        }

        lua_remove( L, -2 ); /* remove previous table */
        fname = e + 1;
    }
    while ( *e == '.' );

    return NULL;
}


/*
** Count number of elements in a luaL_Reg list.
*/
int libsize( const luaL_Reg* l ) {
    int size = 0;

    for ( ; l && l->name; l++ ) {
        size++;
    }

    return size;
}


/*
** Find or create a module table with a given name. The function
** first looks at the LOADED table and, if that fails, try a
** global variable with that name. In any case, leaves on the stack
** the module table.
*/
void luaL_pushmodule( lua_State* L, const char* modname,
                                 int sizehint ) {
    luaL_findtable( L, LUA_REGISTRYINDEX, LUA_LOADED_TABLE, 1 );

    if ( lua_getfield( L, -1, modname ) != LUA_TTABLE ) { /* no LOADED[modname]? */
        lua_pop( L, 1 ); /* remove previous result */
        /* try global variable (and create one if it does not exist) */
        lua_pushglobaltable( L );

        if ( luaL_findtable( L, 0, modname, sizehint ) != NULL ) {
            luaL_error( L, "name conflict for module '%s'", modname );
        }

        lua_pushvalue( L, -1 );
        lua_setfield( L, -3, modname ); /* LOADED[modname] = new table */
    }

    lua_remove( L, -2 ); /* remove LOADED table */
}

 void luaL_openlib( lua_State* L, const char* libname,
                              const luaL_Reg* l, int nup ) {
    luaL_checkversion( L );

    if ( libname ) {
        luaL_pushmodule( L, libname, libsize( l ) ); /* get/create library table */
        lua_insert( L, -( nup + 1 ) ); /* move library table to below upvalues */
    }

    if ( l ) {
        luaL_setfuncs( L, l, nup );
    }
    else {
        lua_pop( L, nup );    /* remove upvalues */
    }
}

#endif

