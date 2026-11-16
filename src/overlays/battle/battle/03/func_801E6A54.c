#include "battle_03.h"

MATCH void func_801E6A54(void) {
    volatile PartyMember* work;
    u8                    value;

    ScratchPad* sp;

    work               = g_Task;
    value              = work->unk_09;
    sp                 = SPAD(0u);
    sp->cells.bytes[2] = value;
    sp->cells.bytes[1] = value;
    sp->cells.bytes[0] = value;
    func_801D99AC(0, 0, 11);
}
