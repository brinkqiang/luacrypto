
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "luacrypto_module.h"
#include "sol.hpp"
#include "dmrc.hpp"
#include "dmdes.h"
LUAMOD_API int luaopen_luacrypto(lua_State* L)
{
    luaL_Reg l[] = { 0 };

    sol::state_view lua(L);
    lua.new_usertype<CDMRC>("rc4",
        sol::constructors<CDMRC()>(),
        "SetKey", &CDMRC::SetKey,
        "Encrypt", sol::overload(sol::resolve<std::string(std::string&)>(&CDMRC::Encrypt), sol::resolve< char* (char* pBuf, size_t len)>(&CDMRC::Encrypt)),
        "Decrypt", sol::overload(sol::resolve<std::string(std::string&)>(&CDMRC::Decrypt), sol::resolve< char* (char* pBuf, size_t len)>(&CDMRC::Decrypt))
        );

    luaL_newlib(L, l);

    return 1;
}

LUAMOD_API int require_luacrypto(lua_State* L)
{
    luaL_requiref(L, "luacrypto", luaopen_luacrypto, 0);
    printf("lua module: require luacrypto\n");
    return 1;
}