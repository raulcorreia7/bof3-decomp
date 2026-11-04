#include "battle_15.h"

MATCH void func_800AE474(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_SpadWork;
    work->word_08.byte.unk_09++;
    if (work->word_08.byte.unk_09 == 0) {
        func_801E5988();
    }
    /* Reload: work does not survive the cue call. */
    Area_UpdatePaletteTint((s8)BATTLE_WORK->word_08.byte.unk_09);
}
