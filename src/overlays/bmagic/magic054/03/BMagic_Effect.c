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
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF238(void) {
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        TASK(PartyMember)->pos.x.fixed = g_BattleEnemyBattlers[TASK(PartyMember)->param.unk_0B].pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = g_BattleEnemyBattlers[TASK(PartyMember)->param.unk_0B].pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = g_BattleEnemyBattlers[TASK(PartyMember)->param.unk_0B].pos.z.fixed;
    } else {
        TASK(PartyMember)->pos.x.fixed = g_Game.members[TASK(PartyMember)->param.unk_0B].pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = g_Game.members[TASK(PartyMember)->param.unk_0B].pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = g_Game.members[TASK(PartyMember)->param.unk_0B].pos.z.fixed;
    }
    TASK(PartyMember)->scale.x = 0x10000;
    TASK(PartyMember)->scale.y = 0x10000;
    TASK(PartyMember)->unk_48  = 2;
    TASK(PartyMember)->unk_0C  = -0xC60;
    TASK(PartyMember)->unk_10  = 0x1080;
    TASK(PartyMember)->unk_18  = 0x60;
    TASK(PartyMember)->unk_1C  = -0x80;
    TASK(PartyMember)->header.step++;
}

MATCH void func_801EF3A4(void) {
    Script_AnimStepLoop();
    TASK(PartyMember)->unk_0C += TASK(PartyMember)->unk_18;
    TASK(PartyMember)->unk_10 += TASK(PartyMember)->unk_1C;
    TASK(PartyMember)->scale.x += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->scale.y += TASK(PartyMember)->unk_10;
    if (TASK(PartyMember)->unk_0C == 0) {
        TASK(PartyMember)->unk_09 = 0x10;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF43C(void) {
    u8 timer;

    Script_AnimStepLoop();
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->unk_18 = 0x60;
        TASK(PartyMember)->unk_1C = -0x80;
        TASK(PartyMember)->header.step += 1;
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
            value2                                     = TASK(PartyMember)->param.unk_0B;
            g_BattleEnemyBattlers[value2].header.flags = g_BattleEnemyBattlers[value2].header.flags & 0xBF;
        } else {
            value                              = TASK(PartyMember)->param.unk_0B;
            g_Game.members[value].header.flags = g_Game.members[value].header.flags & ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"
