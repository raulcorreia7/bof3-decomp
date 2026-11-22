#include "battle_03.h"

/* func_801E69C0 */
MATCH void Battle_RaiseScreenFade(void) {
    u8 value;
    u8 next;

    value                       = BATTLE_WORK->unk_09;
    D_1F800002                  = value;
    D_1F800001                  = value;
    g_ScratchPad.cells.bytes[0] = value;
    func_801D99AC(0, 0, 11);
    next                = BATTLE_WORK->unk_09 + 1;
    BATTLE_WORK->unk_09 = next;
    if (next == 0xFFu) {
        BATTLE_WORK->header.mode += 1;
    }
}
