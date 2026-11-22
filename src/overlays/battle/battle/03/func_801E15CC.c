#include "battle_03.h"

MATCH void func_801E15CC(void) {
    func_801DEDE4();
    if (HAS_STATUS(*g_Game.current, STATUS_KO)) {
        TASK(PartyMember)->header.mode = 6;
        TASK(PartyMember)->header.step = 4;
    } else {
        Battle_ClearSlotPending(TASK(PartyMember)->slot);
        TASK(PartyMember)->header.mode = 3;
        TASK(PartyMember)->header.step = 0;
    }
    TASK(PartyMember)->unk_03 = 0;
}
