#include "scena03_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6E78(void) {
    /* FAKE: retail reads the handler record from entry $v0; the pin is the
       entry-register residual (identical bytes to the unpinned 84.46%). */
    MATCH_REG(u8*, entity, "v0");

    D_801FCF24[entity[1]]();
}

MATCH void func_801F6EB4(void) {
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
    data                              = (u8*)D_801FCF30;
    slots                             = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].flags_00 = 1;
    slots                             = SP_PTR(u8*, 0u);
    work                              = slots[0x11];
    *scratch                          = work[3];
    func_801A65A0(data);
    Actor_BeginScript(0x61, 0xC);
    *scratch = work[4];
    func_801A65A0(data);
    Actor_BeginScript(0x61, 0xC);
    slots[0x11] = work;

    g_Actors[work[3]].x.fixed += ONE;
    g_Actors[work[3]].y.fixed -= ONE;
    g_Actors[work[4]].x.fixed -= ONE;
    g_Actors[work[4]].y.fixed += ONE;
    g_Actors[work[3]].flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots                                     = SP_PTR(u8*, 0u);
    cell                                      = slots[0x11];
    cell4                                     = cell[4];
    cell3                                     = cell[3];
    FIELD(u8, D_801468E4, cell4 * ACTOR_SIZE) = 0;
    FIELD(u8, D_801468E4, cell3 * ACTOR_SIZE) = 0;
    GFX_AllocPaletteFade(&g_Actors[work[3]], 0xF, 0, 0, 1);
    GFX_AllocPaletteFade(&g_Actors[work[4]], 0, 0, 0xF, 1);
    slots          = SP_PTR(u8*, 0u);
    slots[0x11][9] = 4;
    slots          = SP_PTR(u8*, 0u);
    slots[0x11][1] = 1;
}

INCLUDE_ASM(func_801F7260);

#include "shared/Actor_FreePaletteFades.h"

INCLUDE_ASM(func_801F73BC);

MATCH void func_801F7508(void) {
    SYS_DISPATCH_TASK(D_801FCF50, 1, g_SpadWork);
}

MATCH void func_801F754C(void) {
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
    data                              = (u8*)D_801FCF5C;
    slots                             = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].flags_00 = 1;
    slots                             = SP_PTR(u8*, 0u);
    work                              = slots[0x11];
    *scratch                          = work[3];
    func_801A4D54(data);
    *scratch = work[4];
    func_801A4D54(data);
    slots[0x11] = work;

    g_Actors[work[3]].x.fixed -= ONE;
    g_Actors[work[3]].y.fixed += ONE;
    g_Actors[work[4]].x.fixed += ONE;
    g_Actors[work[4]].y.fixed -= ONE;
    g_Actors[work[3]].flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots                                     = SP_PTR(u8*, 0u);
    cell                                      = slots[0x11];
    cell4                                     = cell[4];
    cell3                                     = cell[3];
    FIELD(u8, D_801468E4, cell4 * ACTOR_SIZE) = 0;
    FIELD(u8, D_801468E4, cell3 * ACTOR_SIZE) = 0;
    GFX_AllocPaletteFade(&g_Actors[work[3]], 0xF, 0, 0, 1);
    GFX_AllocPaletteFade(&g_Actors[work[4]], 0, 0, 0xF, 1);
    slots          = SP_PTR(u8*, 0u);
    slots[0x11][9] = 4;
    slots          = SP_PTR(u8*, 0u);
    slots[0x11][1] = 1;
}

MATCH void func_801F78E0(void) {
    u8* work;

    work = (u8*)g_SpadWork;
    if (work[9] != 0) {
        g_Actors[work[11]].flags_00 |= ACTOR_FLAG_HIDDEN;
        g_SpadWork->unk_09 -= 1;
    } else {
        g_Actors[work[11]].flags_00 &= ~ACTOR_FLAG_HIDDEN;
        g_Actors[g_SpadWork->unk_03].flags_00 = 0;
        g_Actors[g_SpadWork->unk_04].flags_00 = 0;
        g_SpadWork->unk_01                    = 2;
    }
}

MATCH void Actor_FreePaletteFades_801F7A14(void) {
    u8** slots;

    ACTOR_FREE_PALETTE_FADES();
}

MATCH void func_801F7A9C(void) {
    SYS_DISPATCH_TASK(D_801FCF70, 1, g_SpadWork);
}

MATCH void func_801F7AE0(void) {
    u8* work;

    work    = (u8*)g_SpadWork;
    work[9] = 0xF;
    work    = (u8*)g_SpadWork;
    work[1]++;
}

INCLUDE_ASM(func_801F7B10);

MATCH void func_801F7BB0(void) {
    Actor* actor;
    s32*   ptr;
    u8     value;

    actor = g_SpadWork;
    ptr   = &actor->unk_0C;
    func_801F7FFC(ptr);
    func_801F8170(ptr);
    actor->script_pc += 4;
    value              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = value;
    if (!(value & 0xFF)) {
        g_SpadWork->unk_09 = 8;
        g_SpadWork->unk_01 += 1;
    }
}

