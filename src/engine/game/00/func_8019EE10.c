#include "game_00.h"

MATCH void func_8019EE10(void) {
    Actor* work;
    Actor* next;

    SELF(Actor)->active_flags = 1;
    FIELD(u16, g_Self, 0x2Cu) = g_Game.members[0].unk_2C.value;
    SELF(Actor)->palette_8bit = PALETTE_TYPE_CELLS_2;
    FIELD(u32, g_Self, 0x4Cu) = D_80145EDC;
    SELF(Actor)->unk_2B       = 1;
    SELF(Actor)->draw_layer   = g_Game.members[0].unk_29;
    /* The work pointer cell is re-read once per store; the second read is kept in
     * its own local so both reads stay in the original load-then-store order. */
    work                      = SELF(Actor);
    work->sheet_page          = 0x1D;
    next                      = SELF(Actor);
    work->voice_flags.raw     = 0;
    next->sheet_row           = 0;
    ACTOR_CLEAR_TINT();
    SELF(Actor)->tint.bytes.flags = 0;
    SELF(Actor)->unk_48           = 0;
}
