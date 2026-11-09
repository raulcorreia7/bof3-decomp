#include "magic054_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC2C(void) {
    Magic054Steps table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EEC98);

#include "overlays/bmagic/Effect_Hit.h"

#include "shared/Effect_StartPlaying.h"

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

MATCH void func_801EF158(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF19C(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

INCLUDE_ASM(func_801EF238);

MATCH void func_801EF3A4(void) {
    Actor_StepAnimLoop();
    g_Task->unk_0C += g_Task->unk_18;
    g_Task->unk_10 += g_Task->unk_1C;
    g_Task->scale.x += g_Task->unk_0C;
    g_Task->scale.y += g_Task->unk_10;
    if (g_Task->unk_0C == 0) {
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF43C(void) {
    u8 timer;

    Actor_StepAnimLoop();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->unk_18 = 0x60;
        g_Task->unk_1C = -0x80;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4A8(void) {
    PartyMember* work;

    Actor_StepAnimLoop();
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

    if (Actor_StepAnimOnce() & BYTE_MASK) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            value2                                     = g_Task->param.unk_0B;
            g_BattleEnemyBattlers[value2].header.flags = g_BattleEnemyBattlers[value2].header.flags & 0xBF;
        } else {
            value                              = g_Task->param.unk_0B;
            g_Game.members[value].header.flags = g_Game.members[value].header.flags & ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"
