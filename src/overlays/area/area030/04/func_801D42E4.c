#include "area030_04.h"

/* Resets the AREA030 scratchpad record for the next state: clears the
 * state, clip, and draw fields, primes the colour step and depth slots, marks
 * the record busy and advances the state byte. */
MATCH void func_801D42E4(void) {
    FishingState* work;
    FishingState* advanced;

    g_Task->direction_08 = FACING_UP_LEFT;
    g_Task->unk_06       = 0;
    g_Task->option_flags = ACTOR_OPT_NO_TARGET;
    g_Task->timer        = 4;
    g_Task->unk_0A       = 0;

    work                 = FISHING_STATE;
    work->saved_index_0B = 0;
    advanced             = FISHING_STATE;

    work->motion_34.unk_34 = 0;
    work->y_38.pos_y       = 0;
    work->bounce_3C.unk_3C = 0;
    work->pos_x_0C         = 0;
    work->cursor_10        = 0;

    advanced->unk_2C           = 0xFFFF;
    advanced->handler_index_01 = (advanced->handler_index_01 + 1);
}
