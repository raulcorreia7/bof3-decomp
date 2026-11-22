#include "area103_13.h"

MATCH void func_801F457C(void) {
    u32* state;
    u8   ticks;

    /* g_GameEntryState and the entry substate, read as one word. */
    state = (u32*)&g_GameEntryState;
    if (*state == 0x50005 && (D_801EB7CA & 0x4000) != 0) {
        TASK(Actor)->header.step++;
    }
    if (TASK(Actor)->timer == 15) {
        TASK(Actor)->timer = 0;
    }
    ticks = TASK(Actor)->timer;
    if ((u8)(ticks % 5) == 0) {
        func_801F4E70((u8)(ticks / 5) + 7);
    }
    TASK(Actor)->timer++;
}
