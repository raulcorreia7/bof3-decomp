#include "scena18_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6C0C(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    ORDER_LOCK(D_801F6D6C[index]());
}

MATCH void func_801F6C40(void) {
    D_80146872 = 1;
}

MATCH void func_801F6C54(void) {
    D_80146872 = 2;
}

MATCH void func_801F6C68(void) {
    SYS_DISPATCH_BYTE(D_801F6D78, g_SceneState.state_04);
}

MATCH void func_801F6CA4(void) {
}

MATCH void func_801F6CAC(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801F6D7C[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801F6CEC(void) {
}

MATCH s32 func_801F6CF4(void) {
    return 0;
}

MATCH s32 func_801F6CFC(void) {
    return 0;
}

#include "overlays/scenario/Scene_SetPartyRyuTeepoRei.h"

MATCH void func_801F6D50(void) {
}
