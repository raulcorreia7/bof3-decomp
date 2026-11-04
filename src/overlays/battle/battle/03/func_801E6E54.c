#include "battle_03.h"

MATCH void func_801E6E54(void) {
    PartyBattler* work;
    /* FAKE: Pin the fresh work pointer to a0. */
    MATCH_FAKE_PIN(PartyBattler*, next, "a0");
    s32 index;
    u8  slot;

    g_SpadWork->word_08.byte.unk_0B = 0;
    slot                            = func_801E8FA8();
    index                           = slot & BYTE_MASK;
    if ((index != GAME_NONE) && (s_BattleBattlerStepIds[index] != 0xFF)) {
        g_SpadWork->word_08.byte.unk_0B = slot;
        g_SpadWork->unk_29              = 2;
        g_SpadWork->unk_25              = 5;
        g_SpadWork->unk_26              = 0xF0;
        g_SpadWork->unk_24              = 0x80;
        g_SpadWork->unk_27              = 0xFF;
        g_SpadWork->unk_28              = 0;
        work                            = g_SpadWork;
        work->unk_2B                    = 0;
        next                            = g_SpadWork;
        work->unk_2C.half               = 1;
        next->unk_48                    = 0;
        work                            = g_SpadWork;
        work->unk_44                    = 0x10000;
        work->unk_40                    = 0x10000;
        work->unk_18                    = 0x666;
        work->unk_0C                    = 0;
        work->word_08.byte.unk_0A       = 0x3C;
        func_801E8DD8();
        Actor_SelectScript(s_BattleBattlerStepIds[index]);
        work          = g_SpadWork;
        work->step_01 = (work->step_01) + 2;
    }
}
