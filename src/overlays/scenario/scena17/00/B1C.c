#include "scena17_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F771C(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    ORDER_LOCK(D_801F973C[index]());
}

INCLUDE_ASM(func_801F7750);

INCLUDE_ASM(func_801F77B4);

MATCH void func_801F789C(void) {
    SYS_DISPATCH_BYTE(D_801F9748, D_80146873);
}

MATCH void func_801F78D8(void) {
}

INCLUDE_ASM(func_801F78E0);

INCLUDE_ASM(func_801F7924);

INCLUDE_ASM(func_801F79AC);

INCLUDE_ASM(func_801F7A08);

INCLUDE_ASM(func_801F7A84);

INCLUDE_ASM(func_801F7B20);

INCLUDE_ASM(func_801F7B88);

INCLUDE_ASM(func_801F7BC0);

INCLUDE_ASM(func_801F7C14);

INCLUDE_ASM(func_801F7C6C);

INCLUDE_ASM(func_801F7D08);

INCLUDE_ASM(func_801F7DF4);

INCLUDE_ASM(func_801F7E9C);

INCLUDE_ASM(func_801F7F04);

INCLUDE_ASM(func_801F7F3C);

MATCH void func_801F7F94(void) {
    u8* timer;
    u8  count;

    timer  = &D_80146875;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        UI_SetMode(13);
        D_80146874 = D_80146874 + 1;
    }
}

INCLUDE_ASM(func_801F7FF0);

INCLUDE_ASM(func_801F8088);

INCLUDE_ASM(func_801F80CC);

MATCH void func_801F8110(void) {
    u8  ready;
    u8* step;

    ready = func_801F938C();
    if ((u8)SND_IsXaIdle() && ready) {
        UI_SetMode(0xD);
        step  = &D_80146874;
        *step = *step + 1;
    }
}

INCLUDE_ASM(func_801F8170);

MATCH void func_801F81BC(void) {
    SYS_DISPATCH_BYTE(D_801F97A4, g_SceneState.state_04);
}

INCLUDE_ASM(func_801F81F8);

INCLUDE_ASM(func_801F8274);

INCLUDE_ASM(func_801F82C0);

INCLUDE_ASM(func_801F833C);

MATCH void func_801F83A8(void) {
    u8* timer;
    u8  count;

    timer  = &D_80146875;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        D_80146874 = D_80146874 + 1;
    }
    func_801F8B10(0x1F4, 0xFF);
}

INCLUDE_ASM(func_801F8404);

INCLUDE_ASM(func_801F8480);

INCLUDE_ASM(func_801F84F4);

INCLUDE_ASM(func_801F8594);

INCLUDE_ASM(func_801F8664);

INCLUDE_ASM(func_801F8710);

INCLUDE_ASM(func_801F87D0);

MATCH void func_801F8844(void) {
    D_80146873            = 0;
    g_SceneState.state_04 = 0;
    CallbackReplace(func_801F9490);
}

MATCH void func_801F887C(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801F97D8[index];
    handler(entity, g_SceneFlags);
}

MATCH s32 func_801F88BC(void) {
    return 0;
}

MATCH s32 func_801F88C4(void) {
    return 0;
}

INCLUDE_ASM(func_801F88CC);

INCLUDE_ASM(func_801F8B10);

INCLUDE_ASM(func_801F8EF0);

INCLUDE_ASM(func_801F8FAC);

INCLUDE_ASM(func_801F90BC);

INCLUDE_ASM(func_801F9160);

INCLUDE_ASM(func_801F91F0);

INCLUDE_ASM(func_801F938C);

INCLUDE_ASM(func_801F9490);

INCLUDE_ASM(func_801F9504);

MATCH void func_801F9654(void) {
    Menu_RunPanelTasks();
    Shop_DispatchStep();
}

MATCH void func_801F967C(void) {
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    SND_Exit();
    CallbackReplace(SYS_StartFrontend);
}

MATCH s32 func_801F96CC(void) {
    return 0;
}

MATCH void func_801F96D4(void) {
    EMI_LoaderStreamFamily(0, 3, 4, 0);
    g_PartySize = 0;
    func_801C187C(0);
    func_801C187C(3);
    func_801C187C(4);
}

MATCH void func_801F9720(void) {
}
