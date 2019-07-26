
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
#include "dmmd5.h"
#include "dmcrc.h"
#include "dmbase64.h"

LUAMOD_API int luaopen_luacrypto(lua_State* L)
{
    luaL_Reg l[] = { 0 };

    sol::state_view lua(L);
    lua.new_usertype<CDMRC>("rc4",
        sol::constructors<CDMRC()>(),
        "SetKey", &CDMRC::SetKey,
        "Encode", sol::overload(sol::resolve<std::string(std::string&)>(&CDMRC::Encrypt), sol::resolve< char* (char* pBuf, size_t len)>(&CDMRC::Encrypt)),
        "Decode", sol::overload(sol::resolve<std::string(std::string&)>(&CDMRC::Decrypt), sol::resolve< char* (char* pBuf, size_t len)>(&CDMRC::Decrypt))
        );

    lua.new_usertype<CDMMD5>("md5",
        sol::constructors<CDMMD5()>(),
        "GetMD5", sol::overload(sol::resolve<std::string(std::string&)>(&CDMMD5::GetMD5))
        );

    lua.new_usertype<DMDES3Context>("DES3Context");
    lua.new_usertype<DMDES3Block>("DES3Block");

    lua.new_usertype<CDMDes>("des",
        sol::constructors<CDMDes()>(),
        "DESGenKey", sol::overload(sol::resolve<void(DMDES3Block *pIV)>(&CDMDes::DESGenKey)),
        "DESGenEncodeKey", sol::overload(sol::resolve<void(DMDES3Context *pCtx, DMDES3Block &oKey)>(&CDMDes::DESGenEncKeySche)),
        "DESGenDecodeKey", sol::overload(sol::resolve<void(DMDES3Context *pCtx, DMDES3Block &oKey)>(&CDMDes::DESGenDecKeySche)),
        "Encode", sol::overload(sol::resolve<std::string(DMDES3Context *pCtx, DMDES3Block *pIV, std::string& strInput)>(&CDMDes::Encode)),
        "Decode", sol::overload(sol::resolve<std::string(DMDES3Context *pCtx, DMDES3Block *pIV, std::string& strInput)>(&CDMDes::Decode))
        );

    lua.new_usertype<CDMCRC>("crc",
        sol::constructors<CDMCRC()>(),
        "GetCRC", sol::overload(&CDMCRC::GetCRC));

    lua.new_usertype<CDMBase64>("base64",
        sol::constructors<CDMBase64()>(),
        "Encode", sol::overload(&CDMBase64::Base64Encode),
        "Decode", sol::overload(&CDMBase64::Base64Decode),
        "hex2bin", sol::overload(&CDMBase64::hex2bin),
        "bin2hex", sol::overload(&CDMBase64::bin2hex)
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