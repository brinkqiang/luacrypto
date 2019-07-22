
local luacrypto = require("luacrypto")

local rc = rc4.new()
rc:SetKey("hello world")

local str = rc:Encrypt("hello world")
print(rc:Decrypt(str))

local md5 = md5.new()
local str2 = md5:GetMD5("hello world")
print(str2)