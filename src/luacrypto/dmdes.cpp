#include "dmdes.h"
#include "dmcryptodes.h"

void CDMDes::DESGenKey(DMESBlock* pIV)
{
    DESRandomKey(pIV);
}

void CDMDes::DESGenKey(DMDES3Block* pIV)
{
    GenDES3Key(pIV);
}

void CDMDes::DESGenEncKeySche(DMDESContext *pCtx, DMESBlock& oKey)
{
    DESSetEncKey(pCtx, oKey.acBlock);
}

void CDMDes::DESGenEncKeySche(DMDES3Context *pCtx, DMDES3Block& oKey)
{
    DES3SetEncKey(pCtx, &oKey);
}


void CDMDes::DESGenDecKeySche(DMDESContext *pCtx, DMESBlock& oKey)
{
    DESSetDecKey(pCtx, oKey.acBlock);
}

void CDMDes::DESGenDecKeySche(DMDES3Context *pCtx, DMDES3Block& oKey)
{
    DES3SetDecKey(pCtx, &oKey);
}

void CDMDes::DESEncryptNCBC(DMDESContext    *pCtx,
    DMESBlock		 *pIV,
    int32_t		 nLength,
    unsigned char *pInput,
    unsigned char *pOutput)
{
    DMESBlock IVBak;
    memcpy(&IVBak, (const void*)pIV, sizeof(DMESBlock));
    DESCryptCBC(pCtx, DES_ENCRYPT, nLength, pIV, pInput, pOutput);
    memcpy(pIV, (const void*)&IVBak, sizeof(DMESBlock));
}

void CDMDes::DESEncryptNCBC(DMDES3Context   *pCtx,
    DMDES3Block	 *pIV,
    int32_t		 nLength,
    unsigned char *pInput,
    unsigned char *pOutput)
{
    DMDES3Block IVBak;
    memcpy(&IVBak, (const void*)pIV, sizeof(DMDES3Block));
    DES3CryptCBC(pCtx, DES_ENCRYPT, nLength, pIV, pInput, pOutput);
    memcpy(pIV, (const void*)&IVBak, sizeof(DMDES3Block));
}

void CDMDes::DESDecryptNCBC(DMDESContext	 *pCtx,
    DMESBlock		 *pIV,
    int32_t		 nLength,
    unsigned char *pInput,
    unsigned char *pOutput)
{
    DMESBlock IVBak;
    memcpy(&IVBak, (const void*)pIV, sizeof(DMESBlock));
    DESCryptCBC(pCtx, DES_DECRYPT, nLength, pIV, pInput, pOutput);
    memcpy(pIV, (const void*)&IVBak, sizeof(DMESBlock));
}

void CDMDes::DESDecryptNCBC(DMDES3Context	 *pCtx,
    DMDES3Block	 *pIV,
    int32_t		 nLength,
    unsigned char *pInput,
    unsigned char *pOutput)
{
    DMDES3Block IVBak;
    memcpy(&IVBak, (const void*)pIV, sizeof(DMDES3Block));
    DES3CryptCBC(pCtx, DES_DECRYPT, nLength, pIV, pInput, pOutput);
    memcpy(pIV, (const void*)&IVBak, sizeof(DMDES3Block));
}

