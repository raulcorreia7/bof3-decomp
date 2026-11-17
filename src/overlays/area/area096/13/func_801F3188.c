#include "area096_13.h"

MATCH void func_801F3188(void) {
    u8 index;

    index = Actor_FindFreeSpawned();
    if (index != 0xFF) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 0x37;
        g_SpawnedActors[index].pos.x.fixed  = 0x410000;
        g_SpawnedActors[index].pos.y.fixed  = 0x3C8000;
        g_SpawnedActors[index].pos.z.fixed  = TO_COORD(512);
        g_SpawnedActors[index].unk_2C       = 0x58;
        g_SpawnedActors[index].unk_07       = 0x12;
        g_SpawnedActors[index].layer        = 1;
        g_SpawnedActors[index].unk_06       = 0;
        g_SpawnedActors[index].unk_29       = 6;

        SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 2));

        if (g_GameAreaId == AREA_ID_BEFORE_MOUNT_GLAUS_BEFORE_NUE) {
            SYS_SetFlag(g_SceneEventFlags, 0x20);
        } else if (g_ScenarioState.scenario_id < 7) {
            SYS_SetFlag(g_SceneEventFlags, 0x21);
        } else {
            SYS_SetFlag(g_SceneEventFlags, 0x22);
        }
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}
