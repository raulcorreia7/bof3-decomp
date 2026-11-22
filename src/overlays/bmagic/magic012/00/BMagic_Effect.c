#include "magic012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEEAC);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EEC5C(void) {
}
#else
INCLUDE_ASM(func_801EEC5C);
#endif

MATCH void func_801EEEAC(void) {
    if (BMAGIC_WORK->param.unk_0B == 0) {
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            g_Game.members[g_Battle.active_battler].chr.hp >>= 1;
            if (g_Game.members[g_Battle.active_battler].chr.hp == 0) {
                g_Game.members[g_Battle.active_battler].chr.hp = 1;
            }
        } else {
            ENEMY_COMBATANT(g_Battle.active_battler).hp >>= 1;
            if (ENEMY_COMBATANT(g_Battle.active_battler).hp == 0) {
                ENEMY_COMBATANT(g_Battle.active_battler).hp = 1;
            }
        }
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EEFF8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF03C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
}

MATCH void func_801EF080(void) {
    u8 value;

    value               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        BMAGIC_WORK->facing = g_BattleEffectBattler->facing;
        BMAGIC_WORK->unk_0C = 0x20000;
        BMAGIC_WORK->unk_10 = 0;
        Effect_RotatePosition(g_Task);
        BMAGIC_WORK->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + BMAGIC_WORK->unk_0C;
        BMAGIC_WORK->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + BMAGIC_WORK->unk_10;
        COORD_INT(BMAGIC_WORK->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
        BMAGIC_WORK->param.unk_0B     = RANDOM_MASK(7);
        BMAGIC_WORK->unk_09           = 0x10;
        BMAGIC_WORK->timer            = 0;
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF188(void) {
    PartyMember* target;
    VECTOR       pos;

    if (g_FrameCount & 1) {
        BMAGIC_WORK->timer += 1;
    }
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        target = (PartyMember*)&g_BattleEnemyBattlers[BMAGIC_WORK->unk_04];
    } else {
        target = &g_Game.members[BMAGIC_WORK->unk_04];
    }
    setVector(&pos, (target->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (target->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (COORD_INT(target->pos.z) + 0xC0) >> 1);
    if (Battle_SlotIsBlocked(BMAGIC_WORK->unk_03) & BYTE_MASK) {
        BMAGIC_WORK->unk_0C      = (target->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
        BMAGIC_WORK->unk_10      = (target->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
        BMAGIC_WORK->unk_14      = (COORD_INT(target->pos.z) + 0xC0) >> 1;
        BMAGIC_WORK->header.step = 0xB;
    }
    Battle_StepRangeToward(pos, 0x40);
    if (func_800AF66C((BattleRange*)target, 0x8000)) {
        g_Battle.flags |= BATTLE_STATE_DAMAGE_APPLIED;
        Battle_MarkDamaged(BMAGIC_WORK->unk_03);
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_AREA, 0x03));
        BMAGIC_WORK->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - BMAGIC_WORK->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - BMAGIC_WORK->pos.y.fixed);
        BMAGIC_WORK->unk_14 = 0x40;
        BMAGIC_WORK->unk_20 = -8;
        BMAGIC_WORK->header.step += 1;
    }
    Battle_ProjectRange();
    func_801EF79C(BMAGIC_WORK->param.unk_0B, 0);
}

MATCH void func_801EF3C4(void) {
    s32          angle;
    s32          dz;
    u8           count;
    PartyMember* task;

    BMAGIC_WORK->timer += 1;
    BMAGIC_WORK->pos.x.fixed += (rsin(BMAGIC_WORK->unk_0C) << 13) >> 12;
    angle = (rcos(BMAGIC_WORK->unk_0C) << 13) >> 12;
    task  = g_Task;
    task->pos.y.fixed += angle;
    count        = task->unk_09 - 1;
    task->unk_09 = count;
    dz           = task->unk_14 + task->unk_20;
    task->unk_14 = dz;
    task->pos.z.part.integer += dz;
    if (count == 0) {
        BMAGIC_WORK->header.step++;
    }
    Battle_ProjectRange();
    func_801EF79C(BMAGIC_WORK->param.unk_0B, 1);
}

MATCH void func_801EF4B8(void) {
    s32 mode;
    u8  ready;

    ready = 0;
    if (Battle_SlotIsBlocked(BMAGIC_WORK->unk_03) & BYTE_MASK) {
        BMAGIC_WORK->header.step = 0xA;
        return;
    }

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        mode = g_BattleEnemyBattlers[BMAGIC_WORK->unk_04].header.mode;
    } else {
        mode = g_Game.members[BMAGIC_WORK->unk_04].header.mode;
    }

    if (mode != 6) {
        ready = 1;
    }

    if (ready) {
        BMAGIC_WORK->facing = g_BattleEffectBattler->facing;
        BMAGIC_WORK->unk_0C = 0x10000;
        BMAGIC_WORK->unk_10 = 0;
        Effect_RotatePosition(g_Task);
        BMAGIC_WORK->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + BMAGIC_WORK->unk_0C;
        BMAGIC_WORK->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + BMAGIC_WORK->unk_10;
        COORD_INT(BMAGIC_WORK->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
        BMAGIC_WORK->param.unk_0B     = RANDOM_MASK(7);
        BMAGIC_WORK->unk_09           = 0x10;
        BMAGIC_WORK->timer            = 0;
        BMAGIC_WORK->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801EF6A4(void) {
    VECTOR pos;
    u8     count;

    if (g_FrameCount & 0x1) {
        BMAGIC_WORK->timer += 1;
    }
    setVector(&pos, BMAGIC_WORK->unk_0C, BMAGIC_WORK->unk_10, BMAGIC_WORK->unk_14);
    Battle_StepRangeToward(pos, 0x30);
    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        BMAGIC_WORK->header.step -= 1;
    }
    func_800AF764();
    func_801EF79C(BMAGIC_WORK->param.unk_0B, 0);
}

MATCH void func_801EF79C(u8 unused, s32 semi) {
    POLY_FT4* prim;
    s32       tpage;
    u8        trans;

    trans = semi;
    tpage = getTPage(TPAGE_DEPTH_4BIT, semi, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.words[0] = 36;
    g_ScratchPad.cells.words[1] = BMAGIC_WORK->unk_09 << 3;
    prim                        = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, trans);
    g_ScratchPad.cells.words[2] = ((BMAGIC_WORK->timer + 13) & 0xF) << 8;
    setXY0(prim, BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]),
           BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]));
    g_ScratchPad.cells.words[2] = ((BMAGIC_WORK->timer + 11) & 0xF) << 8;
    prim->x1                    = BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
    prim->y1                    = BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
    g_ScratchPad.cells.words[2] = ((BMAGIC_WORK->timer + 3) & 0xF) << 8;
    prim->x2                    = BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
    prim->y2                    = BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
    g_ScratchPad.cells.words[2] = ((BMAGIC_WORK->timer + 5) & 0xF) << 8;
    prim->x3                    = BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
    prim->y3                    = BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
    prim->tpage                 = GetTPage(TPAGE_DEPTH_8BIT, trans, 832, 256);
    prim->clut                  = GetClut(0, 506);
    setUV4(prim, BMAGIC_WORK->param.unk_0B << 5, 0, (BMAGIC_WORK->param.unk_0B << 5) + 31, 0, BMAGIC_WORK->param.unk_0B << 5, 64, (BMAGIC_WORK->param.unk_0B << 5) + 31, 64);
    setRGB0(prim, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(POLY_FT4));
}
