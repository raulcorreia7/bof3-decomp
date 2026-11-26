#include "battle_03.h"

MATCH void func_801E15CC(void) {
    func_801DEDE4();
    if (HAS_STATUS(*g_Game.current, STATUS_KO)) {
        SELF(PartyMember)->header.mode = 6;
        SELF(PartyMember)->header.step = 4;
    } else {
        Battle_ClearSlotPending(SELF(PartyMember)->slot);
        SELF(PartyMember)->header.mode = 3;
        SELF(PartyMember)->header.step = 0;
    }
    SELF(PartyMember)->unk_03 = 0;
}
