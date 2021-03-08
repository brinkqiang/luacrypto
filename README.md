# luacrypto

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![luacrypto](https://img.shields.io/badge/brinkqiang-luacrypto-blue.svg?style=flat-square)](https://github.com/brinkqiang/luacrypto)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/luacrypto/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/luacrypto.svg?label=Stars)](https://github.com/brinkqiang/luacrypto) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/luacrypto.svg?label=Fork)](https://github.com/brinkqiang/luacrypto)

## Build status
| [Linux][lin-link] | [MacOSX][osx-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![osx-badge]       | ![win-badge]        |

[lin-badge]: https://travis-ci.org/brinkqiang/luacrypto.svg?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/brinkqiang/luacrypto "Travis build status"
[osx-badge]: https://travis-ci.org/brinkqiang/luacrypto.svg?branch=master "Travis build status"
[osx-link]:  https://travis-ci.org/brinkqiang/luacrypto "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/github/brinkqiang/luacrypto?branch=master&svg=true "AppVeyor build status"
[win-link]:  https://ci.appveyor.com/project/brinkqiang/luacrypto "AppVeyor build status"

## env
install cmake

## Intro
luacrypto

win
```
build.bat
cd bin\relwithdebinfo
lua ..\script\test.lua  
```

linux
```
bash build.sh
cd bin\relwithdebinfo
lua ..\script\test.lua  
```

```lua
local luacrypto = require("luacrypto")

local rc = luacrypto.rc4.new()
rc:SetKey("hello world")

local str = rc:Encode("hello world")
print("rc -> " .. rc:Decode(str))

local md5 = luacrypto.md5.new()
local str2 = md5:GetMD5("hello world")
print("md5 -> " .. str2)

local crc = luacrypto.crc.new()
local str3 = crc:GetCRC("hello world")
print("crc -> " .. str3)

local base64 = luacrypto.base64.new()
local str4 = base64:Encode("hello world")
print("base64 -> " .. base64:Decode(str4))

local des = luacrypto.des.new()
local DES3Block = luacrypto.DES3Block.new()
local DES3ContextEncKey = luacrypto.DES3Context.new()
local DES3ContextDecKey = luacrypto.DES3Context.new()

des:DESGenKey(DES3Block)
des:DESGenEncodeKey(DES3ContextEncKey, DES3Block)
des:DESGenDecodeKey(DES3ContextDecKey, DES3Block)

local encode = des:Encode(DES3ContextEncKey, DES3Block, "hello world")

print("des -> " .. encode)

local decode = des:Decode(DES3ContextDecKey, DES3Block, encode)

print("des -> " .. decode)
```

```output
rc -> hello world
md5 -> 5EB63BBBE01EEED093CB22BB8F5ACDC3
crc -> 222957957
base64 -> hello world
des -> 鑥?剔?;鹰苠嵸
des -> hello world
```
## Contacts

[![Join the chat](https://badges.gitter.im/brinkqiang/luacrypto/Lobby.svg)](https://gitter.im/brinkqiang/luacrypto)

## Thanks
