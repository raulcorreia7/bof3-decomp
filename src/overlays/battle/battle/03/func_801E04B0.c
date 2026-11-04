#include "battle_03.h"

MATCH void func_801E04B0(void) {
    PartyBattler* enemy_work;
    PartyBattler* work;

    enemy_work = g_GameState;
    if (HAS_STATUS(*enemy_work, STATUS_KO)) {
        g_SpadWork->unk_03              = 2;
        g_SpadWork->word_08.byte.unk_0A = 0;
        return;
    }
    work                                = g_SpadWork;
    *(u16*)(((u32)enemy_work + 0x11Cu)) = 0;
    work->unk_0C                        = 0;
    work->unk_10                        = -0x2000;
    func_801DD350((s32)work);
    g_SpadWork->word_08.byte.unk_0A = 4;
    func_801DEE4C();
    SND_QueueSelectionFx(0x205);
    g_SpadWork->unk_03 += 1;
}
