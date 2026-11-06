#include "magic054_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC2C(void) {
    BattleHandlerTable4 table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.handlers, 1, g_Task);
}

INCLUDE_ASM(func_801EEC98);

#include "overlays/bmagic/Effect_MarkTargetDamagedOnTickerZero.h"

#include "shared/Effect_StartPlaying.h"

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

MATCH void func_801EF158(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

INCLUDE_ASM(func_801EF19C);

INCLUDE_ASM(func_801EF238);

MATCH void func_801EF3A4(void) {
    func_8014D978();
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
    u8 temp_v0;

    func_8014D978();
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->unk_18 = 0x60;
        g_Task->unk_1C = -0x80;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4A8(void) {
    PartyBattler* work;

    func_8014D978();
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

    if (func_8014DAEC() & 0xFF) {
        if (g_BattleTargetSelector & BATTLE_TARGET_ENEMY_SIDE) {
            value2                                     = g_Task->unk_0B;
            g_BattleEnemyBattlers[value2].header.flags = g_BattleEnemyBattlers[value2].header.flags & 0xBF;
        } else {
            value = g_Task->unk_0B;
            g_BattlePartyBattlers[value].header.flags =
                g_BattlePartyBattlers[value].header.flags & ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
        }
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"
