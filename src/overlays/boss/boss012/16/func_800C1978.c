#include "boss012_16.h"

MATCH void func_800C1978(s32 mode) {
    g_Battle.flags |= BATTLE_STATE_EFFECT_LOADING;
    Script_AnimStepOnce();
    GFX_ClearRect(832, 256, 128, 256);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_ENEMY, 1));
    SELF(Actor)->unk_18   = (s16)SELF(Actor)->screen_x;
    SELF(Actor)->unk_1C   = (s16)SELF(Actor)->screen_y;
    SELF(Actor)->screen_x = 50;
    SELF(Actor)->screen_y = 65;
    SELF(Actor)->gravity  = 0;
    SELF(Actor)->active_flags |= 0x88;
    func_800C1C08(LOHU(SELF(Actor)->gravity));
    SELF(Actor)->unk_03 = 2;
}
