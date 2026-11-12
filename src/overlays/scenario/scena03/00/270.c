#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F6EB4(void) {
    u8*  work;
    u8*  data;
    u8*  cell;
    u8   cell4;
    u32  cell3;
    s16* scratch;

    g_Task->unk_03 = Actor_FindFree();
    if (g_Task->unk_03 == GAME_NONE) {
        return;
    }

    g_Actors[g_Task->unk_03].header.flags = 1;
    g_Task->unk_04                        = Actor_FindFree();
    if (g_Task->unk_04 == GAME_NONE) {
        g_Actors[g_Task->unk_03].header.flags = 0;
        return;
    }

    scratch                               = (s16*)D_1F800000;
    data                                  = (u8*)D_801FCF30;
    g_Actors[g_Task->unk_04].header.flags = 1;
    work                                  = (u8*)g_Task;
    *scratch                              = work[3];
    func_801A65A0(data);
    Actor_BeginScript(0x61, 0xC);
    *scratch = work[4];
    func_801A65A0(data);
    Actor_BeginScript(0x61, 0xC);
    SP_REF(u8*, 0x44) = work;

    g_Actors[work[3]].pos.x.fixed += ONE;
    g_Actors[work[3]].pos.y.fixed -= ONE;
    g_Actors[work[4]].pos.x.fixed -= ONE;
    g_Actors[work[4]].pos.y.fixed += ONE;
    g_Actors[work[3]].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    g_Actors[g_Task->unk_04].header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    cell                                      = (u8*)g_Task;
    cell4                                     = cell[4];
    cell3                                     = cell[3];
    FIELD(u8, D_801468E4, cell4 * ACTOR_SIZE) = 0;
    FIELD(u8, D_801468E4, cell3 * ACTOR_SIZE) = 0;
    GFX_AllocPaletteFade(&g_Actors[work[3]], 15, 0, 0, 1);
    GFX_AllocPaletteFade(&g_Actors[work[4]], 0, 0, 15, 1);
    g_Task->timer       = 4;
    g_Task->header.mode = 1;
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
        g_Task->draw_layer = 0;
        g_Task->timer      = g_Task->header.mode;
        GFX_AddPrim(g_Task->draw_layer, sizeof(DR_MOVE));
        if (g_Task->header.mode == 4) {
            Actor_Clear();
        }
    } else {
        g_Task->timer--;
    }
}

MATCH void func_801F7508(void) {
    SYS_DISPATCH_TASK(D_801FCF50, 1, g_Task);
}

#include "overlays/Actor_StartFadePair.h"

MATCH void func_801F754C(void) {
    ACTOR_START_FADE_PAIR(D_801FCF5C);
}

#include "shared/Actor_Reveal.h"

MATCH void Actor_FreePaletteFades2(void) {
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
        g_Task->timer = 128;
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

    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 9));
    work                  = SP_REF(void*, 0x44);
    FIELD(u8, work, 0x1u) = (FIELD(u8, work, 0x1u) + 1);
}

MATCH void func_801F7E6C(void) {
    ActorSlot** effects;
    ActorSlot*  spawned;
    Actor*      record;
    Actor*      actor;
    u8          i;
    u8          slot;

    effects = (ActorSlot**)&g_Task->vx;
    for (i = 0; i < 5; i++) {
        slot = Actor_FindFreeSlot();
        if (slot != GAME_NONE) {
            spawned                    = &g_ActorSlots[slot];
            effects[i]                 = spawned;
            spawned->header.flags      = 1;
            spawned->unk_06            = 0;
            spawned->type              = 0x21;
            actor                      = g_Task;
            spawned->scene_step        = actor->pos.x.fixed;
            spawned->selection         = actor->pos.y.fixed;
            spawned->unk_14            = actor->pos.z.fixed;
            record                     = (Actor*)spawned;
            record->script_pc          = 6;
            record->unk_5A             = 0;
            record->tint.halves.unk_5C = i * 819;
            record->tint.halves.unk_5E = 0;
        }
    }
    g_Task->header.mode += 1;
}

MATCH void func_801F7F84(void) {
    ActorSlot** effects; /* the five effect slots spawned at +0x0C */
    u8          i;

    effects = (ActorSlot**)&g_Task->vx;
    for (i = 0; i < 5; i++) {
        if (effects[i]->unk_06 == 0) {
            return;
        }
    }
    g_ScriptVars[0] += 1;
    Actor_Clear();
}

INCLUDE_ASM(func_801F7FFC);

INCLUDE_ASM(func_801F8170);

INCLUDE_ASM(func_801F8200);

