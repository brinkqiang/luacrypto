
#ifndef __DMCRC_H_INCLUDE__
#define __DMCRC_H_INCLUDE__

#include <stddef.h>
#include "dmtypes.h"

class CDMCRC;
class CDMCRCTableInit;

static const uint32_t kCRCPoly = 0xEDB88320;

class CDMCRCTableInit {
  public:
    CDMCRCTableInit() {
        InitTable();
    }

    static inline uint32_t* GetTable() {
        static uint32_t sTable[256];

        return (uint32_t*)&sTable;
    }

    static inline void InitTable() {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t r = i;

            for (int j = 0; j < 8; j++)
                if (r & 1) {
                    r = (r >> 1) ^ kCRCPoly;
                }
                else {
                    r >>= 1;
                }

            GetTable()[i] = r;
        }
    }
};

class CDMCRC {
  private:
    uint32_t _value;
  public:
    static inline CDMCRCTableInit& CRCTableInit() {
        static CDMCRCTableInit sCRCTableInit;
        return sCRCTableInit;
    }

    CDMCRC():  _value(0xFFFFFFFF) {
        CRCTableInit();
    };

    inline void Init() {
        _value = 0xFFFFFFFF;
    }

    inline void UpdateUINT8(uint8_t v) {
        _value = CDMCRCTableInit::GetTable()[((uint8_t)(_value)) ^ v] ^ (_value >> 8);
    }

    inline void UpdateUINT16(uint16_t v) {
        UpdateUINT8(uint8_t(v));
        UpdateUINT8(uint8_t(v >> 8));
    }

    inline void UpdateUINT32(uint32_t v) {
        for (int i = 0; i < 4; i++) {
            UpdateUINT8((uint8_t)(v >> (8 * i)));
        }
    }

    inline void UpdateUInt64(uint64_t v) {
        for (int i = 0; i < 8; i++) {
            UpdateUINT8((uint8_t)(v >> (8 * i)));
        }
    }

    inline void Update(const void* data, size_t size) {
        uint32_t v = _value;
        const uint8_t* p = (const uint8_t*)data;

        for (; size > 0 ; size--, p++) {
            v = CDMCRCTableInit::GetTable()[((uint8_t)(v)) ^ *p] ^ (v >> 8);
        }

        _value = v;
    }

    inline uint32_t GetDigest() const {
        return _value ^ 0xFFFFFFFF;
    }

    inline uint32_t GetCRC(const std::string& strData)
    {
        return CalculateDigest(strData.data(), strData.size());
    }

    static  inline uint32_t CalculateDigest(const void* data, size_t size) {
        CDMCRC crc;
        crc.Update(data, size);
        return crc.GetDigest();
    }
    static inline bool VerifyDigest(uint32_t digest, const void* data,
                                    size_t size) {
        return (CalculateDigest(data, size) == digest);
    }
};

#endif // __DMCRC_H_INCLUDE__
