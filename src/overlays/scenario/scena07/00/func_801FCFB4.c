#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FCFB4(void) {
    u8 cam                   = D_801FDE88[g_FrameCount & 0x3];
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = g_AreaCameraOffsetY + ((cam << 24) >> 22);
}

MATCH void func_801FD000(void) {
    u8 i;
    u8 idx;

    for (i = 0; i < 0xE; i++) {
        g_ScratchPad.cells.halves[0] = Actor_FindFreeField();
        if (g_ScratchPad.cells.halves[0] != GAME_NONE) {
            idx = i;
            Actor_SpawnFromRecord(&D_801FDE8C[idx * 17]);
            TASK(Actor)->pos.z.part.integer = 0xA00;
            if (D_801FDF7C[idx] != 0) {
                g_CurrentActor->timer_75 = D_801FDF7C[idx];
                TASK(Actor)->unk_03      = TASK(Actor)->header.mode;
                TASK(Actor)->header.mode = 5;
            }
        }
    }
}
