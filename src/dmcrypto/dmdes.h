
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

#ifndef __DMDES_H_INCLUDE__
#define __DMDES_H_INCLUDE__

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <time.h>
#include <dmtypes.h>
#include <string>
/**
* @brief DES enc/dec type macros
* DES编码/解码宏
*/
#define DES_ENCRYPT  1
#define DES_DECRYPT  0

/**
* @brief typedef DES context structure
* key schedule table
* 定义DES上下文结构体
* 关键调度表
*/
typedef struct stDESContext
{
    int32_t		nEnDecMode;			/**<encrypt/decrypt*/
    uint32_t      aSubKey[32];		/**<DES sub-keys*/
} DMDESContext;

/**
* @brief typedef DES block structure
* 64bits key (equal to IV)
* 定义DES块结构
* 64位key（等于IV）
*/
typedef struct stDESBlock
{
    uint8_t acBlock[8];
} DMESBlock;

/**
* @brief typedef 3-DES context structure
* key schedule table
* 定义3－DES上下文结构体
* 关键调度表
*/
typedef struct stDES3Context
{
    int32_t		nEnDecMode;			/**<encrypt/decrypt*/
    uint32_t      aSubKey[96];		/**<DES sub-keys*/
} DMDES3Context;

/**
* @brief typedef 3-DES block structure
* 192bits key (equal to IV)
* 定义3DES块结构体
* 192位key（等于IV）
*/
typedef struct stDES3Block
{
    uint8_t acBlock[24];
} DMDES3Block;

/**
* @brief des 加解密封装类，支持3－DES和DES两种方式
*/
class CDMDes
{
public:
    /**
    * @brief
    * initialize des block 初始化DES块
    * @param pIV : [in/out]DES block structure to be initialized
    * 输入输出参数，将被初始化的DES块结构
    * @return void
    */
    void DESGenKey(DMESBlock *pIV);

    /**
    * @brief
    * initialize des-3 block 初始化3－DES块
    * @param pIV : [in/out]DES-3 block structure to be initialized
    * 输入输出参数，将被初始化的3－DES块结构
    * @return void
    */
    void DES3GenKey(DMDES3Block *pIV);

    /**
    * @brief
    * Generate DES encrypt key 生成DES编码键
    * @param pCtx : [in/out]DES context to be initialized
    * 输入输出参数，将被初始化的DES上下文
    * @param oKey : [in]des block [输入参数]DES块
    * @return void
    */
    void DESGenEncKeySche(DMDESContext *pCtx, DMESBlock &oKey);

    /**
    * @brief
    * Generate DES-3 encrypt key 生成3－DES编码键
    * @param pCtx : [in/out]DES-3 context to be initialized
    * [输入输出参数]将被初始化的DES上下文
    * @param oKey : [in]des block [输入参数]DES块
    * @return void
    */
    void DES3GenEncKeySche(DMDES3Context *pCtx, DMDES3Block &oKey);

    /**
    * @brief
    * Generate DES decrypt key 生成DES解码键
    * @param pCtx : [in/out]DES context to be initialized
    * [输入输出参数]将被初始化的DES上下文
    * @param oKey : [in]des block [输入参数]DES块
    * @return void
    */
    void DESGenDecKeySche(DMDESContext *pCtx, DMESBlock &oKey);

    /**
    * @brief
    * Generate DES-3 decrypt key 生成3－DES解码键
    * @param pCtx : [in/out]DES-3 context to be initialized
    * [输入输出参数]将被初始化的3－DES上下文
    * @param oKey : [in]des block [输入参数]DES块
    * @return void
    */
    void DES3GenDecKeySche(DMDES3Context *pCtx, DMDES3Block &oKey);

    /**
    * @brief
    * DES buffer encryption DES缓冲编码
    * @param pCtx : [in]DES context [输入参数]DES上下文
    * @param pIV :[in] DES block [输入参数]DES块
    * @param nInLen : [in]input buffer len [输入参数]输入缓冲区长度
    * @param pInput : [in]input buffer [输入参数]输入缓冲区
    * @param pOutput : [in/out]output buffer [输入输出参数]输出缓冲区
    * @return void
    */
    void DESEncryptNCBC(DMDESContext *pCtx,
                                DMESBlock *pIV,
                                int32_t nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);

    /**
    * @brief
    * DES-3 buffer encryption 3－DES缓冲编码
    * @param pCtx : [in]DES-3 context [输入参数]3－DES上下文
    * @param pIV : [in]DES-3 block[输入参数] 3－DES块
    * @param nInLen : [in]input buffer len [输入参数]输入缓冲区长度
    * @param pInput : [in]input buffer [输入参数]输入缓冲区
    * @param pOutput : [in/out]output buffer [输入输出参数]输出缓冲区
    * @return void
    */
    void DESEncryptNCBC(DMDES3Context *pCtx,
                                DMDES3Block *pIV,
                                int32_t nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);

    /**
    * @brief
    * DES buffer decryption DES缓冲解码
    * @param pCtx : [in]DES context [输入参数]DES上下文
    * @param pIV : [in]DES block [输入参数]DES块
    * @param nInLen : [in]input buffer len [输入参数]输入缓冲区长度
    * @param pInput : [in]input buffer [输入参数]输入缓冲区
    * @param pOutput : [in/out]output buffer [输入输出参数]输出缓冲区
    * @return void
    */
    void DESDecryptNCBC(DMDESContext *pCtx,
                                DMESBlock *pIV,
                                int32_t  nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);

    /**
    * @brief
    * DES-3 buffer decryption 3－DES缓冲解码
    * @param pCtx : [in]DES-3 context [输入参数]3－DES上下文
    * @param pIV : [in]DES-3 block [输入参数]3－DES块
    * @param nInLen : [in]input buffer len [输入参数]输入缓冲长度
    * @param pInput : [in]input buffer [输入参数]输入缓冲区
    * @param pOutput : [in/out]output buffer [输入输出参数]输出缓冲区
    * @return void
    */
    void DESDecryptNCBC(DMDES3Context *pCtx,
                                DMDES3Block *pIV,
                                int32_t nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);

    std::string Encode(DMDES3Context *pCtx,
        DMDES3Block *pIV,
        const std::string& strInput);

    std::string Decode(DMDES3Context *pCtx,
        DMDES3Block *pIV,
        const std::string& strInput);
};

    /** @} */
#endif // __DMDES_H_INCLUDE__
