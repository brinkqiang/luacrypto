
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

/**
* @brief DES enc/dec type macros
* DES����/�����
*/
#define DES_ENCRYPT  1
#define DES_DECRYPT  0

/**
* @brief typedef DES context structure
* key schedule table
* ����DES�����Ľṹ��
* �ؼ����ȱ�
*/
typedef struct stDESContext
{
    int32_t		nEnDecMode;			/**<encrypt/decrypt*/
    uint32_t      aSubKey[32];		/**<DES sub-keys*/
} DMDESContext;

/**
* @brief typedef DES block structure
* 64bits key (equal to IV)
* ����DES��ṹ
* 64λkey������IV��
*/
typedef struct stDESBlock
{
    uint8_t acBlock[8];
} DMESBlock;

/**
* @brief typedef 3-DES context structure
* key schedule table
* ����3��DES�����Ľṹ��
* �ؼ����ȱ�
*/
typedef struct stDES3Context
{
    int32_t		nEnDecMode;			/**<encrypt/decrypt*/
    uint32_t      aSubKey[96];		/**<DES sub-keys*/
} DMDES3Context;

/**
* @brief typedef 3-DES block structure
* 192bits key (equal to IV)
* ����3DES��ṹ��
* 192λkey������IV��
*/
typedef struct stDES3Block
{
    uint8_t acBlock[24];
} DMDES3Block;

/**
* @brief des �ӽ��ܷ�װ�֧࣬��3��DES��DES���ַ�ʽ
*/
class CDMDes
{
public:
    /**
    * @brief
    * initialize des block ��ʼ��DES��
    * @param pIV : [in/out]DES block structure to be initialized
    * �������������������ʼ����DES��ṹ
    * @return void
    */
    void DESGenKey(DMESBlock *pIV);

    /**
    * @brief
    * initialize des-3 block ��ʼ��3��DES��
    * @param pIV : [in/out]DES-3 block structure to be initialized
    * �������������������ʼ����3��DES��ṹ
    * @return void
    */
    void DESGenKey(DMDES3Block *pIV);

    /**
    * @brief
    * Generate DES encrypt key ����DES�����
    * @param pCtx : [in/out]DES context to be initialized
    * �������������������ʼ����DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void DESGenEncKeySche(DMDESContext *pCtx, DMESBlock &oKey);

    /**
    * @brief
    * Generate DES-3 encrypt key ����3��DES�����
    * @param pCtx : [in/out]DES-3 context to be initialized
    * [�����������]������ʼ����DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void DESGenEncKeySche(DMDES3Context *pCtx, DMDES3Block &oKey);

    /**
    * @brief
    * Generate DES decrypt key ����DES�����
    * @param pCtx : [in/out]DES context to be initialized
    * [�����������]������ʼ����DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void DESGenDecKeySche(DMDESContext *pCtx, DMESBlock &oKey);

    /**
    * @brief
    * Generate DES-3 decrypt key ����3��DES�����
    * @param pCtx : [in/out]DES-3 context to be initialized
    * [�����������]������ʼ����3��DES������
    * @param oKey : [in]des block [�������]DES��
    * @return void
    */
    void DESGenDecKeySche(DMDES3Context *pCtx, DMDES3Block &oKey);

    /**
    * @brief
    * DES buffer encryption DES�������
    * @param pCtx : [in]DES context [�������]DES������
    * @param pIV :[in] DES block [�������]DES��
    * @param nInLen : [in]input buffer len [�������]���뻺��������
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void DESEncryptNCBC(DMDESContext *pCtx,
                                DMESBlock *pIV,
                                int32_t nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);

    /**
    * @brief
    * DES-3 buffer encryption 3��DES�������
    * @param pCtx : [in]DES-3 context [�������]3��DES������
    * @param pIV : [in]DES-3 block[�������] 3��DES��
    * @param nInLen : [in]input buffer len [�������]���뻺��������
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void DESEncryptNCBC(DMDES3Context *pCtx,
                                DMDES3Block *pIV,
                                int32_t nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);

    /**
    * @brief
    * DES buffer decryption DES�������
    * @param pCtx : [in]DES context [�������]DES������
    * @param pIV : [in]DES block [�������]DES��
    * @param nInLen : [in]input buffer len [�������]���뻺��������
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void DESDecryptNCBC(DMDESContext *pCtx,
                                DMESBlock *pIV,
                                int32_t  nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);

    /**
    * @brief
    * DES-3 buffer decryption 3��DES�������
    * @param pCtx : [in]DES-3 context [�������]3��DES������
    * @param pIV : [in]DES-3 block [�������]3��DES��
    * @param nInLen : [in]input buffer len [�������]���뻺�峤��
    * @param pInput : [in]input buffer [�������]���뻺����
    * @param pOutput : [in/out]output buffer [�����������]���������
    * @return void
    */
    void DESDecryptNCBC(DMDES3Context *pCtx,
                                DMDES3Block *pIV,
                                int32_t nInLen,
                                uint8_t *pInput,
                                uint8_t *pOutput);
};

    /** @} */
#endif // __DMDES_H_INCLUDE__
