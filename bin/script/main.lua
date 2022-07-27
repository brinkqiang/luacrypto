
local luacrypto = require("luacrypto")

function bin2hex(s)
    s = string.gsub(s,"(.)",function (x) return string.format("%02X ",string.byte(x)) end)
    return s
end

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

print("des -> " .. bin2hex(encode))

local decode = des:Decode(DES3ContextDecKey, DES3Block, encode)

print("des -> " .. decode)

local aes = luacrypto.aes.new()

local plain = "hello world12345" -- Plaintext length must be divisible by 16
local iv = "hello world"
local key = "hello world"

local aes_encode = aes:EncodeECB(plain, key)

print("aes_ecb -> " .. bin2hex(aes_encode))
local aes_decode = aes:DecodeECB(aes_encode, key)

print("aes_ecb -> " .. aes_decode)

local aes_encode2 = aes:EncodeCFB(plain, key, iv)

print("aes_cfb -> " .. bin2hex(aes_encode2))
local aes_decode2 = aes:DecodeCFB(aes_encode2, key, iv)

print("aes_cfb -> " .. aes_decode2)
