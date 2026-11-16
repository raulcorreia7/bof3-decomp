#include "area140_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3E30(void) {
    u8  shift_x;
    u8  shift_y;
    u16 x;
    u16 y;
    s32 index;

    if (SYS_TestFlag(g_SceneEventFlags, 0x66) != 0) {
        g_Task->direction_08 = g_Game.members[0].facing;
        shift_x              = D_80181B00[g_Task->direction_08 * 2];
        shift_y              = D_80181B01[g_Task->direction_08 * 2];
        x                    = COORD_INT(g_Task->pos.x) + (s8)shift_x;
        y                    = COORD_INT(g_Task->pos.y) + (s8)shift_y;
        if (g_Game.members[0].unk_09 != 0) {
            if (g_Game.members[0].u.field.mode_12B.u8_value == 1) {
                if ((func_801F4058(x, y) & BYTE_MASK) == 0) {
                    if (((u16)(x - 0x44) < 0xD) && ((u16)(y - 6) < 0xB)) {
                        g_ScriptState->unk_07 = 2;
                        Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
                    }
                }
            }
        } else {
            func_8015BAC4(g_Task->direction_08);
        }
        index = (g_Task->direction_08 & 0x7) >> 1;
        if ((g_InputPressed & g_InputMasks[INPUT_SLOT_ACTION]) != 0) {
            g_ScriptState->flag_00 |= 0x40;
            g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
            Actor_SelectScript(D_801F4A6C[index * 2]);
            g_Task->unk_2A = D_801F4A6D[index * 2];
            func_801F4380(x, y);
        } else {
            g_ScriptState->cursor += 4;
        }
    } else {
        g_ScriptState->cursor += 4;
    }
}
#else
INCLUDE_ASM(func_801F3E30);
#endif
