#include "area030_04.h"

/* Resets the AREA030 panel scratch record and sub-state, starts the
 * panel cue selected by the loaded-scene flags, and advances the state byte. */
MATCH void func_801D9D38(void) {
    u8* record;
    s32 mode;

    func_801DDE2C();

    D_801E3208                  = 0xFF;
    /* FAKE: typed word stores let the scheduler hoist the later byte store; retail keeps them in order. */
    *(u32*)((u8*)g_Task + 0x0C) = 0;
    *(u32*)((u8*)g_Task + 0x10) = 0;
    *(u32*)((u8*)g_Task + 0x14) = 0;
    *(u32*)((u8*)g_Task + 0x18) = 0;
    *(u32*)((u8*)g_Task + 0x1C) = 0;
    *(u32*)((u8*)g_Task + 0x20) = 0;
    g_Task->unk_09              = 0;

    mode = (D_80145026 && D_80145028) ? 0 : 6;
    func_801DDE94(mode);

    if (g_GameState->slot_index_79 == 0) {
        Actor_BeginScript(0xA, 2);
    } else {
        Actor_SelectScript(0xB);
    }

    record    = (u8*)g_Task;
    record[3] = (u8)(record[3] + 1);
}
