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
```lua
require("luacrypto")

local rc = rc4.new()
rc:SetKey("hello world")

local str = rc:Encode("hello world")
print(rc:Decode(str))

local md5 = md5.new()
local str2 = md5:GetMD5("hello world")
print(str2)

local crc = crc.new()
local str3 = crc:GetCRC("hello world")
print(str3)

local des = des.new()
local DES3Block = DES3Block.new()
local DES3ContextEncKey = DES3Context.new()
local DES3ContextDecKey = DES3Context.new()

des:DESGenKey(DES3Block)
des:DESGenEncodeKey(DES3ContextEncKey, DES3Block)
des:DESGenDecodeKey(DES3ContextDecKey, DES3Block)

local encode = des:Encode(DES3ContextEncKey, DES3Block, "hello world")

print(encode)

local decode = des:Decode(DES3ContextDecKey, DES3Block, encode)

print(decode)
```
## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/luacrypto/Lobby.svg)](https://gitter.im/brinkqiang/luacrypto)

## Thanks
