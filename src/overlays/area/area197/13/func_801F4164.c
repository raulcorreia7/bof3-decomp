#include "area197_13.h"

MATCH void func_801F4164(void) {
    s8* state;

    state = (s8*)&D_801448EC;
    switch (*state) {
        case 0:
            func_801BE1B0(0);
            *state = 1;
            break;
        case 1:
            if (D_80146867 == 0x24) {
                SYS_SetFlag(state + 0x63C, 0x55);
                func_8019FA28(0xAA, 0x60000, 0x3F0000, 0x82);
                *state = 0x1E;
            }
            break;
    }
}
