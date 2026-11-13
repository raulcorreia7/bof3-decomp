#include "battle_03.h"

MATCH void func_801D6E20(void) {
    if ((g_Battle.outcome.options & BATTLE_OPT_KEEP_BGM) == 0u) {
        SND_StopAllSequences();
        SND_PlaySequence(0, 2, 0x64, 0x64);
    }
    Battle_OpenPanel();
    func_801DE60C(0, 2, 0, 0, 255, Message_GetText(0x11));
    g_Battle.phase.sub_step += 1u;
}
