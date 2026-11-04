#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6EAC(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FBEF0[entity[1]]();
}

MATCH void func_801F6EE8(void) {
    u8* first;
    u8* second;
    u8* third;

    first       = (u8*)g_SpadWork;
    first[0x5F] = 0;
    first[0x5E] = 0;
    first[0x5D] = 0;

    second    = (u8*)g_SpadWork;
    second[9] = 0x0F;

    third    = (u8*)g_SpadWork;
    third[1] = 1;
}

INCLUDE_ASM(func_801F6F24);

MATCH void func_801F6FD0(void) {
    func_801F6FF8();
    func_801F70DC();
}

INCLUDE_ASM(func_801F6FF8);

MATCH void func_801F70DC(void) {
    Actor* temp_s1;
    Actor* temp_v1;
    s32    var_s0;

    temp_s1 = g_SpadWork;
    var_s0  = 0;
    do {
        temp_v1    = &g_Actors[var_s0 & 0xFF];
        g_SpadWork = temp_v1;
        if ((temp_v1->flags_00 & 1) && (temp_v1->unk_06 == 6)) {
            temp_v1->unk_29 = 5;
            func_8014D290();
        }
        var_s0 += 1;
    } while ((u32)(var_s0 & 0xFF) < 0x1EU);
    g_SpadWork = temp_s1;
}

MATCH void func_801F7198(void) {
    SYS_DISPATCH_TASK(D_801FBEFC, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F71DC);

INCLUDE_ASM(func_801F7248);

INCLUDE_ASM(func_801F72A0);

INCLUDE_ASM(func_801F735C);

MATCH void func_801F7444(void) {
    if (g_ScriptVars[0] == 0x35) {
        Actor_Clear();
    }
    func_801F7484();
    func_801F7568();
}

INCLUDE_ASM(func_801F7484);

INCLUDE_ASM(func_801F7568);

MATCH void func_801F75F8(void) {
    SYS_DISPATCH_TASK(D_801FBF10, 1, g_SpadWork);
}

MATCH void func_801F763C(void) {
    u8** slots;
    u8*  work;
    u8*  data;
    u8*  cell;
    u8   cell4;
    u32  cell3;
    s16* scratch;

    slots          = SP_PTR(u8*, 0u);
    slots[0x11][3] = Actor_FindFree();
    slots          = SP_PTR(u8*, 0u);
    if (slots[0x11][3] == GAME_NONE) {
        return;
    }

    slots                             = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][3]].flags_00 = 1;
    slots                             = SP_PTR(u8*, 0u);
    slots[0x11][4]                    = Actor_FindFree();
    slots                             = SP_PTR(u8*, 0u);
    if (slots[0x11][4] == GAME_NONE) {
        slots                             = SP_PTR(u8*, 0u);
        g_Actors[slots[0x11][3]].flags_00 = 0;
        return;
    }

    scratch                           = (s16*)D_1F800000;
    data                              = (u8*)D_801FBF20;
    slots                             = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].flags_00 = 1;
    slots                             = SP_PTR(u8*, 0u);
    work                              = slots[0x11];
    *scratch                          = work[3];
    func_801A4D54(data);
    *scratch = work[4];
    func_801A4D54(data);
    slots[0x11] = work;

    g_Actors[work[3]].y.fixed -= 0x10000;
    g_Actors[work[4]].y.fixed += 0x10000;
    g_Actors[work[3]].flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots                                     = SP_PTR(u8*, 0u);
    cell                                      = slots[0x11];
    cell4                                     = cell[4];
    cell3                                     = cell[3];
    FIELD(u8, D_801468E4, cell4 * ACTOR_SIZE) = 1;
    FIELD(u8, D_801468E4, cell3 * ACTOR_SIZE) = 1;
    GFX_AllocPaletteFade(&g_Actors[work[3]], 0xF, 0, 0, 1);
    GFX_AllocPaletteFade(&g_Actors[work[4]], 0, 0, 0xF, 1);
    slots          = SP_PTR(u8*, 0u);
    slots[0x11][9] = 0x20;
    slots          = SP_PTR(u8*, 0u);
    slots[0x11][1] = 1;
}

INCLUDE_ASM(func_801F7958);

INCLUDE_ASM(func_801F7A1C);

INCLUDE_ASM(func_801F7C24);

MATCH void func_801F7D14(void) {
    SYS_DISPATCH_BYTE(D_801FBF48, D_80146872);
}

MATCH void func_801F7D50(void) {
    Game_SetScriptActive();
    g_AreaDrawFlags = 31;
    func_801C16B8();
    func_801C1DF0(0);
    SYS_SetFlag(g_SceneEventFlags, 67);
    SYS_ClearFlag(g_SceneEventFlags, 66);
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7DBC);

MATCH void func_801F8474(void) {
    SYS_DISPATCH_BYTE(D_801FBF54, g_SceneState.state_04);
}

MATCH void func_801F84B0(void) {
}

INCLUDE_ASM(func_801F84B8);

INCLUDE_ASM(func_801F873C);

INCLUDE_ASM(func_801F8C1C);

INCLUDE_ASM(func_801F8D0C);

INCLUDE_ASM(func_801F8DFC);

INCLUDE_ASM(func_801F9570);

INCLUDE_ASM(func_801F9A44);

INCLUDE_ASM(func_801F9E70);

INCLUDE_ASM(func_801F9F18);

INCLUDE_ASM(func_801FA844);

INCLUDE_ASM(func_801FAFA0);

#include "overlays/scenario/GFX_CopyPaletteCapped.h"

MATCH void func_801FB164(void) {
    s32 i;

    i = 0;
    do {
        g_GraphicsPaletteDst[i] = MEM_PTR(const volatile u16, 0x80033800u)[i];
        i++;
    } while (i < 16);
    g_GfxPalettePending = (u8)(g_GfxPalettePending + 1u);
}

INCLUDE_ASM(func_801FB1B4);

MATCH void func_801FB350(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FBFB8[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FB390(void* entity) {
    ((Actor*)entity)->unk_7E = (u16)(((Actor*)entity)->unk_7E + 1);
}

MATCH void func_801FB3A4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 5;
}

MATCH void func_801FB3DC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0x19;
}

MATCH void func_801FB414(void) {
    SYS_SetFlag(g_SceneFlags, 28);
    Game_SetScriptActive();
    D_801448EB = 44;
    D_801448EC = 0;
    D_801448ED = 17;
}

INCLUDE_ASM(func_801FB464);

INCLUDE_ASM(func_801FBA34);

MATCH void func_801FBB78(void) {
    EMI_LoaderStreamFamily(7, 5, 6, 0);
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(6);
    Party_JoinMember(5);
}

INCLUDE_ASM(func_801FBBC4);

MATCH void func_801FBC88(void) {
    EMI_LoaderStreamFamily(7U, 5U, 8U, 0U);
    g_PartySize = 0;
    Party_JoinMember(7);
}

INCLUDE_ASM(func_801FBCC4);

MATCH void func_801FBD84(void) {
    EMI_LoaderStreamFamily(7, 5, 8, 0);
    g_PartySize = 0;
    Party_JoinMember(7);
    Party_JoinMember(5);
    Party_JoinMember(8);
    func_801C1630();
}

INCLUDE_ASM(func_801FBDD8);

MATCH void func_801FBE98(void) {
    Party_JoinMember(4);
    func_801C1630();
}

MATCH void func_801FBEC0(void) {
    Party_JoinMember(2);
    func_801C1630();
}

MATCH void func_801FBEE8(void) {
}
