#include "magic151_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

/* func_801EECB0 */
MATCH void BMagic_AccessionInit(void) {
    u8* text;

    func_800A68A4();
    g_BattleMessageState = 1;
    text                 = UI_MessageGetText(D_800B4C90[g_Battle.dragon_form]);
    SYS_CopyString(D_80149298, text, 8);
    func_801DE560(1, 1, 0, 60, D_80149298);
    if (g_Battle.dragon_form == 3 || g_Battle.dragon_form == DRAGON_FORM_TIAMAT || g_Battle.dragon_form == DRAGON_FORM_MAMMOTH) {
        TASK(PartyMember)->header.step += 1;
    }
    if (g_Game.members[g_Battle.target_selector].chr.character_id == CHAR_ID_RYU_YOUNG) {
        TASK(PartyMember)->unk_09 = 3;
    } else {
        TASK(PartyMember)->unk_09 = 30;
    }
    TASK(PartyMember)->header.mode += 1;
}

/* func_801EEDE0 */
MATCH void BMagic_AccessionTransformUpdate(void) {
    Callback handlers[2] = {func_801EEE38, func_801EF318};

    SYS_DISPATCH_TASK(handlers, 2, g_Task);
}

MATCH void func_801EEE38(void) {
    Magic151Steps handlers;

    handlers = g_BMagicAccessionSoloSteps;
    SYS_DISPATCH_TASK(handlers.steps, 3, g_Task);
}

/* func_801EEEA8 */
MATCH void BMagic_AccessionCastStart(void) {
    PartyMember* saved_work;
    PartyMember* battler;

    saved_work = TASK(PartyMember);
    battler    = &g_Game.members[g_Battle.active_battler];
    g_Task     = battler;
    Script_Request((battler->facing + 0x3C) & BYTE_MASK);
    g_Task = saved_work;
    saved_work->unk_03 += 1;
}

/* func_801EEF24 */
MATCH void BMagic_AccessionCastWait(void) {
    PartyMember* saved;
    PartyMember* work;
    u8           count;
    s32          cue;
    u32          slot;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        cue = EMI_SE_ID(SND_BANK_COMMON, 0x01);
        if (g_Game.members[g_Battle.target_selector].chr.character_id == CHAR_ID_RYU_YOUNG) {
            cue = EMI_SE_ID(SND_BANK_COMMON, 0x00);
        }
        SND_SEQueueSelection(cue);
    }
    saved  = TASK(PartyMember);
    g_Task = &g_Game.members[g_Battle.active_battler];
    if (!(Script_AnimStepOnce() & BYTE_MASK)) {
        g_Task = saved;
        return;
    }
    TASK(PartyMember)->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task                             = saved;
    TASK(PartyMember)->param.unk_0B    = 0;
    slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
    work                               = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = BMAGIC_ACCESSION_EFFECT_SEQUENCE;
    g_BattleEffects[slot].target.party = work;
    TASK(PartyMember)->unk_03 += 1;
}

/* Loads the character archive the active battler's facing selects from the dragon-form row when the effect
 * ticker is one, then advances byte 0x03. */
/* func_801EF070 */
MATCH void BMagic_AccessionSoloLoad(void) {
    s32 archive_id;

    if (TASK(PartyMember)->param.unk_0B == 1) {
        if (g_BattleEffectBattler->facing < 2) {
            archive_id = D_800B499C[g_Battle.dragon_form][0][g_EmiLoadedCharacterIndex];
        } else {
            archive_id = D_800B499C[g_Battle.dragon_form][1][g_EmiLoadedCharacterIndex];
        }
        EMI_ArchiveLoad(archive_id);
        TASK(PartyMember)->unk_03 += 1;
    }
}

/* Installs the active party member as the work record, releases its fades, copies its template byte, loads its
 * action-block palette and status, requests its facing script, then restores the previous record. */
