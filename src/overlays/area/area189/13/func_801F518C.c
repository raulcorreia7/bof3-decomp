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
            SELF(Actor)->timer = 0;
            func_801F5D20();
            break;
        case 1:
            g_Game.current->u.field.mode.unsigned_value = 1;
            angle                                       = &D_801492DC;
            *angle                                      = (*angle + (s8)SELF(Actor)->param.unk_0B) & 0xFFF;
            SELF(Actor)->header.step                    = 4;
            break;
        case 2:
            func_801F54B0();
            x = SELF(Actor)->pos.x.fixed + SELF(Actor)->vx * SELF(Actor)->timer;
            y = SELF(Actor)->pos.y.fixed + SELF(Actor)->vy * SELF(Actor)->timer;
            if ((u32)((x >> 24) - 0x10) < 5 && (y >> 24) >= 0x18) {
                UI_MessageStartArea(MSG_AREA189_ASK_RETURN_BASE_CAMP);
                *state = GAME_REQUEST_MESSAGE;
                func_801F5D20();
                return;
            } else if (SYS_TestFlag(g_SceneFlagRows[SCENARIO_DESERT_OF_DEATH], 4) && (u32)((x >> 24) - 0x15) < 5 && (y >> 24) < 0xF) {
                MESSAGE_START_WAIT(MSG_AREA189_ASK_RETURN_OASIS);
                func_801F5D20();
                return;
            }
            SELF(Actor)->timer--;
            func_801F559C();
            g_Game.current->u.field.mode.unsigned_value = 1;
            SELF(Actor)->header.step                    = 3;
            break;
    }
}
