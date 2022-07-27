#include "dmaes.h"
#include <string>
#include <numeric>

CDMAES::CDMAES(const AESKeyLength keyLength) {
    this->Nb = 4;
    switch (keyLength) {
    case AESKeyLength::AES_128:
        this->Nk = 4;
        this->Nr = 10;
        break;
    case AESKeyLength::AES_192:
        this->Nk = 6;
        this->Nr = 12;
        break;
    case AESKeyLength::AES_256:
        this->Nk = 8;
        this->Nr = 14;
        break;
    }

    blockBytesLen = 4 * this->Nb * sizeof(unsigned char);
}

CDMAES::~CDMAES()
{

}

unsigned char* CDMAES::EncryptECB(const unsigned char in[], unsigned int inLen,
    const unsigned char key[]) {
    CheckLength(inLen);
    unsigned char* out = new unsigned char[inLen];
    unsigned char* roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        EncryptBlock(in + i, out + i, roundKeys);
    }

    delete[] roundKeys;

    return out;
}


std::string CDMAES::EncryptECB(std::string in, std::string key)
{
    unsigned char* out = EncryptECB((unsigned char*)in.data(), in.size(), (unsigned char*)key.data());

    std::string strRet((char*)out, in.size());
    delete[] out;

    return strRet;
}

unsigned char* CDMAES::DecryptECB(const unsigned char in[], unsigned int inLen,
    const unsigned char key[]) {
    CheckLength(inLen);
    unsigned char* out = new unsigned char[inLen];
    unsigned char* roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        DecryptBlock(in + i, out + i, roundKeys);
    }

    delete[] roundKeys;

    return out;
}


std::string CDMAES::DecryptECB(std::string in, std::string key)
{
    unsigned char* out = DecryptECB((unsigned char*)in.data(), in.size(), (unsigned char*)key.data());

    std::string strRet((char*)out, in.size());
    delete[] out;

    return strRet;
}

unsigned char* CDMAES::EncryptCBC(const unsigned char in[], unsigned int inLen,
    const unsigned char key[],
    const unsigned char* iv) {
    CheckLength(inLen);
    unsigned char* out = new unsigned char[inLen];
    unsigned char* block = new unsigned char[blockBytesLen];
    unsigned char* roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        XorBlocks(block, in + i, block, blockBytesLen);
        EncryptBlock(block, out + i, roundKeys);
        memcpy(block, out + i, blockBytesLen);
    }

    delete[] block;
    delete[] roundKeys;

    return out;
}


std::string CDMAES::EncryptCBC(std::string in, std::string key, std::string iv)
{
    unsigned char* out = EncryptCBC((unsigned char*)(in.data()), in.size(),
        (unsigned char*)key.data(), (unsigned char*)iv.data());
    std::string ret((char*)out, in.size());
    delete[] out;
    return ret;
}

unsigned char* CDMAES::DecryptCBC(const unsigned char in[], unsigned int inLen,
    const unsigned char key[],
    const unsigned char* iv) {
    CheckLength(inLen);
    unsigned char* out = new unsigned char[inLen];
    unsigned char* block = new unsigned char[blockBytesLen];
    unsigned char* roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        DecryptBlock(in + i, out + i, roundKeys);
        XorBlocks(block, out + i, out + i, blockBytesLen);
        memcpy(block, in + i, blockBytesLen);
    }

    delete[] block;
    delete[] roundKeys;

    return out;
}


std::string CDMAES::DecryptCBC(std::string in, std::string key, std::string iv)
{
    unsigned char* out = DecryptCBC((unsigned char*)in.data(), (unsigned int)in.size(),
        (unsigned char*)key.data(), (unsigned char*)iv.data());
    std::string ret((char*)out, in.size());
    delete[] out;
    return ret;
}

unsigned char* CDMAES::EncryptCFB(const unsigned char in[], unsigned int inLen,
    const unsigned char key[],
    const unsigned char* iv) {
    CheckLength(inLen);
    unsigned char* out = new unsigned char[inLen];
    unsigned char* block = new unsigned char[blockBytesLen];
    unsigned char* encryptedBlock = new unsigned char[blockBytesLen];
    unsigned char* roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        EncryptBlock(block, encryptedBlock, roundKeys);
        XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
        memcpy(block, out + i, blockBytesLen);
    }

    delete[] block;
    delete[] encryptedBlock;
    delete[] roundKeys;

    return out;
}


std::string CDMAES::EncryptCFB(std::string in, std::string key, std::string iv)
{
    unsigned char* out = EncryptCFB((unsigned char*)in.data(), (unsigned int)in.size(),
        (unsigned char*)key.data(), (unsigned char*)iv.data());
    std::string ret((char*)out, in.size());
    delete[] out;
    return ret;
}

