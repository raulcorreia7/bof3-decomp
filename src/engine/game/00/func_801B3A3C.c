#include "game_00.h"

/* Per-slot field columns over the work-area array; one shared byte offset,
 * each column keeping its own absolute base for slot addressing. */

MATCH void func_801B3A3C(void) {
    Actor* saved;
    /* FAKE: pin armed work pointer to v0 so the constant keeps v1. */
    FAKE_REG(Actor*, work, "v0");
    s32 off;

    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        return;
    }
    if (g_MessageRequest == 3u) {
        off = g_Game.current->status.field.slot_12D * ACTOR_SIZE;
        if (!(FIELD(u8, D_80146893, off) & 0x1u)) {
            saved = g_Task;
            TASK_SET(((u8*)g_Actors + off));
            Actor_SelectScript(0u);
            g_Task = saved;
        }
    } else {
        off = g_Game.current->status.field.slot_12D * ACTOR_SIZE;
        if (FIELD(u8, D_80146893, off) & 0x1u) {
            FIELD(u8, g_Actors, off) = 0u;
        } else if ((FIELD(u16, D_801468BC, off) == 0u) && (FIELD(u16, D_801468C0, off) == 0u)) {
            Area_SetCellCode(FIELD(s16, D_801468BE, off), FIELD(s16, D_801468C2, off), 0x10);
        }
    }
    if (g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT) {
        work              = g_Task;
        work->header.mode = 0x0Cu;
    } else {
        Actor_RequestScript(g_Task->direction_08);
        g_Task->header.mode = 1u;
    }
    ACTOR_CLEAR_STEP();
}
