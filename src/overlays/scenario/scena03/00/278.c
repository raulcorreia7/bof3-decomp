#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6E78(void) {
    u8* entity;

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

    slots                                 = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][3]].header.flags = 1;
    slots                                 = SP_PTR(u8*, 0u);
    slots[0x11][4]                        = Actor_FindFree();
    slots                                 = SP_PTR(u8*, 0u);
    if (slots[0x11][4] == GAME_NONE) {
        slots                                 = SP_PTR(u8*, 0u);
        g_Actors[slots[0x11][3]].header.flags = 0;
        return;
    }

    scratch                               = (s16*)D_1F800000;
    data                                  = (u8*)D_801FCF30;
    slots                                 = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].header.flags = 1;
    slots                                 = SP_PTR(u8*, 0u);
    work                                  = slots[0x11];
    *scratch                              = work[3];
    func_801A65A0(data);
    Actor_BeginScript(0x61, 0xC);
    *scratch = work[4];
    func_801A65A0(data);
    Actor_BeginScript(0x61, 0xC);
    slots[0x11] = work;

    g_Actors[work[3]].pos.x.fixed += ONE;
    g_Actors[work[3]].pos.y.fixed -= ONE;
    g_Actors[work[4]].pos.x.fixed -= ONE;
    g_Actors[work[4]].pos.y.fixed += ONE;
    g_Actors[work[3]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
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

MATCH void func_801F7260(void) {
    if (g_Task->timer != 0) {
        g_Game.members->header.flags |= 0x40;
        g_Task->timer -= 1;
        return;
    }
    g_Game.members->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Actors[g_Task->unk_03].header.flags = 0;
    g_Actors[g_Task->unk_04].header.flags = 0;
    g_Task->header.mode                   = 2;
}

#include "shared/Actor_FreePaletteFades.h"

MATCH void func_801F73BC(void) {
    RECT     rect;
    DR_MOVE* prim;

    if (g_Task->timer == 0) {
        prim   = (DR_MOVE*)g_GfxPrimCursor;
        rect.x = *(&D_801FCF40 + g_Task->header.mode * 2) / 4 + 0x2C0;
        rect.y = *(&D_801FCF42 + g_Task->header.mode * 2) + 0x100;
        rect.w = 0x10;
        rect.h = 0x28;
        SetDrawMove(prim, &rect, D_801FCF40 / 4 + 0x2C0, D_801FCF42 + 0x100);
        g_Task->header.mode++;
        g_Task->unk_29 = 0;
        g_Task->timer  = g_Task->header.mode;
        GFX_AddPrim(g_Task->unk_29, sizeof(DR_MOVE));
        if (g_Task->header.mode == 4) {
            func_80196070();
        }
    } else {
        g_Task->timer--;
    }
}

MATCH void func_801F7508(void) {
    SYS_DISPATCH_TASK(D_801FCF50, 1, g_Task);
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

    slots                                 = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][3]].header.flags = 1;
    slots                                 = SP_PTR(u8*, 0u);
    slots[0x11][4]                        = Actor_FindFree();
    slots                                 = SP_PTR(u8*, 0u);
    if (slots[0x11][4] == GAME_NONE) {
        slots                                 = SP_PTR(u8*, 0u);
        g_Actors[slots[0x11][3]].header.flags = 0;
        return;
    }

    scratch                               = (s16*)D_1F800000;
    data                                  = (u8*)D_801FCF5C;
    slots                                 = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].header.flags = 1;
    slots                                 = SP_PTR(u8*, 0u);
    work                                  = slots[0x11];
    *scratch                              = work[3];
    func_801A4D54(data);
    *scratch = work[4];
    func_801A4D54(data);
    slots[0x11] = work;

    g_Actors[work[3]].pos.x.fixed -= ONE;
    g_Actors[work[3]].pos.y.fixed += ONE;
    g_Actors[work[4]].pos.x.fixed += ONE;
    g_Actors[work[4]].pos.y.fixed -= ONE;
    g_Actors[work[3]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    slots = SP_PTR(u8*, 0u);
    g_Actors[slots[0x11][4]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
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

#include "shared/Actor_Reveal.h"

MATCH void Actor_FreePaletteFades2(void) {
    u8** slots;

    ACTOR_FREE_PALETTE_FADES();
}

MATCH void func_801F7A9C(void) {
    SYS_DISPATCH_TASK(D_801FCF70, 1, g_Task);
}

MATCH void func_801F7AE0(void) {
    u8* work;

    work    = (u8*)g_Task;
    work[9] = 0xF;
    work    = (u8*)g_Task;
    work[1]++;
}

MATCH void func_801F7B10(void) {
    Actor* actor;
    s32*   ptr;
    u8     value;

    actor = g_Task;
    ptr   = &actor->vx;
    func_801F7FFC(ptr);
    func_801F8170(ptr);
    actor->tint.halves.unk_5E += 1;
    value         = g_Task->timer - 1;
    g_Task->timer = value;
    if (!(value & BYTE_MASK)) {
        g_Task->timer = 8;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F7BB0(void) {
    Actor* actor;
    s32*   ptr;
    u8     value;

    actor = g_Task;
    ptr   = &actor->vx;
    func_801F7FFC(ptr);
    func_801F8170(ptr);
    actor->script_pc += 4;
    value         = g_Task->timer - 1;
    g_Task->timer = value;
    if (!(value & BYTE_MASK)) {
        g_Task->timer = 8;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F7C50(void) {
    s32* temp_s0;
    u8   temp_v0;

    temp_s0 = &g_Task->vx;
    func_801F7FFC(temp_s0);
    func_801F8170(temp_s0);
    temp_v0       = g_Task->timer - 1;
    g_Task->timer = temp_v0;
    if (!(temp_v0 & BYTE_MASK)) {
        g_Task->timer = 0x80;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F7CE0(void) {
    Actor* work;
    s32*   pos;
    u8     remaining;

    work = g_Task;
    pos  = &work->vx;
    func_801F7FFC(pos);
    func_801F8170(pos);
    work->unk_5A -= 8;
    work->tint.halves.unk_5C -= 0x40;
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F7D80(void) {
    Actor* work;
    s32*   pos;
    s16    step;

    work = g_Task;
    pos  = &work->vx;
    func_801F7FFC(pos);
    func_801F8170(pos);
    step            = work->script_pc - 8;
    work->script_pc = step;
    if (step < 0) {
        g_Task->unk_06 = 1;
        Actor_Clear();
    }
}

MATCH void func_801F7DF0(void) {
    SYS_DISPATCH_TASK(D_801FCF88, 1, g_Task);
}

MATCH void func_801F7E34(void) {
    void* work;

    SND_PlayCue(EMI_CUE_ID(2, 9));
    work                  = SP_REF(void*, 0x44);
    FIELD(u8, work, 0x1u) = (FIELD(u8, work, 0x1u) + 1);
}

INCLUDE_ASM(func_801F7E6C);

INCLUDE_ASM(func_801F7F84);

INCLUDE_ASM(func_801F7FFC);

INCLUDE_ASM(func_801F8170);

INCLUDE_ASM(func_801F8200);

MATCH void func_801F82E4(void) {
    SYS_DISPATCH_TASK(D_801FCF94, 1, g_Task);
}

MATCH void func_801F8328(void) {
    g_Task->timer = 96;
    g_Task->header.mode++;
    SND_PlayCue(EMI_CUE_ID(2, 4));
}

MATCH void func_801F8370(void) {
    ActorSlot* temp_v0;
    s32        temp_v1;
    u8         temp_v0_2;

    if (g_Task->timer & 4) {
        temp_v1 = func_8019601C() & BYTE_MASK;
        if (temp_v1 != 0xFF) {
            temp_v0               = &g_ActorSlots[temp_v1];
            temp_v0->header.flags = 1;
            temp_v0->type         = 0x24;
        }
    }
    temp_v0_2     = g_Task->timer - 1;
    g_Task->timer = temp_v0_2;
    if (!(temp_v0_2 & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F842C(void) {
    Actor_Clear();
}

MATCH void func_801F844C(void) {
    SYS_DISPATCH_TASK(D_801FCFA0, 1, g_Task);
}

INCLUDE_ASM(func_801F8490);

INCLUDE_ASM(func_801F853C);

MATCH void func_801F85DC(void) {
    Actor_Clear();
}

MATCH void func_801F85FC(void) {
    SYS_DISPATCH_TASK(D_801FCFAC, 1, g_Task);
}

#include "shared/Actor_TrackFocus.h"

MATCH void func_801F8710(void) {
    u8**   slots;
    Actor* work;
    u8*    chk;

    slots = SP_PTR(u8*, 0u);
    work  = (Actor*)slots[0x11];
    GFX_DrawShadedDisc((s16)work->screen_x, (s16)work->screen_y, work->timer, 0x80, 0);
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
    GFX_DrawShadedDisc((s16)work->screen_x, (s16)work->screen_y, (work->timer & 1) | 0x3C, 0x80, 0);
    slots = SP_PTR(u8*, 0u);
    if (slots[0x11][9] == 0xD7) {
        SND_PlayCue(EMI_CUE_ID(2, 8));
    }
    slots  = SP_PTR(u8*, 0u);
    chk    = slots[0x11];
    count  = (chk[9] - 1);
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
    GFX_DrawShadedDisc((s16)work->screen_x, (s16)work->screen_y, work->timer, 0x80, 0);
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

MATCH void func_801F97F8(void) {
    switch (g_SceneState.step_05) {
        case 0:
            func_801BE1B0(1);
            g_ScriptVars[0]      = 0xA;
            g_SceneState.step_05 = 1;
            break;

        case 1:
            if (g_ScriptVars[0] == 0x28) {
                g_SceneState.state_04 = 1;
                g_SceneState.step_05  = 1;
            }
            break;
    }
}

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

MATCH s32 func_801FC5A4(void) {
    if ((D_80144EA2 & 0xF) == 0xF) {
        Game_SetScriptActive();
        D_80146875 = 6;
        D_80146876 = 0x1E;
        return 1;
    }
    return 0;
}

MATCH void func_801FC5FC(void) {
    Item_VitalAdd(VITAL_ITEM_FLIER);
    Message_StartAreaMessage(0x2F);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    SND_PauseBGM(g_SndBGMId);
    SND_StartXAStream(2, 1);
    while (!(SND_IsXAIdle() & BYTE_MASK)) {
        func_801992B8();
        CallbackWait(1U);
    }
    SND_ResumeBGM(g_SndBGMId);
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

/* blocker: both constants need v1; first diff: li v1,30 at 0x801FC6D4. */
INCLUDE_ASM(func_801FC6C4);
INCLUDE_ASM(func_801FC704);

MATCH s32 func_801FC7EC(s32 arg0, s32 arg1) {
    u8 var_v0;

    if (SYS_TestFlag(g_SceneFlags, 1) == 0) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
            if (((arg0 >> 0x10) - 2) < 3U) {
                if (arg1 == TO_COORD(6)) {
                    var_v0 = 2;
                    goto block_9;
                }
            }
        } else if ((SYS_TestFlag(g_SceneFlags, 0) != 0) && (((arg0 >> 0x10) - 3) < 2U)) {
            if (arg1 == TO_COORD(4)) {
                var_v0 = 1;
            block_9:
                D_80146874 = var_v0;
            }
        }
    }
    return 0;
}

MATCH s32 func_801FC8AC(s32 arg0, s32 arg1) {
    if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
        if (((arg1 >> 0x10) - 7) < 2U) {
            if (arg0 == TO_COORD(92)) {
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
        if (arg1 == TO_COORD(65) + COORD_HALF) {
            if (((arg0 >> 0x10) - 32) < 4U) {
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

MATCH s8 func_801FC9DC(s32 arg0, s32 arg1) {
    if (SYS_TestFlag(g_SceneFlags, 0x18) == 0) {
        if (arg0 == TO_COORD(58) + COORD_HALF) {
            if (((arg1 >> 0x10) - 60) >= 2U) {
                goto block_4;
            }
            goto block_9;
        }
    block_4:
        if (arg1 == TO_COORD(2) + COORD_HALF) {
            if (((arg0 >> 0x10) - 31) >= 2U) {
                goto block_7;
            }
            goto block_9;
        }
    block_7:
        if (arg1 == TO_COORD(76) + COORD_HALF) {
            if (((arg0 >> 0x10) - 31) < 2U) {
            block_9:
                D_80146874 = 5;
                D_80146875 = 0;
                return Scene_ShowMessage(0x12);
            }
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #11. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

MATCH s8 func_801FCAB8(s32 arg0, s32 arg1) {
    if (SYS_TestFlag(g_SceneFlags, 0x1A) != 0) {
        if ((arg0 >> 0x10) == 21) {
            if (((arg1 >> 0x10) - 52) < 2U) {
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

MATCH s32 func_801FCCDC(void) {
    if (MEM(u16, GAME_AREA_ID_ADDR) == AREA_ID_MOUNT_BOUMORE_SECOND) {
        return func_801FCD1C();
    }
    return 0;
}

INCLUDE_ASM(func_801FCD1C);

/* needs: D_801FD030 and D_801FD038 declarations. */
INCLUDE_ASM(func_801FCDB4);

MATCH void func_801FCE18(void) {
    Message_StartAreaMessage(25);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    Game_SetScriptActive();
    D_80146876 = 30;
    D_80146874 = 7;
    D_80146875 = 0;
}

MATCH void func_801FCE6C(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR, 0);
    g_PartyFieldOrder[0]  = 255;
    D_80144F5B            = 255;
    D_80144F5C            = 255;
    g_PartyBattleOrder[0] = 255;
    D_80144F5E[0]         = 255;
    D_80144F5F            = 255;
    g_Game.party_size     = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
}

MATCH void func_801FCEDC(void) {
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

#include "overlays/scenario/Scene_RemoveNina.h"
