#include "battle_15.h"

MATCH void func_800AE474(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->unk_09++;
    if (work->unk_09 == 0) {
        Effect_Reset();
    }
    /* Reload: work does not survive the cue call. */
    Area_PaletteUpdateTint((s8)SELF(PartyMember)->unk_09);
}
