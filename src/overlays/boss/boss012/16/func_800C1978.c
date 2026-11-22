#include "boss012_16.h"

MATCH void func_800C1978(s32 mode) {
    g_Battle.flags |= BATTLE_STATE_EFFECT_LOADING;
    Script_AnimStepOnce();
    GFX_ClearRect(832, 256, 128, 256);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_ENEMY, 1));
    TASK(Actor)->unk_18   = (s16)TASK(Actor)->screen_x;
    TASK(Actor)->unk_1C   = (s16)TASK(Actor)->screen_y;
    TASK(Actor)->screen_x = 50;
    TASK(Actor)->screen_y = 65;
    TASK(Actor)->gravity  = 0;
    TASK(Actor)->active_flags |= 0x88;
    func_800C1C08(LOHU(TASK(Actor)->gravity));
    TASK(Actor)->unk_03 = 2;
}
