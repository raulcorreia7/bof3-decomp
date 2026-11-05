#include "area141_13.h"

extern u8 D_801F4E0C[];

void func_801A65A0(u8* script);

MATCH void func_801F4584(void) {
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
        D_1F800000.view.area.entity_counter = (u8)first;
        func_801A65A0(D_801F4E0C);
        D_1F800000.view.area.entity_counter = (u8)second;
        func_801A65A0(D_801F4E0C + 0x10);
    }
}
