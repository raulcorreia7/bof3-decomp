#include "magic012_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEEAC);
}

INCLUDE_ASM(func_801EEC5C);

MATCH void func_801EEEAC(void) {
    if (g_Task->param.unk_0B == 0) {
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
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EEFF8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF03C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
}

MATCH void func_801EF080(void) {
    u8 value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = 0x20000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        COORD_INT(g_Task->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
        g_Task->param.unk_0B     = RANDOM_MASK(7);
        g_Task->unk_09           = 0x10;
        g_Task->timer            = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF188(void) {
    PartyMember* target;
    VECTOR       pos;

    if (g_FrameCount & 1) {
        g_Task->timer += 1;
    }
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        target = (PartyMember*)&g_BattleEnemyBattlers[g_Task->unk_04];
    } else {
        target = &g_Game.members[g_Task->unk_04];
    }
    pos.vx = (target->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (target->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vz = (COORD_INT(target->pos.z) + 0xC0) >> 1;
    if (Battle_SlotIsBlocked(g_Task->unk_03) & BYTE_MASK) {
        g_Task->unk_0C      = (target->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
        g_Task->unk_10      = (target->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
        g_Task->unk_14      = (COORD_INT(target->pos.z) + 0xC0) >> 1;
        g_Task->header.step = 0xB;
    }
    func_800AF3A0(pos, 0x40);
    if (func_800AF66C((BattleRange*)target, 0x8000)) {
        g_Battle.state |= BATTLE_STATE_DAMAGE_APPLIED;
        Battle_MarkDamaged(g_Task->unk_03);
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_AREA, 0x03));
        g_Task->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - g_Task->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - g_Task->pos.y.fixed);
        g_Task->unk_14 = 0x40;
        g_Task->unk_20 = -8;
        g_Task->header.step += 1;
    }
    Battle_ProjectRange();
    func_801EF79C(g_Task->param.unk_0B, 0);
}

MATCH void func_801EF3C4(void) {
    s32          angle;
    s32          dz;
    u8           count;
    PartyMember* task;

    g_Task->timer += 1;
    g_Task->pos.x.fixed += (rsin(g_Task->unk_0C) << 13) >> 12;
    angle = (rcos(g_Task->unk_0C) << 13) >> 12;
    task  = g_Task;
    task->pos.y.fixed += angle;
    count        = task->unk_09 - 1;
    task->unk_09 = count;
    dz           = task->unk_14 + task->unk_20;
    task->unk_14 = dz;
    task->pos.z.part.integer += dz;
    if (count == 0) {
        g_Task->header.step++;
    }
    Battle_ProjectRange();
    func_801EF79C(g_Task->param.unk_0B, 1);
}

MATCH void func_801EF4B8(void) {
    s32 mode;
    u8  ready;

    ready = 0;
    if (Battle_SlotIsBlocked(g_Task->unk_03) & BYTE_MASK) {
        g_Task->header.step = 0xA;
        return;
    }

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        mode = g_BattleEnemyBattlers[g_Task->unk_04].header.mode;
    } else {
        mode = g_Game.members[g_Task->unk_04].header.mode;
    }

    if (mode != 6) {
        ready = 1;
    }

    if (ready) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = 0x10000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        COORD_INT(g_Task->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
        g_Task->param.unk_0B     = RANDOM_MASK(7);
        g_Task->unk_09           = 0x10;
        g_Task->timer            = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF6A4(void) {
    VECTOR pos;
    u8     count;

    if (g_FrameCount & 0x1) {
        g_Task->timer += 1;
    }
    pos.vx = g_Task->unk_0C;
    pos.vy = g_Task->unk_10;
    pos.vz = g_Task->unk_14;
    func_800AF3A0(pos, 0x30);
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->header.step -= 1;
    }
    func_800AF764();
    func_801EF79C(g_Task->param.unk_0B, 0);
}

MATCH void func_801EF79C(u8 unused, s32 semi) {
    POLY_FT4* prim;
    s32       tpage;
    u8        trans;

    trans = semi;
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = ((semi & 3) << 7) | 0x25;
    } else {
        tpage = ((semi & 3) << 5) | 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.scenario.math_00 = 36;
    D_1F800000.view.scenario.math_04 = g_Task->unk_09 << 3;
    prim                             = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, trans);
    D_1F800000.view.scenario.math_08 = ((g_Task->timer + 13) & 0xF) << 8;
    prim->x0                         = g_Task->unk_2E.half + FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    prim->y0                         = g_Task->unk_30.half + FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    D_1F800000.view.scenario.math_08 = ((g_Task->timer + 11) & 0xF) << 8;
    prim->x1                         = g_Task->unk_2E.half + FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    prim->y1                         = g_Task->unk_30.half + FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    D_1F800000.view.scenario.math_08 = ((g_Task->timer + 3) & 0xF) << 8;
    prim->x2                         = g_Task->unk_2E.half + FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    prim->y2                         = g_Task->unk_30.half + FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    D_1F800000.view.scenario.math_08 = ((g_Task->timer + 5) & 0xF) << 8;
    prim->x3                         = g_Task->unk_2E.half + FIXED_MUL(rcos(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    prim->y3                         = g_Task->unk_30.half + FIXED_MUL(rsin(D_1F800000.view.scenario.math_08), D_1F800000.view.scenario.math_00);
    prim->tpage                      = GetTPage(1, trans, 832, 256);
    prim->clut                       = GetClut(0, 506);
    prim->u0                         = g_Task->param.unk_0B << 5;
    prim->v0                         = 0;
    prim->u1                         = (g_Task->param.unk_0B << 5) + 31;
    prim->v1                         = 0;
    prim->u2                         = g_Task->param.unk_0B << 5;
    prim->v2                         = 64;
    prim->u3                         = (g_Task->param.unk_0B << 5) + 31;
    prim->v3                         = 64;
    setRGB0(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}
