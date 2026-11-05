#include "game_00.h"

MATCH void func_8019B4A0(void) {
    u16* state;
    s32  vx;
    s32  vy;
    s32  span;

    /* Non-volatile view of the shared state word (see func_80196FFC). */
    state = (u16*)&g_GameEntryState;
    if (*state != 1) {
        if (g_SpadWork->unk_0A != 0) {
            if ((func_8019C1E4() & BYTE_MASK) == 0) {
                ((void (*)(s16, s16, s32))Area_SetCellCode)(g_SpadWork->x.part.integer, g_SpadWork->y.part.integer,
                                                            g_SpadWork->unk_0B);
                g_SpadWork->unk_0A = (u8)((g_SpadWork->unk_0A + 1) >> 1);
                vx                 = g_FacingOffsets[g_SpadWork->direction_08].x;
                span               = (g_SpadWork->unk_0A - 1) * 0xC00;
                g_SpadWork->vx     = vx * 4;
                if ((vx * 4) > 0) {
                    g_SpadWork->vx = vx * 4 + span;
                } else if ((vx * 4) < 0) {
                    g_SpadWork->vx = vx * 4 - span;
                }
                vy             = g_FacingOffsets[g_SpadWork->direction_08].y;
                g_SpadWork->vy = vy * 4;
                if ((vy * 4) > 0) {
                    g_SpadWork->vy = vy * 4 + span;
                } else if ((vy * 4) < 0) {
                    g_SpadWork->vy = vy * 4 - span;
                }
                g_SpadWork->gravity = 0;
                g_SpadWork->vz      = 0;
                if (g_SpadWork->vx > 0) {
                    g_SpadWork->unk_18 = -0x400;
                } else if (g_SpadWork->vx < 0) {
                    g_SpadWork->unk_18 = 0x400;
                } else {
                    g_SpadWork->unk_18 = 0;
                }
                if (g_SpadWork->vy > 0) {
                    g_SpadWork->unk_1C = -0x400;
                } else if (g_SpadWork->vy < 0) {
                    g_SpadWork->unk_1C = 0x400;
                } else {
                    g_SpadWork->unk_1C = 0;
                }
                g_SpadWork->gravity = 0;
                Actor_SelectScript(1);
                g_SpadWork->unk_09 = 0;
                g_SpadWork->unk_01 = g_SpadWork->unk_01 + 1;
            } else {
                ((void (*)(s16, s16, s32))Area_SetCellCode)(g_SpadWork->x.part.integer, g_SpadWork->y.part.integer,
                                                            g_SpadWork->unk_0B);
                g_SpadWork->unk_09 = 0;
                g_SpadWork->unk_01 = 4;
            }
        } else if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            ((void (*)(s16, s16, s32))Area_SetCellCode)(g_SpadWork->x.part.integer, g_SpadWork->y.part.integer,
                                                        g_SpadWork->unk_0B);
        }
    }
    Area_SetDrawMode();
}
