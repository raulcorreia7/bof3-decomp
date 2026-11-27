#include "magic038_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    u16          i;
    u8           slot;
    PartyMember* task;
    PartyMember* work;
    u16*         dst;
    u16*         src;
    u16*         row_dst;
    u16*         row_src;

    Battle_CenterCamera();
    task               = SELF(PartyMember);
    task->param.unk_0B = 0;
    task->pos.z.fixed += TO_COORD(0x200);
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->header.mode += 1;
    for (i = 0; i < 16; i++) {
        slot                               = Battle_AllocEffect(1, 89);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    /* Copies the first two CLUTs of arena palette row 26 into the work copy as they are, then row 2 with STP set. */
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    i       = 0;
    row_dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    row_src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    for (; i < 16; i++) {
        row_dst[i] = row_src[i] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors[0];
    g_GfxPalettePending                                        = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EEE14(void) {
    u8           i;
    u8           slot;
    PartyMember* work;

    if (SELF(PartyMember)->param.unk_0B == 0) {
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 1));
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            for (i = 0; i < 8; i++) {
                if (!Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT))) {
                    slot                               = Battle_AllocEffect(1, 89);
                    work                               = SELF(PartyMember);
                    g_BattleEffects[slot].header.mode  = 1;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].unk_04       = 2;
                    g_BattleEffects[slot].target.party = work;
                    g_BattleEffects[slot].pos.x        = g_BattleEnemyBattlers[i].pos.x;
                    g_BattleEffects[slot].pos.y        = g_BattleEnemyBattlers[i].pos.y;
                    g_BattleEffects[slot].pos.z        = g_BattleEnemyBattlers[i].pos.z;
                    SELF(PartyMember)->param.unk_0B += 1;
                }
            }
        } else {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!Battle_SlotIsBlocked(i)) {
                    slot                               = Battle_AllocEffect(1, 89);
                    work                               = SELF(PartyMember);
                    g_BattleEffects[slot].header.mode  = 1;
                    g_BattleEffects[slot].unk_04       = 2;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].target.party = work;
                    g_BattleEffects[slot].pos.x        = g_Game.members[i].pos.x;
                    g_BattleEffects[slot].pos.y        = g_Game.members[i].pos.y;
                    g_BattleEffects[slot].pos.z        = g_Game.members[i].pos.z;
                    SELF(PartyMember)->param.unk_0B += 1;
                }
            }
        }
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EF0D0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF114(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF9A8 + 1, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF1AC(void) {
    u8           timer;
    s8           tint;
    PartyMember* work;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->unk_0C      = 0;
        SELF(PartyMember)->unk_14      = 0;
        g_ScratchPad.cells.words[0]    = (SELF(PartyMember)->unk_0C & 0x7F) << 5;
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(g_ScratchPad.cells.words[0]), 0x40000);
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(g_ScratchPad.cells.words[0]), 0x40000);
        g_ScratchPad.cells.words[0]    = (SELF(PartyMember)->unk_14 & 0x3F) << 6;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + FIXED_MUL(rsin(g_ScratchPad.cells.words[0]), 0x800000);
        SELF(PartyMember)->unk_25      = 29;
        SELF(PartyMember)->unk_26      = 0;
        SELF(PartyMember)->unk_27      = 32;
        SELF(PartyMember)->unk_28      = 0;
        SELF(PartyMember)->unk_24      = 0;
        SELF(PartyMember)->header.flags |= 0x20;
        SELF(PartyMember)->unk_5C = 1;
        tint                      = -0x80;
        SELF(PartyMember)->unk_5D = tint;
        SELF(PartyMember)->unk_5E = tint;
        SELF(PartyMember)->unk_5F = tint;
        SELF(PartyMember)->unk_2A = 0;
        SELF(PartyMember)->unk_29 = 4;
        work                      = SELF(PartyMember);
        work->unk_2B              = 0;
        work->unk_2C.value        = 0;
        Script_Select(D_801EF9C0[SELF(PartyMember)->param.unk_0B]);
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF3BC(void) {
    PartyMember* work;

    Script_AnimStepLoop();
    SELF(PartyMember)->unk_5D += 4;
    SELF(PartyMember)->unk_5E += 4;
    SELF(PartyMember)->unk_5F += 4;
    work                           = SELF(PartyMember);
    g_ScratchPad.cells.words[0]    = (++work->unk_0C & 0x7F) << 5;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(g_ScratchPad.cells.words[0]), 0x20000);
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(g_ScratchPad.cells.words[0]), 0x20000);
    work                           = SELF(PartyMember);
    g_ScratchPad.cells.words[0]    = (++work->unk_14 & 0x3F) << 6;
    g_ScratchPad.cells.words[1]    = 0x800;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + rsin(g_ScratchPad.cells.words[0]) * g_ScratchPad.cells.words[1];
    if ((s8)SELF(PartyMember)->unk_5D == -0x40) {
        SELF(PartyMember)->header.flags &= 0xDF;
        SELF(PartyMember)->unk_5C = 0;
        SELF(PartyMember)->unk_5D = 0;
        SELF(PartyMember)->unk_5E = 0;
        SELF(PartyMember)->unk_5F = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Circles the effect round the battler on its two counters, bobbing it by a radius of 0x800, and at
 * the 256th step darkens it and advances the step. */
MATCH void func_801EF590(void) {
    PartyMember* work;
    s8           tint;

    Script_AnimStepLoop();
    work                           = SELF(PartyMember);
    g_ScratchPad.cells.words[0]    = (++work->unk_0C & 0x7F) << 5;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(g_ScratchPad.cells.words[0]), 0x20000);
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(g_ScratchPad.cells.words[0]), 0x20000);
    work                           = SELF(PartyMember);
    g_ScratchPad.cells.words[0]    = (++work->unk_14 & 0x3F) << 6;
    g_ScratchPad.cells.words[1]    = 0x800;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + rsin(g_ScratchPad.cells.words[0]) * g_ScratchPad.cells.words[1];
    if (SELF(PartyMember)->unk_0C == 0x100) {
        SELF(PartyMember)->header.flags |= 0x20;
        SELF(PartyMember)->unk_5C = 1;
        tint                      = -0x40;
        SELF(PartyMember)->unk_5D = tint;
        SELF(PartyMember)->unk_5E = tint;
        SELF(PartyMember)->unk_5F = tint;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF710(void) {
    PartyMember* work;
    s8           tint = -0x80;

    SELF(PartyMember)->unk_5D -= 4;
    SELF(PartyMember)->unk_5E -= 4;
    SELF(PartyMember)->unk_5F -= 4;
    Script_AnimStepLoop();
    work                           = SELF(PartyMember);
    g_ScratchPad.cells.words[0]    = (++work->unk_0C & 0x7F) << 5;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(g_ScratchPad.cells.words[0]), 0x20000);
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(g_ScratchPad.cells.words[0]), 0x20000);
    work                           = SELF(PartyMember);
    g_ScratchPad.cells.words[0]    = (++work->unk_14 & 0x3F) << 6;
    g_ScratchPad.cells.words[1]    = 0x800;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + rsin(g_ScratchPad.cells.words[0]) * g_ScratchPad.cells.words[1];
    SELF(PartyMember)->unk_5D      = tint;
    SELF(PartyMember)->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801EF8B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 11), 2, g_Self);
}

#include "overlays/bmagic/shared/Effect_QueueEntry.h"

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"
