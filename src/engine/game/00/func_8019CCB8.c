#include "game_00.h"

MATCH void func_8019CCB8(void) {
    /* FAKE: retail frame is 0x28; the 8 bytes below the saved registers are
     * unexplained by this draft's locals. */
    FAKE_STACK_PADS(u8, 8);
    s32 copy_count;
    s32 copy_index;
    s32 move_x;
    s32 move_y;
    u8* copy_dst;
    u8  step;

    if (g_SysThreads[0].tail.game_entry.state != GAME_MODE_AREA_LOAD) {
        if (g_SysThreads[0].tail.game_entry.request == GAME_REQUEST_AREA_CHANGE) {
            func_8019D4BC();
            goto block_9;
        }
        if (TASK(Actor)->param.unk_0B != 0) {
            TASK(Actor)->direction = g_Game.members[0].facing;
            TASK(Actor)->vx        = g_FacingOffsets[TASK(Actor)->direction].x * 2;
            TASK(Actor)->vy        = g_FacingOffsets[TASK(Actor)->direction].y * 2;
            TASK(Actor)->timer     = 16;
            step                   = TASK(Actor)->timer;
            move_x                 = TASK(Actor)->pos.x.fixed;
            move_y                 = TASK(Actor)->pos.y.fixed;
            move_x += TASK(Actor)->vx * step;
            move_y += TASK(Actor)->vy * step;
            func_8019D4BC();
            if (func_8019D054(move_x, move_y) & BYTE_MASK) {
                copy_dst   = (u8*)BATTLE_SCRIPT_TABLE;
                copy_count = *TASK(Actor)->range_54.table * 0x28;
                copy_index = 0;
                if (copy_count > 0) {
                    do {
                        *copy_dst = *TASK(Actor)->script;
                        copy_index += 1;
                        TASK(Actor)->script = (u8*)TASK(Actor)->script + 1;
                        copy_dst += 1;
                    } while (copy_index < copy_count);
                }
                TASK(Actor)->script = (u8*)BATTLE_SCRIPT_TABLE; /* the same buffer */
                func_8019D648();
                func_8019D9C0();
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 14));
                TASK(Actor)->header.mode = 3;
                goto block_9;
            }
            func_8019CEDC();
            TASK(Actor)->header.mode += 1;
            return;
        }
        goto block_9;
    }
block_9:
    if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
        Actor_ProjectForDraw();
    }
}
