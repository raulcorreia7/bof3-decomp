#include "battle_03.h"

MATCH void func_801E47A4(void) {
    PartyBattler** scratch_slots;
    PartyBattler*  work;

    scratch_slots = SP_PTR(PartyBattler*, 0u);
    work          = scratch_slots[0x11];
    work->unk_48  = 2;
    work          = scratch_slots[0x11];
    work->scale.y = 0x10000u;
    work->scale.x = 0x10000u;
    work->unk_18  = 0x666u;
    work->unk_0C  = 0;
    work->unk_03  = 1;
}
