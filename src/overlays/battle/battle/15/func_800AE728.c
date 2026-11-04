#include "battle_15.h"

/* EXE-side pointer to the shared battle state record. */

MATCH void func_800AE728(void) {
    PartyBattler* work;
    u8            next;

    work                      = (PartyBattler*)g_SpadWork;
    next                      = work->word_08.byte.unk_09 + 1;
    work->word_08.byte.unk_09 = next;
    if (next == 0x1C) {
        D_801EB4E0->word_08.byte.unk_0B--;
        func_801E5988();
    }
}
