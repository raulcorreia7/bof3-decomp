#include "game_00.h"

MATCH void func_8019B4A0(void) {
    u16* state;
    s32  vx;
    s32  vy;
    s32  span;

    /* Non-volatile view of the shared state word (see func_80196FFC). */
    state = (u16*)&g_SysThreads[0].tail.game_entry.state;
    if (*state != 1) {
        if (TASK(Actor)->unk_0A != 0) {
            if ((func_8019C1E4() & BYTE_MASK) == 0) {
                Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), TASK(Actor)->param.unk_0B);
                TASK(Actor)->unk_0A = (u8)((TASK(Actor)->unk_0A + 1) >> 1);
                vx                  = g_FacingOffsets[TASK(Actor)->direction].x;
                span                = (TASK(Actor)->unk_0A - 1) * 0xC00;
                TASK(Actor)->vx     = vx * 4;
                if ((vx * 4) > 0) {
                    TASK(Actor)->vx = vx * 4 + span;
                } else if ((vx * 4) < 0) {
                    TASK(Actor)->vx = vx * 4 - span;
                }
                vy              = g_FacingOffsets[TASK(Actor)->direction].y;
                TASK(Actor)->vy = vy * 4;
                if ((vy * 4) > 0) {
                    TASK(Actor)->vy = vy * 4 + span;
                } else if ((vy * 4) < 0) {
                    TASK(Actor)->vy = vy * 4 - span;
                }
                TASK(Actor)->gravity = 0;
                TASK(Actor)->vz      = 0;
                if (TASK(Actor)->vx > 0) {
                    TASK(Actor)->unk_18 = -0x400;
                } else if (TASK(Actor)->vx < 0) {
                    TASK(Actor)->unk_18 = 0x400;
                } else {
                    TASK(Actor)->unk_18 = 0;
                }
                if (TASK(Actor)->vy > 0) {
                    TASK(Actor)->unk_1C = -0x400;
                } else if (TASK(Actor)->vy < 0) {
                    TASK(Actor)->unk_1C = 0x400;
                } else {
                    TASK(Actor)->unk_1C = 0;
                }
                TASK(Actor)->gravity = 0;
                Script_Select(1);
                TASK(Actor)->timer       = 0;
                TASK(Actor)->header.mode = TASK(Actor)->header.mode + 1;
            } else {
                Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), TASK(Actor)->param.unk_0B);
                TASK(Actor)->timer       = 0;
                TASK(Actor)->header.mode = 4;
            }
        } else if (g_SysThreads[0].tail.game_entry.request == GAME_REQUEST_AREA_CHANGE) {
            Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), TASK(Actor)->param.unk_0B);
        }
    }
    Area_SetDrawMode();
}