/* func_801EF138 */
MATCH void BMagic_AccessionSoloShow(void) {
    PartyMember* saved;

    if (EMI_IsReady()) {
        if (g_Battle.flags & BATTLE_STATE_OVER) {
            if (g_Battle.unk_EA[0] == g_Battle.active_battler) {
                g_Battle.flags &= ~BATTLE_STATE_OVER;
            }
        }
        saved  = TASK(PartyMember);
        g_Task = &g_Game.members[g_Battle.active_battler];
        GFX_PaletteFreeFadeTarget(g_Task);
        s_BattleBattlerTemplates[g_Battle.active_battler].unk_27 = g_Game.members[g_Battle.active_battler].unk_27;
        GFX_PaletteLoad((TASK(PartyMember)->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, g_Battle.unk_D6[3]);
        func_801DDAB4(g_Game.members[g_Battle.active_battler].chr.status);
        GFX_PaletteUploadRows();
        Script_Request((TASK(PartyMember)->facing + 4) & BYTE_MASK);
        g_Task = saved;
        saved->unk_03 += 1;
    }
}

/* func_801EF2A0 */
MATCH void BMagic_AccessionTransformEnd(void) {
    PartyMember* saved_work;
    PartyMember* battler;

    saved_work = TASK(PartyMember);
    battler    = &g_Game.members[g_Battle.active_battler];
    g_Task     = battler;
    battler->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task = saved_work;
    saved_work->header.mode += 1;
    TASK(PartyMember)->header.step = 0;
    TASK(PartyMember)->unk_03      = 0;
}

MATCH void func_801EF318(void) {
    Magic151Steps handlers;

    handlers = g_BMagicAccessionMergeSteps;
    SYS_DISPATCH_TASK(handlers.steps, 3, g_Task);
}

/* When the effect ticker is one, marks every party member's handler busy and loads the dragon-form archive
 * the battler's facing selects. */
/* func_801EF388 */
MATCH void BMagic_AccessionMergeLoad(void) {
    s32 archive_id;
    u8  i;

    if (TASK(PartyMember)->param.unk_0B == 1) {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            g_Game.members[i].header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
        if (g_BattleEffectBattler->facing < 2) {
            archive_id = D_800B499C[g_Battle.dragon_form][0][0];
        } else {
            archive_id = D_800B499C[g_Battle.dragon_form][1][0];
        }
        EMI_ArchiveLoad(archive_id);
        TASK(PartyMember)->unk_03 += 1;
    }
}

/* Sets the battle up for the loaded party: frees each active member's fade palette and resets its battler template,
 * rebuilds member zero at the encounter origin, and opens the member panels. */
/* func_801EF484 */
MATCH void BMagic_AccessionMerge(void) {
    PartyMember* task;
    u8           i;
    s32          index;
    s16          panel_x;
    s16          panel_y;

    if (!EMI_IsReady()) {
        return;
    }
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (g_Game.members[i].header.flags & 1) {
            GFX_PaletteFreeFadeTarget(&g_Game.members[i]);
            s_BattleBattlerTemplates[i].u.turn.command.type       = 0;
            s_BattleBattlerTemplates[i].u.turn.damage_flags.value = 0;
            s_BattleBattlerTemplates[i].unk_27                    = g_Game.members[i].unk_27;
            func_801DDFEC(i);
            func_801DD14C(i);
        }
    }
    func_801DE1B0(g_Battle.active_battler);
    g_Game.members[0]                    = g_Game.members[g_Battle.active_battler];
    g_Game.members[0].slot               = 0;
    g_Game.members[0].pos.x.fixed        = g_EncounterOriginX;
    g_Game.members[0].pos.y.fixed        = g_EncounterOriginY;
    g_Game.members[0].pos.z.part.integer = Area_HeightSample(g_EncounterOriginX, g_EncounterOriginY);
    D_801EC364                           = g_EncounterOriginX;
    D_801EC368                           = g_EncounterOriginY;
    D_801EC36C                           = Area_HeightSample(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed) << 16;
    g_Game.members[1].header.flags       = 0;
    g_Game.members[2].header.flags       = 0;
    g_Battle.active_battler              = 0;
    g_Battle.flags |= BATTLE_STATE_RELOAD_PARTY;
    g_Battle.unk_EF[0]          = g_Battle.party_count;
    g_Battle.party_count        = 1;
    g_Battle.living_party_count = 1;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (g_Game.members[i].header.flags & 1) {
            UI_PanelOpenTask(i + 0xD, 3);
            D_80148332[i + 0xD].mode_00 = 5;
            D_80148332[i + 0xD].unk_01  = 0;
            index                       = g_Game.members[i].facing * 2 + g_Game.members[i].chr.character_id * 8;
            panel_x                     = g_Game.members[i].screen_x.value + D_801EB0B0[index];
            panel_x                     = D_801EAEA4[(g_Battle.scroll_dir & 0xFE) ^ 0x2] + panel_x;
            D_80148332[i + 0xD].x_02    = panel_x;
            index                       = g_Game.members[i].facing * 2 + g_Game.members[i].chr.character_id * 8;
            panel_y                     = g_Game.members[i].screen_y.value + D_801EB0B1[index] + 0xC;
            D_80148332[i + 0xD].y_04    = panel_y;
            D_80148332[i + 0xD].battler = i;
            D_80148332[i + 0xD].unk_06  = 0;
            D_80148332[i + 0xD].unk_07  = 0;
        }
    }
    D_80148332[1].x_02    = 0x70;
    D_80148332[1].battler = g_Battle.party_count;
    g_Battle.flags &= ~BATTLE_STATE_OVER;
    task = TASK(PartyMember);
    TASK_SET(&g_Game.members[g_Battle.active_battler]);
    func_801DE190(TASK(PartyMember)->slot);
    TASK(PartyMember)->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    Party_MemberLoadSprite(D_80181B34[g_EmiLoadedCharacterIndex][0], 0);
    GFX_PaletteLoad(GAME_PALETTE_STAGE + TASK(PartyMember)->slot * 0x40, g_Battle.unk_D6[3]);
    func_801DDAB4(g_Game.members[g_Battle.active_battler].chr.status);
    GFX_PaletteUploadRows();
    Script_Request((u8)(TASK(PartyMember)->facing + 4));
    TASK_SET(task);
    task->unk_03 += 1;
}

