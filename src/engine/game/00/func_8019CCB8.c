#include "game_00.h"

MATCH void func_8019CCB8(void) {
    /* FAKE: retail frame is 0x28; the 8 bytes below the saved registers are
     * unexplained by this draft's locals. */
    STACK_PADS(u8, 8);
    s32 copy_count;
    s32 copy_index;
    s32 move_x;
    s32 move_y;
    u8* copy_dst;
    u8  step;

    if (g_GameEntryState != 1) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            func_8019D4BC();
            goto block_9; /* shared tail */
        }
        if (g_SpadWork->unk_0B != 0) {
            g_SpadWork->direction_08 = D_80145E98;
            g_SpadWork->unk_0C       = g_FacingOffsets[g_SpadWork->direction_08].x * 2;
            g_SpadWork->unk_10       = g_FacingOffsets[g_SpadWork->direction_08].y * 2;
            g_SpadWork->unk_09       = 0x10;
            step                     = g_SpadWork->unk_09;
            move_x                   = g_SpadWork->x.fixed;
            move_y                   = g_SpadWork->y.fixed;
            move_x += g_SpadWork->unk_0C * step;
            move_y += g_SpadWork->unk_10 * step;
            func_8019D4BC();
            if (func_8019D054(move_x, move_y) & BYTE_MASK) {
                copy_dst   = (u8*)BATTLE_SCRIPT_BANK;
                copy_count = *g_SpadWork->range_54.table * 0x28;
                copy_index = 0;
                if (copy_count > 0) {
                    do {
                        *copy_dst = *g_SpadWork->source_50;
                        copy_index += 1;
                        g_SpadWork->source_50 = (u8*)g_SpadWork->source_50 + 1;
                        copy_dst += 1;
                    } while (copy_index < copy_count);
                }
                g_SpadWork->source_50 = (u8*)BATTLE_SCRIPT_BANK; /* the same buffer */
                func_8019D648();
                func_8019D9C0();
                SND_PlayCue(EMI_CUE_ID(1, 14));
                g_SpadWork->unk_01 = 3;
                goto block_9; /* shared tail */ /* shared tail */
            }
            func_8019CEDC();
            g_SpadWork->unk_01 += 1;
            return;
        }
        goto block_9; /* shared tail */
    }
block_9:
    if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
        func_8015A944();
    }
}
