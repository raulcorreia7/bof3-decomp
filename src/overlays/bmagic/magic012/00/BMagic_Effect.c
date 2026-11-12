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

INCLUDE_ASM(func_801EF188);

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
    if (func_801DB524(g_Task->unk_03) & BYTE_MASK) {
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

INCLUDE_ASM(func_801EF79C);
