#include "battle_15.h"

MATCH void func_800AE3C0(void) {
    PartyMember* work;
    s8           counter;

    work         = SELF(PartyMember);
    counter      = work->unk_09 - 1;
    work->unk_09 = counter;
    if (counter == -6) {
        SELF(PartyMember)->header.mode++;
    }
    Area_PaletteUpdateTint((s8)SELF(PartyMember)->unk_09);
}