/* func_801EF938 */
MATCH void BMagic_AccessionEnd(void) {
    if (TASK(PartyMember)->param.unk_0B == 2) {
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        g_Game.members[g_Battle.active_battler].u.turn.action_flags.value |= BATTLER_ACTION_UNK_5;
        g_Game.members[g_Battle.active_battler].u.turn.action_flags.value &= ~BATTLER_ACTION_ABILITY_ALT_POSE;
        Effect_Reset();
    }
}

/* func_801EF9F0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EFA34 */
MATCH void BMagic_AccessionSequenceUpdate(void) {
    BMagicEffectSteps handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(g_BMagicAccessionSequenceSteps, header.step);
}

/* func_801EFAAC */
MATCH void BMagic_AccessionSequenceBands(void) {
    PartyMember* work;
    s32          y;
    u32          slot;

    TASK(PartyMember)->facing           = g_BattleSelectedActor->facing;
    TASK(PartyMember)->pos.x.fixed      = g_EncounterOriginX;
    y                                   = g_EncounterOriginY;
    TASK(PartyMember)->pos.y.fixed      = y;
    COORD_INT(TASK(PartyMember)->pos.z) = Area_HeightSample(TASK(PartyMember)->pos.x.fixed, y);
    TASK(PartyMember)->param.unk_0B     = 0;
    TASK(PartyMember)->unk_09           = 4;
    TASK(PartyMember)->header.step += 1;
    slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
    work                               = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = BMAGIC_ACCESSION_EFFECT_BAND;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].target.party = work;
    TASK(PartyMember)->param.unk_0B += 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x02));
}

