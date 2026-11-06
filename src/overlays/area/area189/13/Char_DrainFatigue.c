#include "area189_13.h"

MATCH void Char_DrainFatigue(void) {
    Character* chr;
    s32        i;
    u8         fatigue;

    i   = 0;
    chr = g_Characters;
loop:
    fatigue = chr->fatigue;
    if (fatigue < 9U) {
        chr->fatigue = fatigue + 1;
        Char_RebuildStats(chr);
    }
    i += 1;
    chr += 1;
    if (i < 7) {
        goto loop;
    }
}
