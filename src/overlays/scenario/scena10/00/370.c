#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6F70(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FE80C[entity[1]]();
}

INCLUDE_ASM(func_801F6FAC);

INCLUDE_ASM(func_801F7068);

INCLUDE_ASM(func_801F719C);

INCLUDE_ASM(func_801F73EC);

MATCH void func_801F74F8(void) {
    Actor_Clear();
}

MATCH void func_801F7518(void) {
    SYS_DISPATCH_TASK(D_801FE820, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F755C);

INCLUDE_ASM(func_801F7590);

INCLUDE_ASM(func_801F7758);

INCLUDE_ASM(func_801F781C);

INCLUDE_ASM(func_801F79E8);

INCLUDE_ASM(func_801F7AD4);

INCLUDE_ASM(func_801F7C34);

INCLUDE_ASM(func_801F7DDC);

MATCH void func_801F7F50(void) {
    SYS_DISPATCH_BYTE(D_801FE8F4, D_80146872);
}

MATCH void func_801F7F8C(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7FA0);

INCLUDE_ASM(func_801F8550);

MATCH void func_801F8694(void) {
    SYS_DISPATCH_BYTE(D_801FE900, g_SceneState.state_04);
}

MATCH void func_801F86D0(void) {
}

INCLUDE_ASM(func_801F86D8);

INCLUDE_ASM(func_801F8C00);

INCLUDE_ASM(func_801F95B8);

MATCH void func_801F9FC4(void) {
    D_1F800000.view.area.entity_counter = Actor_FindFree();
    if (D_1F800000.view.area.entity_counter != 0xFF) {
        func_801A4D54(D_801FE938);
    }
}

INCLUDE_ASM(func_801FA010);

INCLUDE_ASM(func_801FA5EC);

/* Tests D_80144908 >= 2, D_8014490A >= 3, D_8014490B >= 2, D_8014490D != 0 in turn and returns D_8014490F >= 2, else 0.
 * Five shapes (one condition, nested ifs, early returns, a result local) put the first lui in v0; retail uses v1 and
 * keeps the 0 result in v0 from the first branch delay slot. */
INCLUDE_ASM(func_801FA644);

INCLUDE_ASM(func_801FA6BC);

INCLUDE_ASM(func_801FA98C);

INCLUDE_ASM(func_801FC220);

INCLUDE_ASM(func_801FC280);

INCLUDE_ASM(func_801FC830);

INCLUDE_ASM(func_801FC8A0);

INCLUDE_ASM(func_801FC900);

INCLUDE_ASM(func_801FCD80);

MATCH u16 func_801FD278(void) {
    SCENA10_PARTY_LOOKUP(4, D_801FE950, D_801FE954, 0);
}

MATCH u16 func_801FD31C(void) {
    SCENA10_PARTY_LOOKUP(5, D_801FE95C, D_801FE964, 0);
}

MATCH u16 func_801FD3C0(void) {
    SCENA10_PARTY_LOOKUP(3, D_801FE970, D_801FE974, 0xFFFF);
}

MATCH void func_801FD464(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FE97C[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FD4A4(void) {
    Game_SetScriptActive();
    func_801BE1B0(1);
}

MATCH void func_801FD4CC(void) {
    Game_SetScriptActive();
    func_801BE1B0(4);
}

MATCH void func_801FD4F4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FD528(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 0xA;
    g_ScriptVars[0]       = 0xA;
}

INCLUDE_ASM(func_801FD568);

INCLUDE_ASM(func_801FD5C0);

INCLUDE_ASM(func_801FD734);

INCLUDE_ASM(func_801FD814);

INCLUDE_ASM(func_801FD95C);

INCLUDE_ASM(func_801FD9B4);

INCLUDE_ASM(func_801FDA0C);

MATCH void func_801FDA74(void) {
    SYS_SetFlag(g_SceneFlags, 0x19U);
}

MATCH void func_801FDA9C(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xA;
    g_SceneState.step_05  = 1;
}

MATCH void func_801FDAD4(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xD;
    g_SceneState.step_05  = 5;
}

INCLUDE_ASM(func_801FDB14);

INCLUDE_ASM(func_801FE00C);

INCLUDE_ASM(func_801FE2B0);

MATCH void func_801FE314(void) {
    EMI_LoaderStreamFamily(7, 2, 8, 0);
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(2);
    Party_JoinMember(8);
}

MATCH void func_801FE360(void) {
    u8 i;

    for (i = 0; i < g_PartySize; i++) {
        func_801C1ABC(g_BattlePartyBattlers[i].stats.character_id);
    }
    EMI_LoaderStreamFamily(7, 5, 8, 0);
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(5);
}

MATCH void func_801FE3F8(void) {
    Party_JoinMember(8);
}

MATCH void func_801FE418(void) {
    Party_JoinMember(5);
}

INCLUDE_ASM(func_801FE438);

#include "overlays/scenario/Scene_RebuildTrioParty.h"

INCLUDE_ASM(func_801FE5B0);

#include "overlays/scenario/Scene_RemoveMomo.h"

INCLUDE_ASM(func_801FE63C);

/* Copies the first g_PartySize character ids into D_80144908 and a local ids[3], then func_801C1ABC on every id except 7, then func_801C1630. The C is exact except retail's frame is 0x28 (ids at sp+0x10, s0 at 0x18) against 0x30 here, whatever the ids size or declaration order (first differing instruction +0x8: addiu sp,sp,-40). */
INCLUDE_ASM(func_801FE6F4);
