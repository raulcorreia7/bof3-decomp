#include "area042_13.h"
#include "game/spawn.h"

MATCH void func_801F5088(void) {
    u8  i;
    u8  slot;
    s16 field;

    if (D_80143F03 == 0) {
        if (!SYS_TestFlag(g_SceneEventFlags, 0x11)) {
            for (i = 0; i < 3; i++) {
                if (!SYS_TestFlag(D_80144FC4, i + 0x5C)) {
                    D_801F56F8 = i;
                    break;
                }
            }
            if (i == 3) {
                D_801F56F8 = 2;
            }
        }
        field                               = Actor_FindFreeField();
        D_1F800000.view.area.entity_counter = field;
        if (field != GAME_NONE) {
            func_801A7330(&D_801F56D0[D_801F56F8 * 13]);
        }
    }
    if (D_80143F03 == 1) {
        slot                   = Actor_FindFreeSpawned();
        D_1F800000.view.raw[0] = slot;
        if (slot != GAME_NONE) {
            g_SpawnedActors[slot].header.flags                 = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[D_1F800000.view.raw[0]].type       = 0x28;
            g_SpawnedActors[D_1F800000.view.raw[0]].unk_06     = 2;
            g_SpawnedActors[D_1F800000.view.raw[0]].scene_step = 0x418000;
            g_SpawnedActors[D_1F800000.view.raw[0]].selection  = 0x108000;
            g_SpawnedActors[D_1F800000.view.raw[0]].counter_18 = 0x4D8000;
            g_SpawnedActors[D_1F800000.view.raw[0]].counter_1C = 0x108000;
        }
    }
}
