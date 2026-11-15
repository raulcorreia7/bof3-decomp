#include "area096_13.h"

MATCH void func_801F3188(void) {
    u8 index;

    index = Actor_FindFreeSpawned();
    if (index != 0xFF) {
        D_80143FC8[index].value = 1;
        D_80143FCD[index].value = 0x37;
        D_80143FFC[index].value = 0x410000;
        D_80144000[index].value = 0x3C8000;
        D_80144004[index].value = TO_COORD(512);
        D_80143FF4[index].value = 0x58;
        D_80143FCF[index].value = 0x12;
        D_80143FD1[index].value = 1;
        D_80143FCE[index].value = 0;
        D_80143FF1[index].value = 6;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));

        if (g_GameAreaId == AREA_ID_BEFORE_MOUNT_GLAUS_BEFORE_NUE) {
            SYS_SetFlag(g_SceneEventFlags, 0x20);
        } else if (g_SceneState.scenario_id < 7) {
            SYS_SetFlag(g_SceneEventFlags, 0x21);
        } else {
            SYS_SetFlag(g_SceneEventFlags, 0x22);
        }
    } else {
        g_CurrentActor->unk_7E -= 2;
    }
}
