#include "area103_13.h"

MATCH void func_801F457C(void) {
    u8 ticks;

    /* g_GameEntryState and the entry substate, read as one word. */
    if (*(u32*)&g_GameEntryState == 0x50005 && (D_801EB7CA & 0x4000) != 0) {
        g_Task->header.step++;
    }
    if (g_Task->timer == 15) {
        g_Task->timer = 0;
    }
    ticks = g_Task->timer;
    if ((u8)(ticks % 5) == 0) {
        func_801F4E70((u8)(ticks / 5) + 7);
    }
    g_Task->timer++;
}
