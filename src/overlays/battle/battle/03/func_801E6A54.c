#include "battle_03.h"

MATCH void func_801E6A54(void) {
    volatile PartyBattler* work;
    u8                     value;

    ScratchPad* sp;

    work                     = g_SpadWork;
    value                    = work->word_08.byte.unk_09;
    sp                       = SPAD(0u);
    sp->view.battle.state_02 = value;
    sp->view.battle.state_01 = value;
    sp->view.battle.state_00 = value;
    func_801D99AC(0, 0, 11);
}
