#include "battle_15.h"

MATCH void func_800AE3C0(void) {
    PartyMember* work;
    s8           counter;

    work         = (PartyMember*)g_Task;
    counter      = work->unk_09 - 1;
    work->unk_09 = counter;
    if (counter == -6) {
        BATTLE_WORK->header.mode++;
    }
    Area_UpdatePaletteTint((s8)BATTLE_WORK->unk_09);
}
