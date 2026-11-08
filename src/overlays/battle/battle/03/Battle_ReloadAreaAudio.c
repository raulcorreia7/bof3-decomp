#include "battle_03.h"

MATCH void Battle_ReloadAreaAudio(void) {
    if (EMI_IsReady() != 0) {
        volatile u8* state = &g_Battle.phase.sub_step;

        g_EmiStreamFlags |= 0x20u;
        EMI_LoadArchive(g_GameAreaId + EMI_SLOT_AREA);
        *state += 1u;
    }
}
