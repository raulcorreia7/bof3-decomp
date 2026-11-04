#include "area172_13.h"

MATCH void func_801F2D98(void) {
    PartyBattler* work;

    work                      = g_SpadWork;
    work->word_08.byte.unk_09 = work->word_08.byte.unk_09 - 1;
    if (g_SpadWork->unk_09 == 0) {
        func_80196070();
    }
    func_801F2DF4(1);
}
