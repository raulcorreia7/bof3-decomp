#include "boss012_16.h"
#include "area/spad.h"

MATCH void func_800C1978(s32 mode) {
    g_Battle.state |= BATTLE_STATE_EFFECT_LOADING;
    Actor_StepAnimOnce();
    GFX_ClearRect(832, 256, 128, 256);
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_ENEMY, 1));
    g_Task->unk_18   = (s16)g_Task->screen_x;
    g_Task->unk_1C   = (s16)g_Task->screen_y;
    g_Task->screen_x = 50;
    g_Task->screen_y = 65;
    g_Task->gravity  = 0;
    g_Task->active_flags |= 0x88;
    func_800C1C08(FIELD(u16, g_Task, 0x20));
    g_Task->unk_03 = 2;
}
