#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC094(void) {
    u8 i;
    u8 slot_index;

    for (i = 0; i < ARRAY_COUNT(D_801FDE40); i++) {
        if (D_801FDE40[i].timer != g_ScenarioState.timer_06) {
            continue;
        }
        slot_index = Actor_FindFreeSpawned();
        if (slot_index == GAME_NONE) {
            break;
        }
        g_SpawnedActors[slot_index].header.flags     = 1;
        g_SpawnedActors[slot_index].type             = 0x18;
        g_SpawnedActors[slot_index].link             = 0x18;
        COORD_INT(g_SpawnedActors[slot_index].pos.x) = D_801FDE40[i].x;
        COORD_INT(g_SpawnedActors[slot_index].pos.y) = D_801FDE40[i].y;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2) + i % 3);
    }
}

MATCH void func_801FC1C4(void) {
    u8* step;

    step = &g_ScenarioState.step;
    switch (*step) {
        case 0:
            func_8019FA28(0x35, 0x120000, 0x180000, 1);
            g_GamePrevSelection = 0x4D;
            *step               = 1;
            break;
        case 1:
            if (g_SysThreads[2].state == 0) {
                *step = 2;
            }
            break;
        case 2:
            if (*g_ScriptVars == 9) {
                SYS_SetFlag(g_SceneFlags, 7);
                func_8019FA28(0x58, 0x350000, 0x230000, 3);
                g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                *step                    = 0;
            }
            break;
    }
}
