#include "magic151_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EECB0(void) {
    u8* text;

    func_800A68A4();
    g_BattleMessageState = 1;
    text                 = Message_GetText(D_800B4C90[g_Battle.dragon_form]);
    SYS_CopyString(D_80149298, text, 8);
    func_801DE560(1, 1, 0, 60, D_80149298);
    if (g_Battle.dragon_form == 3 || g_Battle.dragon_form == DRAGON_FORM_TIAMAT || g_Battle.dragon_form == DRAGON_FORM_MAMMOTH) {
        g_Task->header.step += 1;
    }
    if (g_Game.members[g_Battle.target_selector].chr.character_id == 0) {
        g_Task->unk_09 = 3;
    } else {
        g_Task->unk_09 = 30;
    }
    g_Task->header.mode += 1;
}

MATCH void func_801EEDE0(void) {
    Callback handlers[2] = {func_801EEE38, func_801EF318};

    SYS_DISPATCH_TASK(handlers, 2, g_Task);
}

MATCH void func_801EEE38(void) {
    Magic151Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.steps, 3, g_Task);
}

MATCH void func_801EEEA8(void) {
    PartyMember* saved_work;
    PartyMember* battler;

    saved_work = g_Task;
    battler    = &g_Game.members[g_Battle.active_battler];
    g_Task     = battler;
    Actor_RequestScript((battler->facing + 0x3C) & BYTE_MASK);
    g_Task = saved_work;
    saved_work->unk_03 += 1;
}

MATCH void func_801EEF24(void) {
    PartyMember* saved;
    PartyMember* work;
    u8           count;
    s32          cue;
    u32          slot;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        cue = EMI_CUE_ID(SND_BANK_COMMON, 0x01);
        if (g_Game.members[g_Battle.target_selector].chr.character_id == CHAR_ID_RYU_YOUNG) {
            cue = EMI_CUE_ID(SND_BANK_COMMON, 0x00);
        }
        SND_QueueSelectionFx(cue);
    }
    saved  = g_Task;
    g_Task = &g_Game.members[g_Battle.active_battler];
    if (!(Actor_StepAnimOnce() & BYTE_MASK)) {
        g_Task = saved;
        return;
    }
    g_Task->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task                             = saved;
    g_Task->param.unk_0B               = 0;
    slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 4;
    g_BattleEffects[slot].target.party = work;
    g_Task->unk_03 += 1;
}

/* Loads the character archive the active battler's facing selects from the dragon-form row when the effect
 * ticker is one, then advances byte 0x03. */
MATCH void func_801EF070(void) {
    s32 archive_id;

    if (g_Task->param.unk_0B == 1) {
        if (g_BattleEffectBattler->facing < 2) {
            archive_id = D_800B499C[g_Battle.dragon_form][0][g_EmiLoadedCharacterIndex];
        } else {
            archive_id = D_800B499C[g_Battle.dragon_form][1][g_EmiLoadedCharacterIndex];
        }
        EMI_LoadArchive(archive_id);
        g_Task->unk_03 += 1;
    }
}

/* Installs the active party member as the work record, releases its fades, copies its template byte, loads its
 * action-block palette and status, requests its facing script, then restores the previous record. */
