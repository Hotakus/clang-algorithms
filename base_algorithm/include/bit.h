#ifndef CODEWAR_KATA_C_BIT_H_H
#define CODEWAR_KATA_C_BIT_H_H

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
#if __BYTE_ORDER == __BIG_ENDIAN
    unsigned char data;
    struct {
        unsigned char b: 2;
        unsigned char g: 3;
        unsigned char r: 3;
    };
#else
    struct {
        unsigned char r : 3;
        unsigned char g : 3;
        unsigned char b : 2;
    };
    unsigned char data;
#endif

} rgb332_t;

typedef union {
#if __BYTE_ORDER == __BIG_ENDIAN
    unsigned short data;
    struct {
        unsigned char b: 5;
        unsigned char g: 6;
        unsigned char r: 5;
    };
#else
    struct {
        unsigned char r : 5;
        unsigned char g : 6;
        unsigned char b : 5;
    };
    unsigned short data;
#endif
} rgb565_t;

typedef union {
#if __BYTE_ORDER == __BIG_ENDIAN
    unsigned int data;
    struct {
        unsigned char b: 8;
        unsigned char g: 8;
        unsigned char r: 8;
    };
#else
    unsigned int data;
    struct {
        unsigned char r : 8;
        unsigned char g : 8;
        unsigned char b : 8;
    };
#endif
} rgb888_t;


/*...*/

void bit_test();


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //CODEWAR_KATA_C_BIT_H_H