unsigned char* CDMAES::DecryptCFB(const unsigned char in[], unsigned int inLen,
    const unsigned char key[],
    const unsigned char* iv) {
    CheckLength(inLen);
    unsigned char* out = new unsigned char[inLen];
    unsigned char* block = new unsigned char[blockBytesLen];
    unsigned char* encryptedBlock = new unsigned char[blockBytesLen];
    unsigned char* roundKeys = new unsigned char[4 * Nb * (Nr + 1)];
    KeyExpansion(key, roundKeys);
    memcpy(block, iv, blockBytesLen);
    for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
        EncryptBlock(block, encryptedBlock, roundKeys);
        XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
        memcpy(block, in + i, blockBytesLen);
    }

    delete[] block;
    delete[] encryptedBlock;
    delete[] roundKeys;

    return out;
}


std::string CDMAES::DecryptCFB(std::string in, std::string key, std::string iv)
{
    unsigned char* out = DecryptCFB((unsigned char*)(in.data()), (unsigned int)in.size(),
        (unsigned char*)(key.data()), (unsigned char*)(iv.data()));
    std::string ret((char*)out, in.size());
    delete[] out;
    return ret;
}

void CDMAES::CheckLength(unsigned int len) {
    if (len % blockBytesLen != 0) {
        throw std::length_error("Plaintext length must be divisible by " + std::to_string(blockBytesLen));
    }
}

void CDMAES::EncryptBlock(const unsigned char in[], unsigned char out[],
    unsigned char* roundKeys) {
    unsigned char** state = new unsigned char* [4];
    state[0] = new unsigned char[4 * Nb];
    int i, j, round;
    for (i = 0; i < 4; i++) {
        state[i] = state[0] + Nb * i;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            state[i][j] = in[i + 4 * j];
        }
    }

    AddRoundKey(state, roundKeys);

    for (round = 1; round <= Nr - 1; round++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, roundKeys + round * 4 * Nb);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, roundKeys + Nr * 4 * Nb);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            out[i + 4 * j] = state[i][j];
        }
    }

    delete[] state[0];
    delete[] state;
}

void CDMAES::DecryptBlock(const unsigned char in[], unsigned char out[],
    unsigned char* roundKeys) {
    unsigned char** state = new unsigned char* [4];
    state[0] = new unsigned char[4 * Nb];
    int i, j, round;
    for (i = 0; i < 4; i++) {
        state[i] = state[0] + Nb * i;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            state[i][j] = in[i + 4 * j];
        }
    }

    AddRoundKey(state, roundKeys + Nr * 4 * Nb);

    for (round = Nr - 1; round >= 1; round--) {
        InvSubBytes(state);
        InvShiftRows(state);
        AddRoundKey(state, roundKeys + round * 4 * Nb);
        InvMixColumns(state);
    }

    InvSubBytes(state);
    InvShiftRows(state);
    AddRoundKey(state, roundKeys);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            out[i + 4 * j] = state[i][j];
        }
    }

    delete[] state[0];
    delete[] state;
}

void CDMAES::SubBytes(unsigned char** state) {
    int i, j;
    unsigned char t;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            t = state[i][j];
            state[i][j] = sbox[t / 16][t % 16];
        }
    }
}

void CDMAES::ShiftRow(unsigned char** state, int i,
    int n)  // shift row i on n positions
{
    unsigned char* tmp = new unsigned char[Nb];
    for (int j = 0; j < Nb; j++) {
        tmp[j] = state[i][(j + n) % Nb];
    }
    memcpy(state[i], tmp, Nb * sizeof(unsigned char));

    delete[] tmp;
}

void CDMAES::ShiftRows(unsigned char** state) {
    ShiftRow(state, 1, 1);
    ShiftRow(state, 2, 2);
    ShiftRow(state, 3, 3);
}

unsigned char CDMAES::xtime(unsigned char b)  // multiply on x
{
    return (b << 1) ^ (((b >> 7) & 1) * 0x1b);
}

void CDMAES::MixColumns(unsigned char** state) {
    unsigned char temp_state[4][4];

    for (size_t i = 0; i < 4; ++i) {
        memset(temp_state[i], 0, 4);
    }

    for (size_t i = 0; i < 4; ++i) {
        for (size_t k = 0; k < 4; ++k) {
            for (size_t j = 0; j < 4; ++j) {
                if (CMDS[i][k] == 1)
                    temp_state[i][j] ^= state[k][j];
                else
                    temp_state[i][j] ^= GF_MUL_TABLE[CMDS[i][k]][state[k][j]];
            }
        }
    }

    for (size_t i = 0; i < 4; ++i) {
        memcpy(state[i], temp_state[i], 4);
    }
}

void CDMAES::AddRoundKey(unsigned char** state, unsigned char* key) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            state[i][j] = state[i][j] ^ key[i + 4 * j];
        }
    }
}

void CDMAES::SubWord(unsigned char* a) {
    int i;
    for (i = 0; i < 4; i++) {
        a[i] = sbox[a[i] / 16][a[i] % 16];
    }
}

void CDMAES::RotWord(unsigned char* a) {
    unsigned char c = a[0];
    a[0] = a[1];
    a[1] = a[2];
    a[2] = a[3];
    a[3] = c;
}

void CDMAES::XorWords(unsigned char* a, unsigned char* b, unsigned char* c) {
    int i;
    for (i = 0; i < 4; i++) {
        c[i] = a[i] ^ b[i];
    }
}