MATCH void func_801EF138(void) {
    PartyMember* saved;

    if (EMI_IsReady()) {
        if (g_Battle.state & BATTLE_STATE_OVER) {
            if (g_Battle.unk_EA[0] == g_Battle.active_battler) {
                g_Battle.state &= ~BATTLE_STATE_OVER;
            }
        }
        saved  = g_Task;
        g_Task = &g_Game.members[g_Battle.active_battler];
        GFX_FreePaletteFadeTarget(g_Task);
        s_BattleBattlerTemplates[g_Battle.active_battler].unk_27 = g_Game.members[g_Battle.active_battler].unk_27;
        GFX_LoadPalette((g_Task->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, g_Battle.unk_D0[9]);
        func_801DDAB4(g_Game.members[g_Battle.active_battler].chr.status);
        GFX_UploadPaletteRows();
        Actor_RequestScript((g_Task->facing + 4) & BYTE_MASK);
        g_Task = saved;
        saved->unk_03 += 1;
    }
}

MATCH void func_801EF2A0(void) {
    PartyMember* saved_work;
    PartyMember* battler;

    saved_work = g_Task;
    battler    = &g_Game.members[g_Battle.active_battler];
    g_Task     = battler;
    battler->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task = saved_work;
    saved_work->header.mode += 1;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}

MATCH void func_801EF318(void) {
    Magic151Steps handlers;

    handlers = D_801EEC24;
    SYS_DISPATCH_TASK(handlers.steps, 3, g_Task);
}

/* When the effect ticker is one, marks every party member's handler busy and loads the dragon-form archive
 * the battler's facing selects. */
MATCH void func_801EF388(void) {
    s32 archive_id;
    u8  i;

    if (g_Task->param.unk_0B == 1) {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            g_Game.members[i].header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
        if (g_BattleEffectBattler->facing < 2) {
            archive_id = D_800B499C[g_Battle.dragon_form][0][0];
        } else {
            archive_id = D_800B499C[g_Battle.dragon_form][1][0];
        }
        EMI_LoadArchive(archive_id);
        g_Task->unk_03 += 1;
    }
}

INCLUDE_ASM(func_801EF484);

MATCH void func_801EF938(void) {
    if (g_Task->param.unk_0B == 2) {
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        g_Game.members[g_Battle.active_battler].u.turn.action_flags.value |= COMBATANT_FLAG_ACTION_UNK_5;
        g_Game.members[g_Battle.active_battler].u.turn.action_flags.value &= ~COMBATANT_FLAG_ABILITY_ALT_POSE;
        func_801E5988();
    }
}

/* func_801EF9F0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EFA34(void) {
    BMagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC38, header.step);
}

MATCH void func_801EFAAC(void) {
    PartyMember* work;
    s32          y;
    u32          slot;

    g_Task->facing           = g_BattleSelectedActor->facing;
    g_Task->pos.x.fixed      = g_EncounterOriginX;
    y                        = g_EncounterOriginY;
    g_Task->pos.y.fixed      = y;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(g_Task->pos.x.fixed, y);
    g_Task->param.unk_0B     = 0;
    g_Task->unk_09           = 4;
    g_Task->header.step += 1;
    slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 2;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].target.party = work;
    g_Task->param.unk_0B += 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
}

MATCH void func_801EFBAC(void) {
    u8           count;
    u32          slot;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 3;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
        g_Task->unk_09 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFC68(void) {
    PartyMember* work;
    PartyMember* task;
    u32          slot;

    if (--g_Task->unk_09 == 0) {
        slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        task                               = g_Task;
        g_BattleEffects[slot].target.party = work;
        task->param.unk_0B += 1;
        SND_QueueSelectionFx(0x103);
        g_Task->unk_09 = 20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD24(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 1;
        g_Task->header.step              = g_Task->header.step + 1;
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

MATCH void func_801EFDC0(void) {
    if (g_Task->param.unk_0B == 0) {
        g_BattleEffectBattler->param.unk_0B = 2;
        func_801E5988();
    }
}

MATCH void func_801EFE00(void) {
    SYS_DISPATCH_BYTE(D_801F24B8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F026C();
        func_801F0648();
        PopMatrix();
    }
}

MATCH void func_801EFE90(void) {
    PartyMember* work  = g_Task;
    PartyMember* actor = g_BattleEffectBattler;
    s32          z;

    work->pos.x.fixed    = actor->pos.x.fixed;
    work->pos.y.fixed    = actor->pos.y.fixed;
    z                    = actor->pos.z.fixed;
    work->unk_5D         = 0x10;
    work->pos.z.fixed    = z;
    g_Task->unk_5E       = 0x10;
    g_Task->unk_5F       = 0x24;
    g_Task->unk_04       = 0;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 30;
    g_Task->header.step += 1;
}

MATCH void func_801EFF44(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if (timer == 32) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EFF94(void) {
    u32          slot;
    PartyMember* work;

    if ((g_FrameCount & 0x3) == 0) {
        slot                               = Battle_AllocEffect(1, 68) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = g_Task->unk_04 & 0xF;
        g_Task->param.unk_0B += 1;
        g_Task->unk_04 += 1;
    }
    if (g_BattleEffectBattler->header.step == 5) {
        if (--g_Task->timer == 0) {
            g_Task->header.step += 1;
        }
    }
}

#include "overlays/bmagic/Effect_StepOnZeroTick.h"

MATCH void func_801F00E8(void) {
    u8 count;

    count          = g_Task->unk_5D - 1;
    g_Task->unk_5D = count;
    if ((s8)count == 8) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F013C(void) {
    s8 count;
    u8 count_next;

    count = g_Task->unk_5D;
    if (count != 0) {
        g_Task->unk_5D = count - 1;
    }
    count_next     = g_Task->unk_5E - 1;
    g_Task->unk_5E = count_next;
    if ((count_next << 0x18) == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F026C);

INCLUDE_ASM(func_801F0648);

/* Draws the glow ring step header.step selects: sets the actor matrix, advances the effect timers and
 * passes the slot's draw row to func_801F0D0C while the step is running. */
MATCH void func_801F0AC8(void) {
    PartyMember* work;

    SYS_DISPATCH_BYTE(D_801F24F0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        work = g_Task;
        work->unk_09 += 2;
        work->unk_0C += 1;
        func_801F0D0C(D_801F24D0[g_Task->unk_04][0] + g_Task->unk_09, D_801F24D0[g_Task->unk_04][1]);
        PopMatrix();
    }
}

MATCH void func_801F0BA8(void) {
    PartyMember* work;
    s32          value;

    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    value                = RANDOM_MASK(0x1F);
    work                 = g_Task;
    work->unk_5D         = 0x10;
    work->unk_0C         = value;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 4;
    g_Task->header.step += 1;
}

MATCH void func_801F0C50(void) {
    u8 timer_next;

    timer_next    = g_Task->timer + 4;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) >= 0x20U) {
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0CB0(void) {
    PartyMember* work;
    s8           timer;

    work         = g_Task;
    timer        = work->unk_5D - 2;
    work->unk_5D = timer;
    if (timer == 0) {
        work               = g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0D0C);

/* Runs the step's handler, projects the battle range and, once the effect is live, sets the rolled actor
 * matrix and draws its three bands. */
MATCH void func_801F10E8(void) {
    SYS_DISPATCH_BYTE(D_801F24FC, g_Task->header.step);
    Battle_ProjectRange();
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrixQuarterRoll();
        func_801F14D0(32, 32, 0x7);
        g_Task->param.unk_0B += 4;
        func_801F14D0(16, 64, 0xF);
        g_Task->param.unk_0B += 4;
        func_801F14D0(16, 96, 0x1F);
        g_Task->param.unk_0B -= 8;
        PopMatrix();
    }
}

MATCH void func_801F11E0(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
        g_Task->param.unk_0B = RANDOM_MASK(0xF);
        g_Task->unk_09       = 0;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F129C(void) {
    g_Task->param.unk_0B += 1;
    g_Task->timer += 4;
    if (g_Task->timer == 16) {
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_Wait.h"

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixQuarterRoll.h"

INCLUDE_ASM(func_801F14D0);

MATCH void func_801F1C3C(void) {
    SYS_DISPATCH_BYTE(D_801F250C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F1DC0();
        BMagic_DrawGlowRingInner();
        BMagic_DrawGlowRingOuter();
        PopMatrix();
    }
}

MATCH void func_801F1CCC(void) {
    PartyMember* work  = g_Task;
    PartyMember* actor = g_BattleEffectBattler;
    s32          z;

    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->unk_09      = 0x10;
    work->unk_14      = 0x100;
    work->pos.z.fixed = z;
    g_Task->header.step += 1;
}

MATCH void func_801F1D28(void) {
    PartyMember* work;
    s32          value;

    work         = g_Task;
    value        = work->unk_14 + 0x80;
    work->unk_14 = value;
    if (value == 0x400) {
        work->header.step++;
    }
}

/* Best 7 differences: lui a0 at 0x801F1D60; adjust register allocation. */
MATCH void func_801F1D60(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->unk_14 += 0x20;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix5(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

/* The glow ring scratch: the inner radius, the outer radius and the shade, then the quad corners (D_1F800014). */
#define GLOW_RING_INNER D_1F800000.view.effect.params[1]
#define GLOW_RING_OUTER D_1F800000.view.effect.params[2]
#define GLOW_RING_SHADE D_1F800000.view.effect.params[5]

/* The inner half of the glow ring: a ring of 64 additive quads from the effect radius (word 0x14) out
 * to 64 past it, brightest at its outer edge. */
MATCH void BMagic_DrawGlowRingInner(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(4, getTPage(0, 1, 320, 256));
    GLOW_RING_INNER  = g_Task->unk_14;
    GLOW_RING_OUTER  = g_Task->unk_14 + 0x40;
    GLOW_RING_SHADE  = g_Task->unk_09 * 15;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    D_1F800014[3].vz = 0;
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 64; i++) {
        prim             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_OUTER);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB1(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(4, sizeof(POLY_G4));
    }
}

/* The outer half of the glow ring: the ring from 64 to 128 past the effect radius, fading out at its outer edge. */
MATCH void BMagic_DrawGlowRingOuter(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(4, getTPage(0, 1, 320, 256));
    GLOW_RING_INNER  = g_Task->unk_14 + 0x40;
    GLOW_RING_OUTER  = g_Task->unk_14 + 0x80;
    GLOW_RING_SHADE  = g_Task->unk_09 * 15;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    D_1F800014[3].vz = 0;
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 64; i++) {
        prim             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_OUTER);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB3(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        GFX_AddPrim(4, sizeof(POLY_G4));
    }
}