/* func_801EFBAC */
MATCH void BMagic_AccessionSequenceGlow(void) {
    u8           count;
    u32          slot;
    PartyMember* work;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
        work                               = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_ACCESSION_EFFECT_GLOW;
        g_BattleEffects[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B += 1;
        TASK(PartyMember)->unk_09 = 4;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EFC68 */
MATCH void BMagic_AccessionSequenceDome(void) {
    PartyMember* work;
    PartyMember* task;
    u32          slot;

    if (--TASK(PartyMember)->unk_09 == 0) {
        slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
        work                               = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_ACCESSION_EFFECT_DOME;
        task                               = TASK(PartyMember);
        g_BattleEffects[slot].target.party = work;
        task->param.unk_0B += 1;
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x03));
        TASK(PartyMember)->unk_09 = 20;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EFD24 */
MATCH void BMagic_AccessionSequenceWait(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 1;
        TASK(PartyMember)->header.step   = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EFD80(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->header.mode == 2) {
        work              = SP_REF(PartyMember*, 0x44u);
        work->header.step = work->header.step + 1;
    }
}

/* func_801EFDC0 */
MATCH void BMagic_AccessionSequenceEnd(void) {
    if (TASK(PartyMember)->param.unk_0B == 0) {
        g_BattleEffectBattler->param.unk_0B = 2;
        Effect_Reset();
    }
}

/* func_801EFE00 */
MATCH void BMagic_AccessionDomeUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicAccessionDomeSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        BMagic_AccessionDrawDome();
        BMagic_AccessionDrawFlare();
        PopMatrix();
    }
}