MATCH void func_801F82E4(void) {
    SYS_DISPATCH_TASK(D_801FCF94, 1, g_Task);
}

MATCH void func_801F8328(void) {
    g_Task->timer = 96;
    g_Task->header.mode++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
}

MATCH void func_801F8370(void) {
    ActorSlot* temp_v0;
    s32        temp_v1;
    u8         temp_v0_2;

    if (g_Task->timer & 0x4) {
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

MATCH void func_801F853C(void) {
    Scena03Work* work;
    s16          value;

    work = SCN_LINE;
    func_801F88FC(&work->line);
    value             = work->line.unk_06 - 0x10;
    work->line.unk_06 = value;
    if (value < 0) {
        work->line.unk_06 = 0;
    }
    if (work->line.unk_06 < 0x80) {
        work->line.unk_08 -= 0x10;
    }
    if (work->line.unk_08 < 0) {
        work->line.unk_06 = 0;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F85DC(void) {
    Actor_Clear();
}

MATCH void func_801F85FC(void) {
    SYS_DISPATCH_TASK(D_801FCFAC, 1, g_Task);
}

#include "shared/Actor_TrackFocus.h"

MATCH void func_801F8710(void) {
    GFX_DrawShadedDisc((s16)g_Task->screen_x, (s16)g_Task->screen_y, g_Task->timer, 0x80, 0);
    g_Task->timer += 15;
    if (g_Task->timer >= 61) {
        g_Task->timer = 255;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F87A4(void) {
    u8 count;

    GFX_DrawShadedDisc((s16)g_Task->screen_x, (s16)g_Task->screen_y, (g_Task->timer & 0x1) | 0x3C, 0x80, 0);
    if (g_Task->timer == 215) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 8));
    }
    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        g_Task->timer = 60;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F885C(void) {
    GFX_DrawShadedDisc((s16)g_Task->screen_x, (s16)g_Task->screen_y, g_Task->timer, 0x80, 0);
    g_Task->timer -= 1;
    if ((s8)g_Task->timer < 0) {
        g_Task->header.mode += 1;
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

MATCH void func_801FC3B4(void) {
    SCENA03_NUDGE_SCROLL(D_801FD004, 3);
}

MATCH void func_801FC410(void) {
    SCENA03_NUDGE_SCROLL(D_801FD008, 1);
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FC4AC(void* entity, void* bits) {
    Game_SetScriptActive();
    SYS_SetFlag(bits, 20U);
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
        g_SceneState.step_05  = 6;
        g_SceneState.timer_06 = 30;
        return 1;
    }
    return 0;
}

MATCH void func_801FC5FC(void) {
    Item_VitalAdd(VITAL_ITEM_FLIER);
    Message_StartAreaMessage(47);
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
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0;
    return 0;
}

MATCH s32 func_801FC6C4(void) {
    Game_SetScriptActive();
    g_SceneState.timer_06 = 30;
    g_SceneState.state_04 = 7;
    g_SceneState.step_05  = 0;
    return 0;
}

MATCH s8 func_801FC704(s32 entry_x, s32 entry_y) {
    /* kept: the LOHU halfword compare matches retail; the plain u16 lvalue adds four bytes. */
    switch (LOHU(g_GameAreaId)) {
        case AREA_ID_WYNDIA_LOWER:
            return func_801FC944(entry_x, entry_y);
        case AREA_ID_WYNDIA_CASTLE_BASEMENT:
            return func_801FC8AC(entry_x, entry_y);
        case AREA_ID_GENMEL:
            return func_801FCAB8(entry_x, entry_y);
        case AREA_ID_MOUNT_MYRNEG:
            return func_801FC7EC(entry_x, entry_y);
        case AREA_ID_EYGNOCK_ROAD:
            return func_801FC9DC(entry_x, entry_y);
        case AREA_ID_MOUNT_BOUMORE_FIRST:
            return func_801FCB4C(entry_x, entry_y);
    }
    return 0;
}

MATCH s32 func_801FC7EC(s32 entry_x, s32 entry_y) {
    u8 var_v0;

    if (SYS_TestFlag(g_SceneFlags, 1) == 0) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
            if (((entry_x >> 0x10) - 2) < 3U) {
                if (entry_y == TO_COORD(6)) {
                    var_v0 = 2;
                    goto block_9;
                }
            }
        } else if ((SYS_TestFlag(g_SceneFlags, 0) != 0) && (((entry_x >> 0x10) - 3) < 2U)) {
            if (entry_y == TO_COORD(4)) {
                var_v0 = 1;
            block_9:
                g_SceneState.state_04 = var_v0;
            }
        }
    }
    return 0;
}

MATCH s32 func_801FC8AC(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
        if (((entry_y >> 0x10) - 7) < 2U) {
            if (entry_x == TO_COORD(92)) {
                SYS_SetFlag(g_SceneFlags, 7U);
                g_SceneState.state_04 = 3;
                g_SceneState.step_05  = 0xA;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

MATCH s8 func_801FC944(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 21) == 0) {
        if (entry_y == TO_COORD(65) + COORD_HALF) {
            if (((entry_x >> 0x10) - 32) < 4U) {
                g_SceneState.state_04 = 4;
                g_SceneState.step_05  = 5;
                return Scene_ShowMessage(0x33);
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

MATCH s8 func_801FC9DC(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 24) == 0) {
        if (entry_x == TO_COORD(58) + COORD_HALF) {
            if (((entry_y >> 0x10) - 60) >= 2U) {
                goto block_4;
            }
            goto block_9;
        }
    block_4:
        if (entry_y == TO_COORD(2) + COORD_HALF) {
            if (((entry_x >> 0x10) - 31) >= 2U) {
                goto block_7;
            }
            goto block_9;
        }
    block_7:
        if (entry_y == TO_COORD(76) + COORD_HALF) {
            if (((entry_x >> 0x10) - 31) < 2U) {
            block_9:
                g_SceneState.state_04 = 5;
                g_SceneState.step_05  = 0;
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

MATCH s8 func_801FCAB8(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 26) != 0) {
        if ((entry_x >> 0x10) == 21) {
            if (((entry_y >> 0x10) - 52) < 2U) {
                g_SceneState.state_04 = 5;
                g_SceneState.step_05  = 0x10;
                return Scene_ShowMessage(0x1F);
            }
        }
    }
    return 0;
}

MATCH s8 func_801FCB4C(s32 entry_x, s32 entry_y) {
    if (SYS_TestFlag(g_SceneFlags, 0x1B) == 0) {
        if (D_80143F03 != 2) {
            return 0;
        }
        if (entry_x != TO_COORD(0xA) + COORD_HALF) {
            return 0;
        }
        if (((entry_y >> 16) - 0x24) >= 2U) {
            return 0;
        }
        g_ScriptVars[1]       = 1;
        g_SceneState.state_04 = 6;
        g_SceneState.step_05  = 5;
        return Scene_ShowMessage(0xC);
    }
    if (D_80143F03 == 3 && entry_y == TO_COORD(0xB) + COORD_HALF && ((entry_x >> 16) - 5) < 2U) {
        if (SYS_TestFlag(g_SceneFlags, 0x1C) == 0) {
            Game_SetScriptActive();
            g_SceneState.step_05  = 0xF;
            g_SceneState.state_04 = 6;
            return 1;
        } else {
            g_SceneState.step_05  = 0xD;
            g_SceneState.state_04 = 6;
            return Scene_ShowMessage(0x11);
        }
    }
    return 0;
}

#include "overlays/scenario/Scene_ShowMessage.h"

MATCH s32 func_801FCCDC(s32 x, s32 y) {
    if (MEM(u16, GAME_AREA_ID_ADDR) == AREA_ID_MOUNT_BOUMORE_SECOND) {
        return func_801FCD1C(x, y);
    }
    return 0;
}

MATCH s8 func_801FCD1C(s32 x, s32 y) {
    if (SYS_TestFlag(g_SceneFlags, 30) == 0) {
        if (y == TO_COORD(73)) {
            if (((x >> 16) - 14) < 4U) {
                Game_SetScriptActive();
                g_SceneState.state_04 = 8;
                g_SceneState.step_05  = 2;
                g_SceneState.timer_06 = 30;
                return 1;
            }
        }
    }
    return 0;
}

/* needs: D_801FD030 and D_801FD038 declarations. */
MATCH s32 func_801FCDB4(s32 arg0, s32 arg1) {
    s8  index;
    s32 result;

    index = func_801A7AD8(&D_801FD030, 1, arg0, arg1);
    if (index >= 0) {
        SYS_DISPATCH_BYTE(D_801FD038, index);
        result = 1;
    } else {
        result = -1;
    }
    return result;
}

MATCH void func_801FCE18(void) {
    Message_StartAreaMessage(25);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    Game_SetScriptActive();
    g_SceneState.timer_06 = 30;
    g_SceneState.state_04 = 7;
    g_SceneState.step_05  = 0;
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

/* func_801FCEDC */
MATCH void Party_JoinNinaYoung(void) {
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

#include "overlays/scenario/Scene_RemoveNina.h"
