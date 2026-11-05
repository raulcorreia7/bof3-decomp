#define GAME_SCRATCH_BASE_SCALAR
#include "area141_13.h"

extern u8 D_801F4E2C[];

void func_801A4D54(u8* script);

MATCH void func_801F4674(void) {
    s32 first;
    s32 second;
    s32 first_index;
    s32 second_index;

    first       = Actor_FindFree();
    first_index = first & BYTE_MASK;
    if (first_index != GAME_NONE) {
        g_Actors[first_index].flags_00 = 1;
        second                         = Actor_FindFree();
        second_index                   = second & BYTE_MASK;
        if (second_index == GAME_NONE) {
            g_Actors[first_index].flags_00 = 0;
            return;
        }
        g_Actors[second_index].flags_00 = 1;
        *(s16*)D_1F800000               = (u8)first;
        func_801A4D54(D_801F4E2C);
        *(s16*)D_1F800000 = (u8)second;
        func_801A4D54(D_801F4E2C + 0x11);
    }
}
