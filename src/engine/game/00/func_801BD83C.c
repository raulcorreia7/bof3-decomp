#include "game_00.h"

MATCH void func_801BD83C(void) {
    s32 alt;
    s32 diff;
    s32 result;
    s32 kind;
    u16 screen_y;
    u8  mode;
    s32 offset;
    s32 value;

    offset   = g_Task->unk_06 * BATTLE_PARTY_STRIDE;
    mode     = ((u8*)D_80145FBB)[offset];
    screen_y = FIELD(u16, &D_80145ECE, offset);
    if (mode == 3) {
        value = COORD_INT(g_Task->z);
        diff  = value - (s16)screen_y;
        diff = ABS(diff);
        if (diff >= 0x81) {
            result = (s16)screen_y < value;
        } else {
            result = 3;
        }
    } else {
        alt    = COORD_INT(g_Task->z);
        result = ((s16)screen_y < alt) * 2;
    }
    kind = result & BYTE_MASK;
    switch (kind) {
        case 0:
            func_801C5558();
            break;
        case 1:
            func_801C5620();
            break;
        case 2:
            func_801C56E4();
            break;
    }
}
