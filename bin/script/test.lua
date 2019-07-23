
local luacrypto = require("luacrypto")

local rc = rc4.new()
rc:SetKey("hello world")

local str = rc:Encrypt("hello world")
print(rc:Decrypt(str))

local md5 = md5.new()
local str2 = md5:GetMD5("hello world")
print(str2)

local crc = crc.new()
local str3 = crc:GetCRC("hello world")
print(str3)

local des = des.new()
local DMDES3Block = DMDES3Block.new()
local DMDES3Context = DMDES3Context.new()

des:DESGenKey(DMDES3Block)
des:DESGenEncKeySche(DMDES3Context, DMDES3Block)

local encode = des:Encode(DMDES3Context, DMDES3Block, "hello world")

print(encode)

local decode = des:Decode(DMDES3Context, DMDES3Block, encode)

print(decode)