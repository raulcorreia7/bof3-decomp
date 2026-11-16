#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FD07C(void) {
    s16* counter;
    s32  first;
    s32  second;

    first      = Actor_FindFreeField();
    D_801FEA74 = first;
    if (first == GAME_NONE) {
        return;
    }
    g_Actors[first].header.flags = 1;
    second                       = Actor_FindFreeField();
    D_801FEA78                   = second;
    if (second == GAME_NONE) {
        g_Actors[D_801FEA74].header.flags = 0;
        return;
    }
    g_Actors[second].header.flags = 1;
    /* kept: one base register for both writes; writing the view member directly adds four bytes. */
    counter                       = &D_1F800000.view.area.entity_counter;
    *counter                      = D_801FEA74;
    func_801A65A0(D_801FE9A0);
    Actor_BeginScript(0x4C, 0);
    *counter = D_801FEA78;
    func_801A65A0(D_801FE9A0 + 0x10);
    Actor_BeginScript(0x36, 0);
}
