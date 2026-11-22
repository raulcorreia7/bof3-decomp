#include "commu00_00.h"

MATCH void func_801F03D0(void) {
    u8  caps[3];
    s32 row;
    s32 count;
    s32 i;
    s32 value;
    s16 candidate;

    memcpy(caps, D_801EEC08, sizeof(caps));

    for (row = 0; row < 3; row++) {
        for (count = 2; count >= 0; count--) {
            D_801F2930[row][count] = 0;
        }
    }

    for (row = 0; row < 3; row++) {
        count = 0;
        while (count < 3) {
            value = RANDOM_MASK(0x1F);
            while (1) {
                if (caps[row] >= (u8)value) {
                    break;
                }
                value -= RANDOM_MASK(0xF);
            }
            candidate = (value & 0xFF) + 0x9B;
            for (i = 0; i < 3; i++) {
                if ((u16)candidate == D_801F2930[row][i]) {
                    break;
                }
            }
            if ((u32)(candidate - 0x9F) < 2 || i < 3) {
                continue;
            }
            D_801F2930[row][count] = candidate;
            count++;
        }
    }
}
