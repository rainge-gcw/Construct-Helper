//
// Created by oceanstar on 2021/8/13.
//
#include <cstdlib>
#include "base64.h"

namespace oceanstar{
    static const unsigned char to_b64[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    static const unsigned char un_b64[] = {
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62,  255, 255, 255, 63,
            52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  255, 255, 255, 255, 255, 255,
            255, 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
            15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  255, 255, 255, 255, 255,
            255, 26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,
            41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
    };

#define UNSIG_CHAR_PTR(x) ((const unsigned char *)(x))
    unsigned char *acl_base64_encode( const char *in, int len){
        const unsigned char *cp;
        int     count, size = len * 4 /3;

        unsigned char * out = (unsigned char *)malloc(size + 1);
        int out_index = 0;
        for (cp = UNSIG_CHAR_PTR(in), count = len; count > 0; count -= 3, cp += 3) {
            out[out_index++] = to_b64[cp[0] >> 2];
            if (count > 1) {
                out[out_index++] = to_b64[(cp[0] & 0x3) << 4 | cp[1] >> 4];
                if (count > 2) {
                    out[out_index++] = to_b64[(cp[1] & 0xf) << 2 | cp[2] >> 6];
                    out[out_index++] = to_b64[cp[2] & 0x3f];
                }else{
                    out[out_index++] = to_b64[(cp[1] & 0xf) << 2];
                    out[out_index++] = '=';
                    break;
                }
            } else {
                out[out_index++] = to_b64[(cp[0] & 0x3) << 4];
                out[out_index++] = '=';
                out[out_index++] = '=';
                break;
            }
        }
        out[out_index] = 0;
        return out;
    }

    unsigned char *acl_base64_decode(const char *in, int len){
        const unsigned char *cp;
        int     count;
        int     ch0;
        int     ch1;
        int     ch2;
        int     ch3;

        /*
	 * Sanity check.
	 */
        if (len % 4)
            return (NULL);

#define INVALID		0xff

        unsigned char * out = (unsigned char *)malloc(len + 1);
        int out_index = 0;
        for (cp = UNSIG_CHAR_PTR(in), count = 0; count < len; count += 4) {
            if ((ch0 = un_b64[*cp++]) == INVALID
                || (ch1 = un_b64[*cp++]) == INVALID)
                return (0);
            out[out_index++] = ch0 << 2 | ch1 >> 4;
            if ((ch2 = *cp++) == '=')
                break;
            if ((ch2 = un_b64[ch2]) == INVALID)
                return (0);
            out[out_index++] = ch1 << 4 | ch2 >> 2;
            if ((ch3 = *cp++) == '=')
                break;
            if ((ch3 = un_b64[ch3]) == INVALID)
                return (0);
            out[out_index++] = ch2 << 6 | ch3;
        }

        out[out_index] = 0;
        return out;
    }

}
