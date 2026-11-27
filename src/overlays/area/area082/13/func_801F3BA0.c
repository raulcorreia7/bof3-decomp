#include "area082_13.h"

MATCH void func_801F3BA0(void) {
    Actor* task;
    s32    vx;
    s32    vy;

    if (g_ScriptVars[0] != 5) {
        return;
    }
    SYS_SetFlag(g_Scenario2Flags + 0x40, 4);
    task               = SELF(Actor);
    vx                 = task->vx;
    vy                 = task->vy;
    task->pos.z.fixed  = 0x3A0;
    task->pos.x.fixed  = ((vx + 0x4B8000) >> 9) - AREA_CELL_ORIGIN;
    task->pos.y.fixed  = ((vy + 0x568000) >> 9) - AREA_CELL_ORIGIN;
    task->vz           = 340000;
    task->screen_y     = 128;
    task->unk_32       = 0;
    task->vy           = 0;
    task->vx           = 0;
    task->param.unk_0B = 2;
    SELF(Actor)->timer = 0;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
    SELF(Actor)->header.step++;
    func_801F4430();
}
