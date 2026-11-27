#include "battle_03.h"

/* func_801E6A54 */
MATCH void Battle_HoldScreenFade(void) {
    volatile PartyMember* work;
    u8                    value;

    ScratchPad* sp;

    work               = SELF(PartyMember);
    value              = work->unk_09;
    sp                 = SPAD(0u);
    sp->cells.bytes[2] = value;
    sp->cells.bytes[1] = value;
    sp->cells.bytes[0] = value;
    func_801D99AC(0, 0, 11);
}
