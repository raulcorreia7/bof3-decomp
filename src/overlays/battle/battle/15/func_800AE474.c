#include "battle_15.h"

MATCH void func_800AE474(void) {
    PartyMember* work;

    work = (PartyMember*)g_Task;
    work->unk_09++;
    if (work->unk_09 == 0) {
        func_801E5988();
    }
    /* Reload: work does not survive the cue call. */
    Area_UpdatePaletteTint((s8)BATTLE_WORK->unk_09);
}
