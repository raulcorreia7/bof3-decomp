#include "magic054_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC2C(void) {
    Magic054Steps table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EEC98(void) {
}
#else
INCLUDE_ASM(func_801EEC98);
#endif

#include "overlays/bmagic/shared/Effect_Hit.h"

#include "shared/Effect_StartPlaying.h"

#include "overlays/bmagic/shared/Effect_CountDownAndMarkDamaged.h"

/* func_801EF158 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF19C(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_BYTE(handlers.steps, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF238(void) {
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        BMAGIC_WORK->pos.x.fixed = g_BattleEnemyBattlers[BMAGIC_WORK->param.unk_0B].pos.x.fixed;
        BMAGIC_WORK->pos.y.fixed = g_BattleEnemyBattlers[BMAGIC_WORK->param.unk_0B].pos.y.fixed;
        BMAGIC_WORK->pos.z.fixed = g_BattleEnemyBattlers[BMAGIC_WORK->param.unk_0B].pos.z.fixed;
    } else {
        BMAGIC_WORK->pos.x.fixed = g_Game.members[BMAGIC_WORK->param.unk_0B].pos.x.fixed;
        BMAGIC_WORK->pos.y.fixed = g_Game.members[BMAGIC_WORK->param.unk_0B].pos.y.fixed;
        BMAGIC_WORK->pos.z.fixed = g_Game.members[BMAGIC_WORK->param.unk_0B].pos.z.fixed;
    }
    BMAGIC_WORK->scale.x = 0x10000;
    BMAGIC_WORK->scale.y = 0x10000;
    BMAGIC_WORK->unk_48  = 2;
    BMAGIC_WORK->unk_0C  = -0xC60;
    BMAGIC_WORK->unk_10  = 0x1080;
    BMAGIC_WORK->unk_18  = 0x60;
    BMAGIC_WORK->unk_1C  = -0x80;
    BMAGIC_WORK->header.step++;
}

MATCH void func_801EF3A4(void) {
    Script_AnimStepLoop();
    BMAGIC_WORK->unk_0C += BMAGIC_WORK->unk_18;
    BMAGIC_WORK->unk_10 += BMAGIC_WORK->unk_1C;
    BMAGIC_WORK->scale.x += BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->scale.y += BMAGIC_WORK->unk_10;
    if (BMAGIC_WORK->unk_0C == 0) {
        BMAGIC_WORK->unk_09 = 0x10;
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF43C(void) {
    u8 timer;

    Script_AnimStepLoop();
    timer               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        BMAGIC_WORK->unk_18 = 0x60;
        BMAGIC_WORK->unk_1C = -0x80;
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF4A8(void) {
    PartyMember* work;

    Script_AnimStepLoop();
    work = g_Task;
    work->unk_0C += work->unk_18;
    work->unk_10 += work->unk_1C;
    work->scale.x += work->unk_0C;
    work->scale.y += work->unk_10;
    if (work->unk_0C == 0xC00) {
        work->header.step++;
    }
}

MATCH void func_801EF534(void) {
    u8 value;
    u8 value2;

    if (Script_AnimStepOnce() & BYTE_MASK) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            value2                                     = BMAGIC_WORK->param.unk_0B;
            g_BattleEnemyBattlers[value2].header.flags = g_BattleEnemyBattlers[value2].header.flags & 0xBF;
        } else {
            value                              = BMAGIC_WORK->param.unk_0B;
            g_Game.members[value].header.flags = g_Game.members[value].header.flags & ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
        BMAGIC_WORK->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"