INCLUDE_ASM(func_801F7C50);

INCLUDE_ASM(func_801F7CE0);

INCLUDE_ASM(func_801F7D80);

MATCH void func_801F7DF0(void) {
    SYS_DISPATCH_TASK(D_801FCF88, 1, g_SpadWork);
}

MATCH void func_801F7E34(void) {
    void* work;

    SND_PlayCue(EMI_CUE_ID(2, 9));
    work                  = SP_REF(void*, 0x44);
    FIELD(u8, work, 0x1u) = (u8)(FIELD(u8, work, 0x1u) + 1);
}

INCLUDE_ASM(func_801F7E6C);

INCLUDE_ASM(func_801F7F84);

INCLUDE_ASM(func_801F7FFC);

INCLUDE_ASM(func_801F8170);

INCLUDE_ASM(func_801F8200);

MATCH void func_801F82E4(void) {
    SYS_DISPATCH_TASK(D_801FCF94, 1, g_SpadWork);
}

MATCH void func_801F8328(void) {
    g_SpadWork->unk_09 = 96;
    g_SpadWork->unk_01++;
    SND_PlayCue(516);
}

INCLUDE_ASM(func_801F8370);

MATCH void func_801F842C(void) {
    Actor_Clear();
}

MATCH void func_801F844C(void) {
    SYS_DISPATCH_TASK(D_801FCFA0, 1, g_SpadWork);
}

INCLUDE_ASM(func_801F8490);

INCLUDE_ASM(func_801F853C);

MATCH void func_801F85DC(void) {
    Actor_Clear();
}

MATCH void func_801F85FC(void) {
    SYS_DISPATCH_TASK(D_801FCFAC, 1, g_SpadWork);
}

MATCH void func_801F8640(void) {
    SVECTOR* vertex;
    u16*     screen;
    long     depth;
    long     flag;
    long     result;
    u16      other;
    u8**     slots;
    u8*      work;
    u8*      item;

    vertex                 = D_1F800014;
    screen                 = D_1F800034;
    vertex->vx             = (s16)((D_80145EC4 >> 9) - 0x4000);
    SP_REF(s16, 0x16)      = (s16)((D_80145EC8 >> 9) - 0x4000);
    SP_REF(s16, 0x18)      = (s16)((-D_80145ECE) / 2);
    result                 = RotTransPers(vertex, (long*)screen, &depth, &flag);
    slots                  = SP_PTR(u8*, 0u);
    work                   = slots[0x11];
    FIELD(s32, work, 0x60) = result;
    FIELD(u16, work, 0x2E) = screen[0];
    other                  = SP_REF(u16, 0x36);
    work[9]                = 0;
    slots                  = SP_PTR(u8*, 0u);
    item                   = slots[0x11];
    FIELD(u16, work, 0x30) = other;
    item[1] += 1;
}

MATCH void func_801F8710(void) {
    u8**   slots;
    Actor* work;
    u8*    chk;

    slots = SP_PTR(u8*, 0u);
    work  = (Actor*)slots[0x11];
    GFX_DrawShadedDisc((s16)work->unk_2E, (s16)work->unk_30, work->unk_09, 0x80, 0);
    slots = SP_PTR(u8*, 0u);
    slots[0x11][9] += 0x0F;
    slots = SP_PTR(u8*, 0u);
    chk   = slots[0x11];
    if (chk[9] >= 0x3D) {
        chk[9] = 0xFF;
        slots  = SP_PTR(u8*, 0u);
        slots[0x11][1] += 1;
    }
}

MATCH void func_801F87A4(void) {
    u8**   slots;
    Actor* work;
    u8*    chk;
    u8     count;

    slots = SP_PTR(u8*, 0u);
    work  = (Actor*)slots[0x11];
    GFX_DrawShadedDisc((s16)work->unk_2E, (s16)work->unk_30, (work->unk_09 & 1) | 0x3C, 0x80, 0);
    slots = SP_PTR(u8*, 0u);
    if (slots[0x11][9] == 0xD7) {
        SND_PlayCue(EMI_CUE_ID(2, 8));
    }
    slots  = SP_PTR(u8*, 0u);
    chk    = slots[0x11];
    count  = (u8)(chk[9] - 1);
    chk[9] = count;
    if (count == 0) {
        slots          = SP_PTR(u8*, 0u);
        slots[0x11][9] = 0x3C;
        slots          = SP_PTR(u8*, 0u);
        slots[0x11][1] += 1;
    }
}

MATCH void func_801F885C(void) {
    u8**   slots;
    Actor* work;
    s8*    chk;

    slots = SP_PTR(u8*, 0u);
    work  = (Actor*)slots[0x11];
    GFX_DrawShadedDisc((s16)work->unk_2E, (s16)work->unk_30, work->unk_09, 0x80, 0);
    slots = SP_PTR(u8*, 0u);
    slots[0x11][9] -= 1;
    slots = SP_PTR(u8*, 0u);
    chk   = (s8*)slots[0x11];
    if (chk[9] < 0) {
        slots = SP_PTR(u8*, 0u);
        slots[0x11][1] += 1;
    }
}

