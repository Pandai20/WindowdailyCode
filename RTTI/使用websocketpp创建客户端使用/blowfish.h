// blowfish.h     interface file for blowfish.cpp
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger
//
// modify H.Shirouzu 07/2002 (add change_order(), CBC mode)
// modify H.Shirouzu 01/2004 (add PKCS#5 mode)

#ifndef BLOWFISH_H
#define BLOWFISH_H

#include <stdint.h>

#define MAXKEYuint8_tS		56		// 448 bits max
#define NPASS			16		// SBox passes
#define BF_ECB                  0x0001
#define BF_CBC                  0x0002
//#define BF_OFB		0x0004
//#define BF_CFB		0x0008
//#define BF_PKCS2              0x0010
#define BF_PKCS5                0x0020
#define BF_BLKSIZE              8

#define ALIGN_SIZE(size, align_size) ((((size) + (align_size) -1) / (align_size)) * (align_size))

class CBlowFish
{
public:
    CBlowFish(const uint8_t *key=NULL, int keybytes=0);

    ~CBlowFish();

    void Initialize(const uint8_t *key, int keybytes);

    uint32_t GetOutputLength(uint32_t lInputLong, int mode);

    uint32_t Encrypt(const uint8_t *pInput, uint8_t *pOutput, uint32_t lSize, int mode=BF_CBC|BF_PKCS5, int64_t IV=0);

    uint32_t Decrypt(const uint8_t *pInput, uint8_t *pOutput, uint32_t lSize, int mode=BF_CBC|BF_PKCS5, int64_t IV=0);

private:
    void Blowfish_encipher(uint32_t *xl, uint32_t *xr);
    void Blowfish_decipher(uint32_t *xl, uint32_t *xr);
    uint32_t *PArray;
    uint32_t (*SBoxes)[256];
};

// choose a byte order for your hardware
#define ORDER_DCBA	// chosing Intel in this case

union aword {
    uint32_t	dword;
    uint8_t	byte[4];
    struct {
#ifdef ORDER_ABCD  	// ABCD - big endian - motorola
        uint8_t byte0;
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
#endif
#ifdef ORDER_DCBA  	// DCBA - little endian - intel
        uint8_t byte3;
        uint8_t byte2;
        uint8_t byte1;
        uint8_t byte0;
#endif
#ifdef ORDER_BADC  	// BADC - vax
        uint8_t byte1;
        uint8_t byte0;
        uint8_t byte3;
        uint8_t byte2;
#endif
    } w;
};

#endif
