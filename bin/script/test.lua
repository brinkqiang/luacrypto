
local luacrypto = require("luacrypto")

local rc = rc4.new()
rc:SetKey("hello world")

local str = rc:Encrypt("hello world")
print(rc:Decrypt(str))
