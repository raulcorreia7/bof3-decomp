#include "scena19_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6C0C(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    SYS_DISPATCH_INDEX(D_801F6DD0, index);
}

MATCH void func_801F6C40(void) {
    D_80146872 = 1;
}

MATCH void func_801F6C54(void) {
    D_80146872 = 2;
}

MATCH void func_801F6C68(void) {
    SYS_DISPATCH_BYTE(D_801F6DDC, g_ScenarioState.state_04);
}

MATCH void func_801F6CA4(void) {
    SpawnedActor* slot;
    s32           index;

    if (g_PadStates[0].pressed & PADR1) {
        index = Actor_FindFreeSpawned();
        if (index != GAME_NONE) {
            slot               = &g_SpawnedActors[index];
            slot->header.flags = 1;
            slot->type         = 0x2F;
        }
    }
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801F6D50(void) {
}

MATCH s32 func_801F6D58(void) {
    return 0;
}

MATCH s32 func_801F6D60(void) {
    return 0;
}

#include "overlays/scenario/shared/Scene_SetPartyRyuYoungTeepoRei.h"

MATCH void func_801F6DB4(void) {
}
