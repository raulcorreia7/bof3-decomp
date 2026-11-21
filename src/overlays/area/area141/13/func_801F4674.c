#include "area141_13.h"

MATCH void func_801F4674(void) {
    s32 first;
    s32 second;
    s32 first_index;
    s32 second_index;

    first       = Actor_FindFreeField();
    first_index = first & BYTE_MASK;
    if (first_index != GAME_NONE) {
        g_Actors[first_index].header.flags = 1;
        second                             = Actor_FindFreeField();
        second_index                       = second & BYTE_MASK;
        if (second_index == GAME_NONE) {
            g_Actors[first_index].header.flags = 0;
            return;
        }
        g_Actors[second_index].header.flags = 1;
        g_ScratchPad.cells.halves[0]        = (u8)first;
        Actor_SpawnFromRecord(D_801F4E2C);
        g_ScratchPad.cells.halves[0] = (u8)second;
        Actor_SpawnFromRecord(D_801F4E2C + 0x11);
    }
}
