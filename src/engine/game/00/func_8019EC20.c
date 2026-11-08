#include "game_00.h"

MATCH void func_8019EC20(void) {
    Actor* work;

    work = (Actor*)g_Task;
    work->pos.x.fixed += work->vx;
    work->pos.y.fixed += work->vy;
    if (FIELD(u16, MAP_BUNDLE_BASE,
              (COORD_INT(work->pos.y) * MEM(u8, MAP_BUNDLE_BASE) * 2 + D_80104002 * 4 + COORD_INT(work->pos.x) * 2)) !=
        0) {
        if (func_8019EEE4()) {
            func_8019EE10();
            ((Actor*)g_Task)->unk_27 = g_Game.members[0].unk_27;
            Actor_SelectScript(0x4A);
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 14));
            ((Actor*)g_Task)->header.mode++;
            return;
        }
        if (--((Actor*)g_Task)->unk_0A != 0) {
            return;
        }
    }
    Actor_Clear();
}
