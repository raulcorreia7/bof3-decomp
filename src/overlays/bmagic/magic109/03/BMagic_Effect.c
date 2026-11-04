#include "magic109_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

INCLUDE_ASM(func_801EEEAC);

INCLUDE_ASM(func_801EEF30);

MATCH void func_801EF008(void) {
    u8  timer;
    s32 offset;

    timer              = g_SpadWork->unk_09 - 2;
    g_SpadWork->unk_09 = timer;
    if (timer == 2) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    func_801EF0F8(g_SpadWork->unk_64);
    if (g_SpadWork->unk_0B == 0) {
        offset             = g_SpadWork->unk_64 + 8;
        g_SpadWork->unk_64 = offset;
        if (offset >= 0x80) {
            g_SpadWork->unk_0B = 1;
        }
    } else {
        offset             = g_SpadWork->unk_64 - 8;
        g_SpadWork->unk_64 = offset;
        if (offset < -0x7F) {
            g_SpadWork->unk_0B = 0;
        }
    }
}

INCLUDE_ASM(func_801EF0F8);
