#include "game_00.h"

MATCH void func_8019B4A0(void) {
    u16* state;
    s32  vx;
    s32  vy;
    s32  span;

    /* Non-volatile view of the shared state word (see func_80196FFC). */
    state = (u16*)&g_GameEntryState;
    if (*state != 1) {
        if (g_Task->unk_0A != 0) {
            if ((func_8019C1E4() & BYTE_MASK) == 0) {
                Area_SetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y), g_Task->param.unk_0B);
                g_Task->unk_0A = (u8)((g_Task->unk_0A + 1) >> 1);
                vx             = g_FacingOffsets[g_Task->direction_08].x;
                span           = (g_Task->unk_0A - 1) * 0xC00;
                g_Task->vx     = vx * 4;
                if ((vx * 4) > 0) {
                    g_Task->vx = vx * 4 + span;
                } else if ((vx * 4) < 0) {
                    g_Task->vx = vx * 4 - span;
                }
                vy         = g_FacingOffsets[g_Task->direction_08].y;
                g_Task->vy = vy * 4;
                if ((vy * 4) > 0) {
                    g_Task->vy = vy * 4 + span;
                } else if ((vy * 4) < 0) {
                    g_Task->vy = vy * 4 - span;
                }
                g_Task->gravity = 0;
                g_Task->vz      = 0;
                if (g_Task->vx > 0) {
                    g_Task->unk_18 = -0x400;
                } else if (g_Task->vx < 0) {
                    g_Task->unk_18 = 0x400;
                } else {
                    g_Task->unk_18 = 0;
                }
                if (g_Task->vy > 0) {
                    g_Task->unk_1C = -0x400;
                } else if (g_Task->vy < 0) {
                    g_Task->unk_1C = 0x400;
                } else {
                    g_Task->unk_1C = 0;
                }
                g_Task->gravity = 0;
                Actor_SelectScript(1);
                g_Task->timer       = 0;
                g_Task->header.mode = g_Task->header.mode + 1;
            } else {
                Area_SetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y), g_Task->param.unk_0B);
                g_Task->timer       = 0;
                g_Task->header.mode = 4;
            }
        } else if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            Area_SetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y), g_Task->param.unk_0B);
        }
    }
    Area_SetDrawMode();
}