MATCH void func_801F88DC(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F88FC);

#include "shared/GFX_DrawShadedDisc.h"

MATCH void func_801F8DA8(void) {
    SYS_DISPATCH_BYTE(D_801FCFD4, D_80146872);
}

MATCH void func_801F8DE4(void) {
    D_80146872 = 1;
    D_80144EA0 = 0;
}

INCLUDE_ASM(func_801F8E00);

MATCH void func_801F92F4(void) {
    SYS_DISPATCH_BYTE(D_801FCFE0, g_SceneState.state_04);
}

MATCH void func_801F9330(void) {
}

INCLUDE_ASM(func_801F9338);

INCLUDE_ASM(func_801F97F8);

INCLUDE_ASM(func_801F9880);

INCLUDE_ASM(func_801FA0A4);

INCLUDE_ASM(func_801FA34C);

INCLUDE_ASM(func_801FABA8);

INCLUDE_ASM(func_801FB268);

INCLUDE_ASM(func_801FB8A4);

INCLUDE_ASM(func_801FC1D0);

INCLUDE_ASM(func_801FC3B4);

INCLUDE_ASM(func_801FC410);

MATCH void func_801FC46C(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FD00C[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FC4AC(void* entity, void* bits) {
    Game_SetScriptActive();
    SYS_SetFlag(bits, 0x14U);
    g_SceneState.state_04 = 4;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FC4F4(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x10);
}

MATCH void func_801FC520(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x11);
}

MATCH void func_801FC54C(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x12);
}

MATCH void func_801FC578(void* entity, void* flags) {
    Scene_SetFlagThenContinue(flags, 0x13);
}

INCLUDE_ASM(func_801FC5A4);

MATCH void func_801FC5FC(void) {
    Party_AddVitalItem(1);
    Message_StartAreaMessage(0x2F);
    g_GameStateIndex = 2;
    SND_PauseBgm((s32)g_SndBgmId);
    SND_StartXaStream(2, 1);
    while (!(SND_IsXaIdle() & 0xFF)) {
        func_801992B8();
        CallbackWait(1U);
    }
    SND_ResumeBgm((s32)g_SndBgmId);
}

MATCH void func_801FC688(void) {
}

MATCH s32 func_801FC690(void) {
    /* FAKE: retail materializes the action code in v1. */
    MATCH_REG(s32, action, "v1");

    Game_SetScriptActive();
    action     = 6;
    D_80146874 = action;
    D_80146875 = 0;
    return 0;
}

INCLUDE_ASM(func_801FC6C4);

INCLUDE_ASM(func_801FC704);

INCLUDE_ASM(func_801FC7EC);

MATCH s32 func_801FC8AC(s32 arg0, s32 arg1) {
    if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
        if ((u32)((arg1 >> 0x10) - 7) < 2U) {
            if (arg0 == 0x5C0000) {
                SYS_SetFlag(g_SceneFlags, 7U);
                D_80146874 = 3;
                D_80146875 = 0xA;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

MATCH s8 func_801FC944(s32 arg0, s32 arg1) {
    if (SYS_TestFlag(g_SceneFlags, 0x15) == 0) {
        if (arg1 == 0x418000) {
            if ((u32)((arg0 >> 0x10) - 0x20) < 4U) {
                D_80146874 = 4;
                D_80146875 = 5;
                return Scene_ShowMessage(0x33);
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM(func_801FC9DC);

MATCH s8 func_801FCAB8(s32 arg0, s32 arg1) {
    if (SYS_TestFlag(g_SceneFlags, 0x1A) != 0) {
        if ((arg0 >> 0x10) == 0x15) {
            if ((u32)((arg1 >> 0x10) - 0x34) < 2U) {
                D_80146874 = 5;
                D_80146875 = 0x10;
                return Scene_ShowMessage(0x1F);
            }
        }
    }
    return 0;
}

INCLUDE_ASM(func_801FCB4C);

#include "overlays/scenario/Scene_ShowMessage.h"

INCLUDE_ASM(func_801FCCDC);

INCLUDE_ASM(func_801FCD1C);

INCLUDE_ASM(func_801FCDB4);

MATCH void func_801FCE18(void) {
    Message_StartAreaMessage(25);
    g_GameStateIndex = 2;
    Game_SetScriptActive();
    D_80146876 = 30;
    D_80146874 = 7;
    D_80146875 = 0;
}

MATCH void func_801FCE6C(void) {
    EMI_LoaderStreamFamily(0, 1, 2, 0);
    D_80144F5A[0] = 255;
    D_80144F5B    = 255;
    D_80144F5C    = 255;
    D_80144F5D[0] = 255;
    D_80144F5E[0] = 255;
    D_80144F5F    = 255;
    g_PartySize   = 0;
    Party_JoinMember(0);
}

MATCH void func_801FCEDC(void) {
    Party_JoinMember(1);
}

#include "overlays/scenario/Scene_RemoveNina.h"
