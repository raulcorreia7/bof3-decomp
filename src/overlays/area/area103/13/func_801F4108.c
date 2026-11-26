#include "area103_13.h"

/* Steps the entry overlay: the entry gate advances once, the timer wraps at 15
 * frames, every fifth frame moves the beat, and the overlay steps. */
MATCH void func_801F4108(void) {
    u32* state;
    u8   ticks;

    /* g_GameEntryState and the entry substate, read as one word. */
    state = (u32*)&g_GameEntryState;
    if (*state == 0x50005 && (*FIELD_PTR(u16, D_801EB6B2, 0) & 0x4000) != 0) {
        SELF(Actor)->header.step++;
    }
    if (SELF(Actor)->timer == 15) {
        SELF(Actor)->timer = 0;
    }
    ticks = SELF(Actor)->timer;
    if ((u8)(ticks % 5) == 0) {
        func_801F4E70((u8)(ticks / 5) + 7);
    }
    SELF(Actor)->timer++;
    func_801F49A0(1);
}
