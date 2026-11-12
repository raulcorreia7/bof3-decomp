#include "area144_13.h"

MATCH void func_801F30CC(void) {
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);
    /* FAKE: the held constants keep their loads ahead of the row base; plain stores put the base first. */
    u8           one;
    u8           thirty;
    u8           three;
    u8           shade;
    /* FAKE: the stores keep their source order behind one base; plain stores reorder and need a second base. */
    volatile u8* row;
    u16          i;

    i = 0;
    FAKE_HOLD(one, 1);
    FAKE_HOLD(thirty, 30);
    FAKE_HOLD(three, 3);
    FAKE_HOLD(shade, 240);
    row = MEM_PTR(volatile u8, AREA_WORK + 0x16);
    for (; i < 6; i++) {
        row[2]  = one;
        row[3]  = thirty;
        row[1]  = three;
        row[-2] = 0;
        row[-1] = shade;
        row[0]  = 0;
        row += 28;
    }
}
