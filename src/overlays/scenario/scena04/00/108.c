#include "scena04_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6D08(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FA180[entity[1]]();
}

INCLUDE_ASM(func_801F6D44);

INCLUDE_ASM(func_801F6DD4);

INCLUDE_ASM(func_801F6EA4);

INCLUDE_ASM(func_801F6F2C);

INCLUDE_ASM(func_801F6FF8);

MATCH void func_801F7064(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F7084);

INCLUDE_ASM(func_801F732C);

INCLUDE_ASM(func_801F747C);

INCLUDE_ASM(func_801F75BC);

MATCH void func_801F77A8(void) {
    SYS_DISPATCH_TASK(D_801FA198, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F77EC);

INCLUDE_ASM(func_801F78F4);

MATCH void func_801F7A64(void) {
    Actor_Clear();
}

MATCH void func_801F7A84(void) {
    SYS_DISPATCH_TASK(D_801FA1E4, 1, g_SpadWork);
}

MATCH void func_801F7AC8(void) {
    Actor* work;

    func_801F7FCC();
    work = (Actor*)g_SpadWork;
    work->unk_01 += 1;
}

INCLUDE_ASM(func_801F7B00);

INCLUDE_ASM(func_801F7BC0);

INCLUDE_ASM(func_801F7CA8);

INCLUDE_ASM(func_801F7CF0);

INCLUDE_ASM(func_801F7EC0);

MATCH void func_801F7FCC(void) {
    s32   index;
    void* cell;

    cell  = (void*)AREA_WORK_WINDOW;
    index = 0;
    do {
        FIELD(s8, cell, 0x25u) = 0;
        index += 1;
        cell += 0x28;
    } while ((u32)(index & BYTE_MASK) < 0x80U);
}

INCLUDE_ASM(func_801F7FF8);

INCLUDE_ASM(func_801F8034);

MATCH void func_801F8124(void) {
    SYS_DISPATCH_BYTE(D_801FA204, D_80146872);
}

MATCH void func_801F8160(void) {
    D_80146872 = 1;
    D_80144EA8 = 0;
}

INCLUDE_ASM(func_801F817C);

MATCH void func_801F863C(void) {
    SYS_DISPATCH_BYTE(D_801FA210, g_SceneState.state_04);
}

MATCH void func_801F8678(void) {
}

INCLUDE_ASM(func_801F8680);

INCLUDE_ASM(func_801F8F98);

MATCH void func_801F9CFC(void) {
    s32 offset = D_801FA220[(g_FrameCount >> 1) & 3];

    g_AreaViewRefreshCount = 2;
    g_AreaCameraHeight += offset * 4;
}

MATCH void func_801F9D48(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FA224[index];
    handler(entity, g_SceneFlags);
}

INCLUDE_ASM(func_801F9D88);

MATCH s32 func_801F9DAC(void) {
    return 0;
}

MATCH s32 func_801F9DB4(void) {
    if (g_GameAreaId == 40) {
        return func_801F9DF4();
    }
    return 0;
}

INCLUDE_ASM(func_801F9DF4);

#include "overlays/scenario/Scene_ShowMessage.h"

INCLUDE_ASM(func_801FA010);

MATCH void func_801FA074(void) {
    Game_SetScriptActive();
    g_SceneState.timer_06 = 0xA;
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FA0B4(void) {
    EMI_LoaderStreamFamily(0, 1, 5, 0);
    D_80144F5A    = 255;
    D_80144F5B    = 255;
    D_80144F5C    = 255;
    D_80144F5D[0] = 255;
    D_80144F5E    = 255;
    D_80144F5F    = 255;
    g_PartySize   = 0;
    Party_JoinMember(0);
    Party_JoinMember(1);
}

MATCH void func_801FA12C(void) {
    EMI_LoaderStreamFamily(0, 1, 5, 0);
    g_PartySize = 0;
    func_801C187C(0);
    func_801C187C(1);
    func_801C187C(5);
}

MATCH void func_801FA178(void) {
}
