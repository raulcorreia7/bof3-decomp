#include "area030_04.h"

/* Resets the AREA030 scratchpad record for the next state: clears the
 * state, clip, and draw fields, primes the colour step and depth slots, marks
 * the record busy and advances the state byte. */
MATCH void func_801D42E4(void) {
    FishingState* work;
    FishingState* advanced;

    g_Task->direction    = FACING_UP_LEFT;
    g_Task->unk_06       = 0;
    g_Task->option_flags = ACTOR_OPT_NO_TARGET;
    g_Task->timer        = 4;
    g_Task->unk_0A       = 0;

    work              = FISHING_STATE;
    work->saved_index = 0;
    advanced          = FISHING_STATE;

    work->motion.unk_34 = 0;
    work->y_38.pos_y    = 0;
    work->bounce.unk_3C = 0;
    work->pos_x         = 0;
    work->cursor_10     = 0;

    advanced->unk_2C        = 0xFFFF;
    advanced->handler_index = (advanced->handler_index + 1);
}