/* func_801EFE90 */
MATCH void BMagic_AccessionDomeStart(void) {
    PartyMember* work  = TASK(PartyMember);
    PartyMember* actor = g_BattleEffectBattler;
    s32          z;

    work->pos.x.fixed               = actor->pos.x.fixed;
    work->pos.y.fixed               = actor->pos.y.fixed;
    z                               = actor->pos.z.fixed;
    work->unk_5D                    = 0x10;
    work->pos.z.fixed               = z;
    TASK(PartyMember)->unk_5E       = 0x10;
    TASK(PartyMember)->unk_5F       = 0x24;
    TASK(PartyMember)->unk_04       = 0;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->timer        = 30;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EFF44(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(unk_09, 2, 32);
}

/* func_801EFF94 */
MATCH void BMagic_AccessionDomeRays(void) {
    u32          slot;
    PartyMember* work;

    if ((g_FrameCount & 0x3) == 0) {
        slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
        work                               = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_ACCESSION_EFFECT_RAY;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = TASK(PartyMember)->unk_04 & 0xF;
        TASK(PartyMember)->param.unk_0B += 1;
        TASK(PartyMember)->unk_04 += 1;
    }
    if (g_BattleEffectBattler->header.step == 5) {
        if (--TASK(PartyMember)->timer == 0) {
            TASK(PartyMember)->header.step += 1;
        }
    }
}

#include "overlays/bmagic/shared/Effect_StepOnZeroTick.h"

/* func_801F00E8 */
MATCH void BMagic_AccessionDomeDim(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_5D - 1;
    TASK(PartyMember)->unk_5D = count;
    if ((s8)count == 8) {
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F013C */
MATCH void BMagic_AccessionDomeEnd(void) {
    s8 count;
    u8 count_next;

    count = TASK(PartyMember)->unk_5D;
    if (count != 0) {
        TASK(PartyMember)->unk_5D = count - 1;
    }
    count_next                = TASK(PartyMember)->unk_5E - 1;
    TASK(PartyMember)->unk_5E = count_next;
    if ((count_next << 0x18) == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801F026C */
MATCH void BMagic_AccessionDrawDome(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      x;
    s32      y;
    u8       ring;
    u8       i;

    g_ScratchPad.cells.halves[5] = (s8)TASK(PartyMember)->unk_5D * 15;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 16;
    g_ScratchPad.cells.halves[1] = FIXED_MUL(rsin(0x400), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[3] = FIXED_MUL(rcos(0x400), g_ScratchPad.cells.halves[0]);
    for (ring = 9; ring <= 16; ring++) {
        g_ScratchPad.cells.halves[2] = g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[4] = g_ScratchPad.cells.halves[3];
        g_ScratchPad.cells.halves[1] = FIXED_MUL(rsin(ring << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[3] = FIXED_MUL(rcos(ring << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vz    = g_ScratchPad.cells.halves[3];
        g_ScratchPadVectors[1].vz    = g_ScratchPad.cells.halves[3];
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[2].vz    = g_ScratchPad.cells.halves[4];
        g_ScratchPadVectors[3].vz    = g_ScratchPad.cells.halves[4];
        for (i = 1; i <= 16; i++) {
            g_ScratchPad.cells.halves[7] = (i & 15) * 256;
            g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2]);
            g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2]);
            x                            = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
            y                            = (g_ScratchPadVectors[3].vy << 9) + TASK(PartyMember)->pos.y.fixed;
            tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 1, sizeof(DR_MODE));
            prim = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
            Area_CellAddPrim(x, y, 1, sizeof(POLY_F4));
        }
    }
}

/* func_801F0648 */
MATCH void BMagic_AccessionDrawFlare(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      x;
    s32      y;
    u8       i;

    g_ScratchPad.cells.halves[5] = (s8)TASK(PartyMember)->unk_5E * 12;
    g_ScratchPad.cells.halves[6] = (s8)TASK(PartyMember)->unk_5E * 8;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 16;
    g_ScratchPad.cells.halves[2] = FIXED_MUL(rsin(0x400), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[4] = FIXED_MUL(rcos(0x400), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 18;
    g_ScratchPad.cells.halves[7] = ((s8)TASK(PartyMember)->unk_5F + RANDOM_MASK(3)) * 32;
    g_ScratchPad.cells.halves[1] = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[3] = FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[0].vz    = g_ScratchPad.cells.halves[3];
    g_ScratchPadVectors[1].vz    = g_ScratchPad.cells.halves[3];
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]);
    g_ScratchPadVectors[2].vz    = g_ScratchPad.cells.halves[4];
    g_ScratchPadVectors[3].vz    = g_ScratchPad.cells.halves[4];
    for (i = 1; i <= 16; i++) {
        g_ScratchPad.cells.halves[7] = (i & 15) * 256;
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2]);
        x                            = (g_ScratchPadVectors[3].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y                            = (g_ScratchPadVectors[3].vy << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 1, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5]);
        setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5]);
        Area_CellAddPrim(x, y, 1, sizeof(POLY_G4));
    }
}

/* Draws the glow ring step header.step selects: sets the actor matrix, advances the effect timers and
 * passes the slot's draw row to BMagic_AccessionDrawRay while the step is running. */
/* func_801F0AC8 */
MATCH void BMagic_AccessionRayUpdate(void) {
    PartyMember* work;

    SYS_DISPATCH_BYTE(g_BMagicAccessionRaySteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        work = TASK(PartyMember);
        work->unk_09 += 2;
        work->unk_0C += 1;
        BMagic_AccessionDrawRay(g_BMagicAccessionRayAngles[TASK(PartyMember)->unk_04][0] + TASK(PartyMember)->unk_09, g_BMagicAccessionRayAngles[TASK(PartyMember)->unk_04][1]);
        PopMatrix();
    }
}

/* func_801F0BA8 */
MATCH void BMagic_AccessionRayStart(void) {
    PartyMember* work;
    s32          value;

    TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    value                           = RANDOM_MASK(0x1F);
    work                            = TASK(PartyMember);
    work->unk_5D                    = 0x10;
    work->unk_0C                    = value;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->timer        = 4;
    TASK(PartyMember)->header.step += 1;
}

/* func_801F0C50 */
MATCH void BMagic_AccessionRayGrow(void) {
    u8 timer_next;

    timer_next               = TASK(PartyMember)->timer + 4;
    TASK(PartyMember)->timer = timer_next;
    if ((timer_next & BYTE_MASK) >= 0x20U) {
        TASK(PartyMember)->param.unk_0B = 1;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F0CB0 */
MATCH void BMagic_AccessionRayFade(void) {
    PartyMember* work;
    s8           timer;

    work         = TASK(PartyMember);
    timer        = work->unk_5D - 2;
    work->unk_5D = timer;
    if (timer == 0) {
        work               = g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Effect_Reset();
    }
}

/* func_801F0D0C */
MATCH void BMagic_AccessionDrawRay(u8 angle0, u8 angle1) {
    LINE_F2* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      x;
    s32      y;
    u8       i;

    g_ScratchPad.cells.halves[5] = (s8)TASK(PartyMember)->unk_5D * 12;
    g_ScratchPad.cells.halves[0] = 0x200;
    g_ScratchPad.cells.halves[1] = FIXED_MUL(rsin(angle1 << 4), g_ScratchPad.cells.halves[0]);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(angle0 << 4), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(angle0 << 4), g_ScratchPad.cells.halves[1]),
              FIXED_MUL(rcos(angle1 << 4), g_ScratchPad.cells.halves[0]));
    for (i = 0; i < TASK(PartyMember)->timer; i++) {
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz    = g_ScratchPadVectors[1].vz;
        g_ScratchPad.cells.halves[2] = RANDOM_MASK(3) + 4;
        g_ScratchPad.cells.halves[7] = ((TASK(PartyMember)->unk_0C + i) & 0x1F) * 128;
        g_ScratchPad.cells.halves[7] = (angle1 + FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[2])) << 4;
        g_ScratchPad.cells.halves[1] = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
        angle0 += RANDOM_MASK(7);
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(angle0 << 4), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(angle0 << 4), g_ScratchPad.cells.halves[1]);
        x                         = (g_ScratchPadVectors[1].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[1].vy << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TASK(PartyMember)->param.unk_0B, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
        prim = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        SetSemiTrans(prim, TASK(PartyMember)->param.unk_0B);
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &depth, &flag);
        RotTransPers(&g_ScratchPadVectors[1], (long*)&prim->x1, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        Area_CellAddPrim(x, y, 2, sizeof(LINE_F2));
    }
}

