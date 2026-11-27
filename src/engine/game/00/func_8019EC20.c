#include "game_00.h"

MATCH void func_8019EC20(void) {
    Actor* work;

    work = SELF(Actor);
    work->pos.x.fixed += work->vx;
    work->pos.y.fixed += work->vy;
    if (FIELD(u16, MAP_BUNDLE_BASE, (COORD_INT(work->pos.y) * MEM(u8, MAP_BUNDLE_BASE) * 2 + g_AreaMapBundle.grid_offset * 4 + COORD_INT(work->pos.x) * 2)) != 0) {
        if (func_8019EEE4()) {
            func_8019EE10();
            SELF(Actor)->clut_select = g_Game.members[0].unk_27;
            Script_Select(0x4A);
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 14));
            SELF(Actor)->header.mode++;
            return;
        }
        if (--SELF(Actor)->unk_0A != 0) {
            return;
        }
    }
    Actor_Clear();
}
