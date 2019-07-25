
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