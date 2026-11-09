#include "area030_04.h"

/* Advances the four AREA030 label slots for one frame. */
MATCH void func_801DE018(void) {
    s32 i;
    s32 mode;
    u8  v;
    u8  m;
    s8  grow;
    s8  limit;
    s8  span;

    func_801DDFD4();
    for (i = 0; i < 4; i++) {
        v    = D_801E31E0[i];
        m    = (*(u8*)(*(u8**)(D_801E28F4 + i * 8) + v) & 0x7F);
        mode = 0;
        if (v != 0) {
            D_801E31E4[i] = (D_801E31E4[i] - 1);
        }
        if (D_801E31F0 == 1) {
            if (D_801E31E0[i] != 0) {
                if (D_801E31E4[i] < 4) {
                    mode = (m == 1) ? 1 : 2;
                } else {
                    mode = 2;
                }
            } else {
                mode = 1;
            }
        } else if (D_801E31F0 == 0 && D_801E31E4[i] == 0) {
            mode = 2;
            if (m == 0) {
                mode = 1;
            }
        }
        if (mode == 1) {
            v = D_801E31E0[i];
            if ((*(u8*)(*(u8**)(D_801E28F4 + i * 8) + v) & 0x80) != 0) {
                grow  = D_801E28F8[i * 8];
                limit = g_ActorSlots[0].unk_07;
                span  = g_FishingLureRow->unk_0F;
                if (grow + span >= limit) {
                    g_ActorSlots[0].unk_07 = (grow + span);
                    g_ActorSlots[0].unk_0A = g_FishingLureRow->unk_10;
                }
                D_801E31E0[i] = 0;
                D_801E31E4[i] = 0;
            } else {
                D_801E31E0[i] = (v + 1);
                D_801E31E4[i] = 0xC;
            }
        } else if (mode == 2) {
            D_801E31E4[i] = 0;
            D_801E31E0[i] = 0;
        }
    }
}
