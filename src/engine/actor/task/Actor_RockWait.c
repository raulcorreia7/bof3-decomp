#include "engine/game/00/game_00.h"

/* func_8019B4A0 */
/* Waits for a kick; sets the roll velocity from its strength and facing, or ends the rock when the way ahead is blocked. */
MATCH void Actor_RockWait(void) {
    u16* state;
    s32  vx;
    s32  vy;
    s32  span;

    /* Non-volatile view of the shared state word (see func_80196FFC). */
    state = (u16*)&g_SysThreads[0].tail.game_entry.state;
    if (*state != 1) {
        if (SELF(Actor)->unk_0A != 0) {
            if ((Actor_RockIsBlockedAhead() & BYTE_MASK) == 0) {
                Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), SELF(Actor)->param.unk_0B);
                SELF(Actor)->unk_0A = (u8)((SELF(Actor)->unk_0A + 1) >> 1);
                vx                  = g_FacingOffsets[SELF(Actor)->direction].x;
                span                = (SELF(Actor)->unk_0A - 1) * 0xC00;
                SELF(Actor)->vx     = vx * 4;
                if ((vx * 4) > 0) {
                    SELF(Actor)->vx = vx * 4 + span;
                } else if ((vx * 4) < 0) {
                    SELF(Actor)->vx = vx * 4 - span;
                }
                vy              = g_FacingOffsets[SELF(Actor)->direction].y;
                SELF(Actor)->vy = vy * 4;
                if ((vy * 4) > 0) {
                    SELF(Actor)->vy = vy * 4 + span;
                } else if ((vy * 4) < 0) {
                    SELF(Actor)->vy = vy * 4 - span;
                }
                SELF(Actor)->gravity = 0;
                SELF(Actor)->vz      = 0;
                if (SELF(Actor)->vx > 0) {
                    SELF(Actor)->unk_18 = -0x400;
                } else if (SELF(Actor)->vx < 0) {
                    SELF(Actor)->unk_18 = 0x400;
                } else {
                    SELF(Actor)->unk_18 = 0;
                }
                if (SELF(Actor)->vy > 0) {
                    SELF(Actor)->unk_1C = -0x400;
                } else if (SELF(Actor)->vy < 0) {
                    SELF(Actor)->unk_1C = 0x400;
                } else {
                    SELF(Actor)->unk_1C = 0;
                }
                SELF(Actor)->gravity = 0;
                Script_Select(1);
                SELF(Actor)->timer       = 0;
                SELF(Actor)->header.mode = SELF(Actor)->header.mode + 1;
            } else {
                Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), SELF(Actor)->param.unk_0B);
                SELF(Actor)->timer       = 0;
                SELF(Actor)->header.mode = ACTOR_ROCK_MODE_END;
            }
        } else if (g_SysThreads[0].tail.game_entry.request == GAME_REQUEST_AREA_CHANGE) {
            Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), SELF(Actor)->param.unk_0B);
        }
    }
    Area_SetDrawMode();
}
