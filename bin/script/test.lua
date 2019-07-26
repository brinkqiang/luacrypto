
require("luacrypto")

local rc = rc4.new()
rc:SetKey("hello world")

local str = rc:Encode("hello world")
print("rc -> " .. rc:Decode(str))

local md5 = md5.new()
local str2 = md5:GetMD5("hello world")
print("md5 -> " .. str2)

local crc = crc.new()
local str3 = crc:GetCRC("hello world")
print("crc -> " .. str3)

local base64 = base64.new()
local str4 = base64:Encode("hello world")
print("base64 -> " .. base64:Decode(str4))

local des = des.new()
local DES3Block = DES3Block.new()
local DES3ContextEncKey = DES3Context.new()
local DES3ContextDecKey = DES3Context.new()

des:DESGenKey(DES3Block)
des:DESGenEncodeKey(DES3ContextEncKey, DES3Block)
des:DESGenDecodeKey(DES3ContextDecKey, DES3Block)

local encode = des:Encode(DES3ContextEncKey, DES3Block, "hello world")

print("des -> " .. encode)

local decode = des:Decode(DES3ContextDecKey, DES3Block, encode)

print("des -> " .. decode)