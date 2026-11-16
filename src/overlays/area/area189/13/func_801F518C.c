#include "area189_13.h"

/* Runs one step of the talk-and-turn phase: the pad's turn step decides whether the
 * camera angle advances, the actor walks into the exit cells, or the area message
 * starts. Message path 2 writes the state byte through its pointer, path 3 by name. */
MATCH void func_801F518C(void) {
    u8*  state;
    u16* angle;
    s32  x;
    s32  y;

    if (GAME_SCRIPT_ACTIVE()) {
        return;
    }
    if (g_Game.walk_flags & AREA_WALK_ENTRY_PENDING) {
        return;
    }
    state = &g_GameStateIndex;
    if (*state != GAME_REQUEST_IDLE) {
        return;
    }
    if (func_801F5D6C() & BYTE_MASK) {
        return;
    }
    if (func_801F5EA8() & BYTE_MASK) {
        return;
    }
    switch (func_801F5F3C() & BYTE_MASK) {
        case 0:
            g_Task->timer = 0;
            func_801F5D20();
            break;
        case 1:
            g_Game.current->u.field.mode_12B.u8_value = 1;
            angle                                     = &D_801492DC;
            *angle                                    = (*angle + (s8)g_Task->param.unk_0B) & 0xFFF;
            g_Task->header.step                       = 4;
            break;
        case 2:
            func_801F54B0();
            x = g_Task->pos.x.fixed + g_Task->vx * g_Task->timer;
            y = g_Task->pos.y.fixed + g_Task->vy * g_Task->timer;
            if ((u32)((x >> 24) - 0x10) < 5 && (y >> 24) >= 0x18) {
                Message_StartAreaMessage(MSG_002);
                *state = GAME_REQUEST_MESSAGE;
                func_801F5D20();
                return;
            } else if (SYS_TestFlag(D_80144EF8, 4) && (u32)((x >> 24) - 0x15) < 5 && (y >> 24) < 0xF) {
                MESSAGE_START_WAIT(MSG_003);
                func_801F5D20();
                return;
            }
            g_Task->timer--;
            func_801F559C();
            g_Game.current->u.field.mode_12B.u8_value = 1;
            g_Task->header.step                       = 3;
            break;
    }
}
