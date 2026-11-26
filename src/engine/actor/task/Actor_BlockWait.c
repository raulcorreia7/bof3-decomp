#include "engine/game/00/game_00.h"

/* func_8019CCB8 */
/* Waits for Garr's push; slides one step ahead, or shatters when the way ahead is blocked. */
MATCH void Actor_BlockWait(void) {
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
            Actor_BlockReleaseCells();
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
            Actor_BlockReleaseCells();
            if (Actor_BlockIsPathBlocked(move_x, move_y) & BYTE_MASK) {
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
                Actor_ShatterBuildShards();
                Actor_ShatterStartDust();
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 14));
                TASK(Actor)->header.mode = ACTOR_BLOCK_MODE_SHATTER;
                goto block_9;
            }
            Actor_BlockSlide();
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
