#include "area141_13.h"

extern u8 D_801F4DDC[];

void func_801A65A0(u8* script);
void Actor_BeginScript(s32 raw_selector, s32 raw_code);

MATCH void func_801F4400(void) {
    s32 first;
    s32 second;
    s32 first_index;
    s32 second_index;

    first       = Actor_FindFree();
    first_index = first & 0xFF;
    if (first_index != GAME_NONE) {
        g_Actors[first_index].header.flags = 1;
        second                             = Actor_FindFree();
        second_index                       = second & 0xFF;
        if (second_index == GAME_NONE) {
            g_Actors[first_index].header.flags = 0;
            return;
        }
        g_Actors[second_index].header.flags = 1;
        D_1F800000.view.area.entity_counter = (u8)first;
        func_801A65A0(D_801F4DDC);
        Actor_BeginScript(107, 0);
        D_1F800000.view.area.entity_counter = (u8)second;
        func_801A65A0(D_801F4DDC + 0x10);
        Actor_BeginScript(88, 0);
    }
}
