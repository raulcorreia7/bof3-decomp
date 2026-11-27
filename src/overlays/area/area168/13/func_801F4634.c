#include "area168_13.h"

MATCH void func_801F4634(void) {
    u8* state;

    if (g_AreaSceneMode & SELF(Actor)->param.unk_0B) {
        state = &g_GameStateIndex;
        if (*state != 2) {
            func_801A4BC0(SELF(Actor)->pos.x.part.integer, SELF(Actor)->pos.y.part.integer, 0xA1);
            func_801A4BC0(SELF(Actor)->pos.x.part.integer, SELF(Actor)->pos.y.part.integer + 1, 0xA1);
            if (*state == 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
            }
            SELF(Actor)->header.step++;
        }
    }
    Area_Update();
}