/* Runs the step's handler, projects the battle range and, once the effect is live, sets the rolled actor
 * matrix and draws its three bands. */
/* func_801F10E8 */
MATCH void BMagic_AccessionBandUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicAccessionBandSteps, TASK(PartyMember)->header.step);
    Battle_ProjectRange();
    if (TASK(PartyMember)->header.step != 0 && TASK(PartyMember)->header.flags != 0) {
        Effect_SetActorMatrixQuarterRoll();
        BMagic_AccessionDrawBand(32, 32, 0x7);
        TASK(PartyMember)->param.unk_0B += 4;
        BMagic_AccessionDrawBand(16, 64, 0xF);
        TASK(PartyMember)->param.unk_0B += 4;
        BMagic_AccessionDrawBand(16, 96, 0x1F);
        TASK(PartyMember)->param.unk_0B -= 8;
        PopMatrix();
    }
}

/* func_801F11E0 */
MATCH void BMagic_AccessionBandStart(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
        TASK(PartyMember)->param.unk_0B = RANDOM_MASK(0xF);
        TASK(PartyMember)->unk_09       = 0;
        TASK(PartyMember)->timer        = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F129C */
MATCH void BMagic_AccessionBandGrow(void) {
    TASK(PartyMember)->param.unk_0B += 1;
    TASK(PartyMember)->timer += 4;
    if (TASK(PartyMember)->timer == 16) {
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_Wait.h"

#include "overlays/bmagic/shared/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrixQuarterRoll.h"

/* Draws seventeen steps of four quads: the ring sways with the effect counter and its radius jitters by jitter_mask. */
/* func_801F14D0 */
MATCH void BMagic_AccessionDrawBand(s16 band_height, s16 radius, u16 jitter_mask) {
    POLY_G4* prim;
    long     p;
    long     flag;
    s32      tpage;
    s32      i;

    g_ScratchPad.cells.halves[0] = radius / 2;
    g_ScratchPad.cells.halves[7] = (TASK(PartyMember)->param.unk_0B & 0xF) * 256;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer * 15;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->timer * 13;
    g_ScratchPadVectors[0].vy    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[0].vz    = 0;
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    for (i = 1; i < 18; i++) {
        g_ScratchPad.cells.halves[7] = ((TASK(PartyMember)->param.unk_0B + i) & 0xF) << 8;
        if RANDOM_MASK (1) {
            g_ScratchPad.cells.halves[0] = radius + (jitter_mask & rand());
        } else {
            g_ScratchPad.cells.halves[0] = radius - (jitter_mask & rand());
        }
        g_ScratchPadVectors[2].vx = 0;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx = 0;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[0].vy - band_height;
        g_ScratchPadVectors[3].vz = g_ScratchPadVectors[0].vz;
        setVector(&g_ScratchPadVectors[0], 0, FIXED_MUL(rsin(g_ScratchPad.cells.halves[7]), g_ScratchPad.cells.halves[0]), -(i << 6));
        g_ScratchPadVectors[1].vx = 0;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vy - band_height;
        g_ScratchPadVectors[1].vz = -(i << 6);
        prim                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
            setRGB3(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy -= band_height;
        g_ScratchPadVectors[1].vy -= band_height;
        g_ScratchPadVectors[2].vy -= band_height;
        g_ScratchPadVectors[3].vy -= band_height;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
        setRGB1(prim, 1, 1, 1);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy += band_height * 2;
        g_ScratchPadVectors[1].vy += band_height * 2;
        g_ScratchPadVectors[2].vy += band_height * 2;
        g_ScratchPadVectors[3].vy += band_height * 2;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
            setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy += band_height;
        g_ScratchPadVectors[1].vy += band_height;
        g_ScratchPadVectors[2].vy += band_height;
        g_ScratchPadVectors[3].vy += band_height;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        } else {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, g_ScratchPad.cells.halves[6], 1, g_ScratchPad.cells.halves[6]);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        g_ScratchPadVectors[0].vy -= band_height * 2;
    }
}

/* func_801F1C3C */
MATCH void BMagic_AccessionGlowUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicAccessionGlowSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix5();
        BMagic_DrawGlowRingInner();
        BMagic_DrawGlowRingOuter();
        PopMatrix();
    }
}

/* func_801F1CCC */
MATCH void BMagic_AccessionGlowStart(void) {
    PartyMember* work  = TASK(PartyMember);
    PartyMember* actor = g_BattleEffectBattler;
    s32          z;

    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->unk_09      = 0x10;
    work->unk_14      = 0x100;
    work->pos.z.fixed = z;
    TASK(PartyMember)->header.step += 1;
}

/* func_801F1D28 */
MATCH void BMagic_AccessionGlowGrow(void) {
    PartyMember* work;
    s32          value;

    work         = TASK(PartyMember);
    value        = work->unk_14 + 0x80;
    work->unk_14 = value;
    if (value == 0x400) {
        work->header.step++;
    }
}

/* Best 7 differences: lui a0 at 0x801F1D60; adjust register allocation. */
/* func_801F1D60 */
#include "overlays/bmagic/shared/Effect_RiseUntilTimerZero.h"

MATCH void Effect_SetActorMatrix5(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

/* The glow ring scratch: the inner radius, the outer radius and the shade, then the quad corners (g_ScratchPadVectors). */
#define GLOW_RING_INNER g_ScratchPad.cells.halves[1]
#define GLOW_RING_OUTER g_ScratchPad.cells.halves[2]
#define GLOW_RING_SHADE g_ScratchPad.cells.halves[5]

/* The inner half of the glow ring: a ring of 64 additive quads from the effect radius (word 0x14) out
 * to 64 past it, brightest at its outer edge. */
MATCH void BMagic_DrawGlowRingInner(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(GFX_LAYER_BATTLE_SCENE, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    GLOW_RING_INNER           = TASK(PartyMember)->unk_14;
    GLOW_RING_OUTER           = TASK(PartyMember)->unk_14 + 0x40;
    GLOW_RING_SHADE           = TASK(PartyMember)->unk_09 * 15;
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), GLOW_RING_INNER), FIXED_MUL(rcos(0), GLOW_RING_INNER), 0);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 64; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_OUTER);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_OUTER);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_INNER);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_INNER);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB1(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_G4));
    }
}

/* The outer half of the glow ring: the ring from 64 to 128 past the effect radius, fading out at its outer edge. */
MATCH void BMagic_DrawGlowRingOuter(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(GFX_LAYER_BATTLE_SCENE, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    GLOW_RING_INNER           = TASK(PartyMember)->unk_14 + 0x40;
    GLOW_RING_OUTER           = TASK(PartyMember)->unk_14 + 0x80;
    GLOW_RING_SHADE           = TASK(PartyMember)->unk_09 * 15;
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), GLOW_RING_INNER), FIXED_MUL(rcos(0), GLOW_RING_INNER), 0);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 64; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_OUTER);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_OUTER);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_INNER);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_INNER);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB3(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_G4));
    }
}
