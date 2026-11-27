#include "area082_13.h"

/* Emit the effect's four sprites, then its ring from the offset table, and advance the step. */
MATCH void func_801F3E08(void) {
    s32 i;
    s32 x;
    s32 y;

    setVector(&g_ScratchPadVectors[0], -0x1A40, -0x14C0, 0x160);
    g_ScratchPadVectors[1].vx = 0x620;
    g_ScratchPadVectors[1].vy = 0;

    i = 0;
    do {
        g_ScratchPadVectors[1].vz = (g_FrameCount << 5) + (i << 10);
        func_801F46C8(SELF(Actor)->timer << 2, 0x1F, 0xE00 + i * 0x400, 0x18);
        i++;
    } while (i < 4);

    if (SELF(Actor)->timer >= 3) {
        g_ScratchPadVectors[0].vz = 0x3A0;
        g_ScratchPadVectors[1].vx = 0x400;
        g_ScratchPadVectors[1].vy = 0;

        i = 0;
        do {
            x                         = D_801F5764[i].x * 3;
            x                         = ((x << 16) + 0x4B8000) >> 9;
            g_ScratchPadVectors[0].vx = x - AREA_CELL_ORIGIN;
            y                         = D_801F5764[i].y * 3;
            y                         = ((y << 16) + 0x568000) >> 9;
            g_ScratchPadVectors[0].vy = y - AREA_CELL_ORIGIN;
            g_ScratchPadVectors[1].vz = (g_FrameCount << 5) + (i << 10);
            func_801F46C8(0, 0x1E, i << 10, 0x10);
            i++;
        } while (i < 4);
    }

    func_801F4430();
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer >= 8) {
        SELF(Actor)->header.step++;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
    }
}
