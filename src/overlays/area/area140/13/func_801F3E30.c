#include "area140_13.h"

MATCH void func_801F3E30(void) {
    u8  shift_x;
    u8  shift_y;
    u16 x;
    u16 y;
    s32 index;

    if (SYS_TestFlag(g_SceneEventFlags, 0x66) != 0) {
        SELF(Actor)->direction = g_Game.members[0].facing;
        shift_x                = D_80181B00[SELF(Actor)->direction][0];
        shift_y                = D_80181B00[SELF(Actor)->direction][1];
        x                      = COORD_INT(SELF(Actor)->pos.x) + (s8)shift_x;
        y                      = COORD_INT(SELF(Actor)->pos.y) + (s8)shift_y;
        if (g_Game.members[0].unk_09 != 0 && g_Game.members[0].u.field.mode.unsigned_value == 1) {
            if ((func_801F4058(x, y) & BYTE_MASK) == 0) {
                if (((u16)(x - 0x44) < 0xD) && ((u16)(y - 6) < 0xB)) {
                    g_ScriptState->steps = 2;
                    Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
                }
            }
        } else {
            Script_DispatchSelector(SELF(Actor)->direction);
        }
        index = (SELF(Actor)->direction & 0x7) >> 1;
        if ((g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_ACTION]) != 0) {
            g_ScriptState->flags |= 0x40;
            SELF(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
            Script_Select(D_801F4A6C[index * 2]);
            SELF(Actor)->mirror = D_801F4A6D[index * 2];
            func_801F4380(x, y);
        } else {
            g_ScriptState->cursor += 4;
        }
    } else {
        g_ScriptState->cursor += 4;
    }
}
