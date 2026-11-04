#include "scena19_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6C0C(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    ORDER_LOCK(D_801F6DD0[index]());
}

MATCH void func_801F6C40(void) {
    D_80146872 = 1;
}

MATCH void func_801F6C54(void) {
    D_80146872 = 2;
}

MATCH void func_801F6C68(void) {
    SYS_DISPATCH_BYTE(D_801F6DDC, g_SceneState.state_04);
}

MATCH void func_801F6CA4(void) {
    ActorSlot* slot;
    s32        index;

    if (g_InputPressed & PADR1) {
        index = Actor_FindFreeSlot();
        if (index != GAME_NONE) {
            slot           = &g_ActorSlots[index];
            slot->flags_00 = 1;
            slot->type     = 0x2F;
        }
    }
}

MATCH void func_801F6D10(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801F6DE0[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801F6D50(void) {
}

MATCH s32 func_801F6D58(void) {
    return 0;
}

MATCH s32 func_801F6D60(void) {
    return 0;
}

#include "overlays/scenario/Scene_SetPartyRyuTeepoRei.h"

MATCH void func_801F6DB4(void) {
}
