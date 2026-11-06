#include "area030_04.h"

/* Translates the frame's pad state into the panel mode: the 0x10
 *           case advances the step counter, 0x80/0x4 select the next panel
 *           step, and 0x40 either arms or clears the fishing prompt depending
 *           on the lure/rod and the area query. */
MATCH void func_801D9E40(void) {
    switch (g_InputPressed & (PADRup | PADRdown | PADRleft | PADL1)) {
        case PADRup:
            D_80144125 = 7;
            D_8014403D = 4;
            FISHING_STATE->sub_index_03++;
            break;
        case PADRleft:
            D_80144125                   = 7;
            D_8014403D                   = 4;
            FISHING_STATE->mode_index_02 = 9;
            FISHING_STATE->sub_index_03  = 0;
            break;
        case PADRdown:
            D_80144125 = 7;
            if (D_80145026 == 0 || D_80145028 == 0) {
                D_8014403D                   = 4;
                FISHING_STATE->mode_index_02 = 9;
                FISHING_STATE->sub_index_03  = 0;
                break;
            }
            if (func_801E1C10() & BYTE_MASK) {
                if (D_801E3204 == 0) {
                    D_801E3204                  = 1;
                    D_8014403D                  = 4;
                    FISHING_STATE->sub_index_03 = 7;
                    break;
                }
            } else {
                D_801E3204 = 0;
            }
            FISHING_STATE->mode_index_02 = 2;
            /* FAKE: the order lock steers regalloc */
            ORDER_LOCK_BEGIN
                FISHING_STATE->sub_index_03 = 0;
            ORDER_LOCK_END;
            break;
        case PADL1:
            D_80144125                   = 7;
            D_8014403D                   = 4;
            FISHING_STATE->mode_index_02 = 0xA;
            FISHING_STATE->sub_index_03  = 0;
            break;
    }
}