void CDMAES::Rcon(unsigned char* a, int n) {
    int i;
    unsigned char c = 1;
    for (i = 0; i < n - 1; i++) {
        c = xtime(c);
    }

    a[0] = c;
    a[1] = a[2] = a[3] = 0;
}

void CDMAES::KeyExpansion(const unsigned char key[], unsigned char w[]) {
    unsigned char* temp = new unsigned char[4];
    unsigned char* rcon = new unsigned char[4];

    int i = 0;
    while (i < 4 * Nk) {
        w[i] = key[i];
        i++;
    }

    i = 4 * Nk;
    while (i < 4 * Nb * (Nr + 1)) {
        temp[0] = w[i - 4 + 0];
        temp[1] = w[i - 4 + 1];
        temp[2] = w[i - 4 + 2];
        temp[3] = w[i - 4 + 3];

        if (i / 4 % Nk == 0) {
            RotWord(temp);
            SubWord(temp);
            Rcon(rcon, i / (Nk * 4));
            XorWords(temp, rcon, temp);
        }
        else if (Nk > 6 && i / 4 % Nk == 4) {
            SubWord(temp);
        }

        w[i + 0] = w[i - 4 * Nk] ^ temp[0];
        w[i + 1] = w[i + 1 - 4 * Nk] ^ temp[1];
        w[i + 2] = w[i + 2 - 4 * Nk] ^ temp[2];
        w[i + 3] = w[i + 3 - 4 * Nk] ^ temp[3];
        i += 4;
    }

    delete[] rcon;
    delete[] temp;
}

void CDMAES::InvSubBytes(unsigned char** state) {
    int i, j;
    unsigned char t;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < Nb; j++) {
            t = state[i][j];
            state[i][j] = inv_sbox[t / 16][t % 16];
        }
    }
}

void CDMAES::InvMixColumns(unsigned char** state) {
    unsigned char temp_state[4][4];

    for (size_t i = 0; i < 4; ++i) {
        memset(temp_state[i], 0, 4);
    }

    for (size_t i = 0; i < 4; ++i) {
        for (size_t k = 0; k < 4; ++k) {
            for (size_t j = 0; j < 4; ++j) {
                temp_state[i][j] ^= GF_MUL_TABLE[INV_CMDS[i][k]][state[k][j]];
            }
        }
    }

    for (size_t i = 0; i < 4; ++i) {
        memcpy(state[i], temp_state[i], 4);
    }
}

void CDMAES::InvShiftRows(unsigned char** state) {
    ShiftRow(state, 1, Nb - 1);
    ShiftRow(state, 2, Nb - 2);
    ShiftRow(state, 3, Nb - 3);
}

void CDMAES::XorBlocks(const unsigned char* a, const unsigned char* b,
    unsigned char* c, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        c[i] = a[i] ^ b[i];
    }
}

void CDMAES::printHexArray(unsigned char a[], unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        printf("%02x ", a[i]);
    }
}

void CDMAES::printHexVector(std::vector<unsigned char> a) {
    for (unsigned int i = 0; i < a.size(); i++) {
        printf("%02x ", a[i]);
    }
}

std::vector<unsigned char> CDMAES::ArrayToVector(unsigned char* a,
    unsigned int len) {
    std::vector<unsigned char> v(a, a + len * sizeof(unsigned char));
    return v;
}

unsigned char* CDMAES::VectorToArray(std::vector<unsigned char>& a) {
    return a.data();
}

std::vector<unsigned char> CDMAES::EncryptECB(std::vector<unsigned char> in,
    std::vector<unsigned char> key) {
    unsigned char* out = EncryptECB(VectorToArray(in), (unsigned int)in.size(),
        VectorToArray(key));
    std::vector<unsigned char> v = ArrayToVector(out, in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> CDMAES::DecryptECB(std::vector<unsigned char> in,
    std::vector<unsigned char> key) {
    unsigned char* out = DecryptECB(VectorToArray(in), (unsigned int)in.size(),
        VectorToArray(key));
    std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> CDMAES::EncryptCBC(std::vector<unsigned char> in,
    std::vector<unsigned char> key,
    std::vector<unsigned char> iv) {
    unsigned char* out = EncryptCBC(VectorToArray(in), (unsigned int)in.size(),
        VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> CDMAES::DecryptCBC(std::vector<unsigned char> in,
    std::vector<unsigned char> key,
    std::vector<unsigned char> iv) {
    unsigned char* out = DecryptCBC(VectorToArray(in), (unsigned int)in.size(),
        VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> CDMAES::EncryptCFB(std::vector<unsigned char> in,
    std::vector<unsigned char> key,
    std::vector<unsigned char> iv) {
    unsigned char* out = EncryptCFB(VectorToArray(in), (unsigned int)in.size(),
        VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, in.size());
    delete[] out;
    return v;
}

std::vector<unsigned char> CDMAES::DecryptCFB(std::vector<unsigned char> in,
    std::vector<unsigned char> key,
    std::vector<unsigned char> iv) {
    unsigned char* out = DecryptCFB(VectorToArray(in), (unsigned int)in.size(),
        VectorToArray(key), VectorToArray(iv));
    std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
    delete[] out;
    return v;
}
