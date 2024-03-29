cmake_minimum_required(VERSION 3.2)

PROJECT(luacrypto)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/LuaModule.cmake)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(LUA_MODULE lua54)
SET(LUACRYPTO_VERSION_MAJOR "1")
SET(LUACRYPTO_VERSION_MINOR "0")
SET(LUACRYPTO_VERSION_PATCH "1")
SET(LUACRYPTO_VERSION "${LUACRYPTO_VERSION_MAJOR}.${LUACRYPTO_VERSION_MINOR}.${LUACRYPTO_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${LUACRYPTO_VERSION}")

ADD_DEFINITIONS(-DUSE_LUACRYPTO)
ADD_DEFINITIONS(-DLUA_COMPAT_MODULE -DLUA_COMPAT_APIINTCASTS)

LibImport("dmcrypto" "src/dmcrypto")
LuaModuleImport("${LUA_MODULE}" "luacrypto" "src/luacrypto" "dmcrypto")

