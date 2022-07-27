
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
#include "sol/sol.hpp"
#include "luacrypto_module.h"

#include "dmrc.hpp"
#include "dmdes.h"
#include "dmmd5.h"
#include "dmcrc.h"
#include "dmbase64.h"
#include "dmaes.h"

namespace lua_module
{
    static sol::table require_api(sol::this_state L) {
        sol::state_view lua(L);
        sol::table module = lua.create_table();

        module.new_usertype<CDMRC>("rc4",
            sol::constructors<CDMRC()>(),
            "SetKey", &CDMRC::SetKey,
            "Encode", sol::resolve<std::string(const std::string&)>(&CDMRC::Encrypt),
            "Decode", sol::resolve<std::string(const std::string&)>(&CDMRC::Decrypt)
            );

        module.new_usertype<CDMMD5>("md5",
            sol::constructors<CDMMD5()>(),
            "GetMD5", sol::resolve<std::string(const std::string&)>(&CDMMD5::GetMD5)
            );

        module.new_usertype<DMDES3Context>("DES3Context");
        module.new_usertype<DMDES3Block>("DES3Block");

        module.new_usertype<CDMDes>("des",
            sol::constructors<CDMDes()>(),
            "DESGenKey", (&CDMDes::DES3GenKey),
            "DESGenEncodeKey", (&CDMDes::DES3GenEncKeySche),
            "DESGenDecodeKey", (&CDMDes::DES3GenDecKeySche),
            "Encode", (&CDMDes::Encode),
            "Decode", (&CDMDes::Decode)
            );

        module.new_usertype<CDMCRC>("crc",
            sol::constructors<CDMCRC()>(),
            "GetCRC", (&CDMCRC::GetCRC)
            );

        module.new_usertype<CDMBase64>("base64",
            sol::constructors<CDMBase64()>(),
            "Encode", (&CDMBase64::Base64Encode),
            "Decode", (&CDMBase64::Base64Decode),
            "hex2bin", (&CDMBase64::hex2bin),
            "bin2hex", (&CDMBase64::bin2hex)
            );

        module.new_usertype<CDMAES>("aes",
            sol::constructors<CDMAES()>(),
            "EncodeECB", sol::resolve<std::string(std::string, std::string)>(&CDMAES::EncryptECB),
            "DecodeECB", sol::resolve<std::string(std::string, std::string)>(&CDMAES::DecryptECB),
            "EncodeCBC", sol::resolve<std::string(std::string, std::string, std::string)>(&CDMAES::EncryptCBC),
            "DecodeCBC", sol::resolve<std::string(std::string, std::string, std::string)>(&CDMAES::DecryptCBC),
            "EncodeCFB", sol::resolve<std::string(std::string, std::string, std::string)>(&CDMAES::EncryptCFB),
            "DecodeCFB", sol::resolve<std::string(std::string, std::string, std::string)>(&CDMAES::DecryptCFB)
            );

        return module;
    }
}

LUAMOD_API int luaopen_luacrypto(lua_State* L)
{
    return sol::stack::call_lua(L, 1, lua_module::require_api);
}

LUAMOD_API int require_luacrypto(lua_State* L)
{
    luaL_requiref(L, "luacrypto", luaopen_luacrypto, 0);
    printf("lua module: require luacrypto\n");
    return 1;
}
