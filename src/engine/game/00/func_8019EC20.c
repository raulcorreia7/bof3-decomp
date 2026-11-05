#include "game_00.h"

MATCH void func_8019EC20(void) {
    Actor* work;

    work = (Actor*)g_SpadWork;
    work->x.fixed += work->vx;
    work->y.fixed += work->vy;
    if (FIELD(u16, MAP_BUNDLE_BASE,
              (work->y.part.integer * MEM(u8, MAP_BUNDLE_BASE) * 2 + D_80104002 * 4 + work->x.part.integer * 2)) != 0) {
        if (func_8019EEE4()) {
            func_8019EE10();
            ((Actor*)g_SpadWork)->unk_27 = D_80145EB7;
            Actor_SelectScript(0x4A);
            SND_PlayCue(EMI_CUE_ID(1, 14));
            ((Actor*)g_SpadWork)->unk_01++;
            return;
        }
        if (--((Actor*)g_SpadWork)->unk_0A != 0) {
            return;
        }
    }
    Actor_Clear();
}
