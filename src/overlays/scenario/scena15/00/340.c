#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6F40(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FE57C[entity[1]]();
}

MATCH void func_801F6F7C(void) {
    Actor* work;

    work         = (Actor*)g_SpadWork;
    work->unk_2E = 640;
    work->unk_30 = 1536;
    work->unk_09 = 0;
    Area_ClearWorkColumn();
    ((Actor*)g_SpadWork)->unk_01 = ((Actor*)g_SpadWork)->unk_01 + 1;
}

INCLUDE_ASM(func_801F6FCC);

INCLUDE_ASM(func_801F7078);

INCLUDE_ASM(func_801F7100);

MATCH void func_801F717C(void) {
    if (!(func_801F7748() & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F71B0);

INCLUDE_ASM(func_801F752C);

#include "shared/Area_ClearWorkColumn.h"

INCLUDE_ASM(func_801F75D8);

INCLUDE_ASM(func_801F7748);

MATCH void func_801F77F8(void) {
    SYS_DISPATCH_TASK(D_801FE590, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F783C);

MATCH void func_801F7900(void) {
    func_801F79C4();
}

INCLUDE_ASM(func_801F7920);

MATCH void func_801F79BC(void) {
}

INCLUDE_ASM(func_801F79C4);

MATCH void func_801F7AA8(void) {
    SYS_DISPATCH_TASK(D_801FE5A0, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F7AEC);

INCLUDE_ASM(func_801F7D1C);

INCLUDE_ASM(func_801F7E2C);

INCLUDE_ASM(func_801F7F5C);

INCLUDE_ASM(func_801F7FFC);

INCLUDE_ASM(func_801F81D8);

INCLUDE_ASM(func_801F83AC);

MATCH void func_801F8488(void) {
    SYS_DISPATCH_TASK(D_801FE5B0, 1, g_SpadWork);
}

/* The statements of func_801F84CC and func_801F87F8, byte-identical twins: set +0x29 of every party battler row to 3,
 * clear the three tint bytes of the current work and move it to step 1. Each member declares work and i. Every change
 * here must verify both members. */
#define SCENA15_PARTY_SETUP()                \
    work = g_SpadWork;                       \
    for (i = 0; i < g_PartySize; i++) {      \
        g_BattlePartyBattlers[i].unk_29 = 3; \
    }                                        \
    g_SpadWork              = work;          \
    work->tint.bytes.unk_5F = 0;             \
    work->tint.bytes.unk_5E = 0;             \
    work->tint.bytes.unk_5D = 0;             \
    g_SpadWork->unk_01      = 1

MATCH void func_801F84CC(void) {
    Actor* work;
    u8     i;

    SCENA15_PARTY_SETUP();
}

INCLUDE_ASM(func_801F8548);

MATCH void func_801F85F0(void) {
    func_801F79C4();
    func_801F8704();
}

INCLUDE_ASM(func_801F8618);

INCLUDE_ASM(func_801F8704);

MATCH void func_801F87B4(void) {
    SYS_DISPATCH_TASK(D_801FE5C0, 1, g_SpadWork);
}

MATCH void func_801F87F8(void) {
    Actor* work;
    u8     i;

    SCENA15_PARTY_SETUP();
}

INCLUDE_ASM(func_801F8874);

MATCH void func_801F8930(void) {
    func_801F79C4();
    func_801F8958();
}

INCLUDE_ASM(func_801F8958);

MATCH void func_801F8A5C(void) {
    SYS_DISPATCH_TASK(D_801FE5CC, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F8AA0);

INCLUDE_ASM(func_801F8BC4);

INCLUDE_ASM(func_801F8C78);

INCLUDE_ASM(func_801F8D30);

INCLUDE_ASM(func_801F8EA8);

INCLUDE_ASM(func_801F8F4C);

MATCH void func_801F9000(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F9020);

INCLUDE_ASM(func_801F92F0);

INCLUDE_ASM(func_801F9500);

INCLUDE_ASM(func_801F97CC);

INCLUDE_ASM(func_801F9A20);

MATCH void func_801F9CAC(void) {
    SYS_DISPATCH_BYTE(D_801FE66C, D_80146872);
}

MATCH void func_801F9CE8(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F9CFC);

INCLUDE_ASM(func_801FA6BC);

INCLUDE_ASM(func_801FA854);

MATCH void func_801FA998(void) {
    SYS_DISPATCH_BYTE(D_801FE678, g_SceneState.state_04);
}

MATCH void func_801FA9D4(void) {
}

INCLUDE_ASM(func_801FA9DC);

INCLUDE_ASM(func_801FADFC);

INCLUDE_ASM(func_801FAFA8);

INCLUDE_ASM(func_801FB788);

INCLUDE_ASM(func_801FC100);

INCLUDE_ASM(func_801FC1D8);

INCLUDE_ASM(func_801FCA3C);

INCLUDE_ASM(func_801FCBAC);

INCLUDE_ASM(func_801FDB84);

INCLUDE_ASM(func_801FDC10);

INCLUDE_ASM(func_801FDC6C);

MATCH void func_801FDD80(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FE6EC[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FDDC0(void* entity) {
    u8 message;

    message = D_801FE71C[((Actor*)entity)->callback_index];
    if (g_GameAreaId == 0xC0) {
        Message_StartAreaMessage(func_801F326C(message));
    } else {
        Message_StartAreaMessage(func_801F37AC(message));
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
}

MATCH void func_801FDE2C(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 0x32;
}

INCLUDE_ASM(func_801FDE64);

INCLUDE_ASM(func_801FDEB4);

INCLUDE_ASM(func_801FDF04);

INCLUDE_ASM(func_801FDF4C);

INCLUDE_ASM(func_801FDF9C);

MATCH void func_801FDFEC(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    actor->unk_7E = (u16)(actor->unk_7E + 1);
}

INCLUDE_ASM(func_801FE024);

INCLUDE_ASM(func_801FE18C);

INCLUDE_ASM(func_801FE3C8);

MATCH void func_801FE49C(void) {
    Party_JoinMember(4);
    Party_JoinMember(2);
    func_801C1630();
}

MATCH void func_801FE4CC(void) {
    EMI_LoaderStreamFamily(7, 8, 2, 0);
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(8);
    Party_JoinMember(2);
    func_801C1630();
}

MATCH void func_801FE520(void) {
    EMI_LoaderStreamFamily(7, 8, 4, 0);
    g_PartySize = 0;
    func_801C187C(7);
    func_801C187C(8);
    func_801C187C(4);
    func_801C1630();
}

MATCH void func_801FE574(void) {
}
