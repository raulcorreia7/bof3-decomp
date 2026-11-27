#include "area091_13.h"

MATCH void func_801F3228(void) {
    Actor* task;
    s32    i;
    u8     cell;
    u32    row;
    u32    col;
    u32    palette;
    u16*   colors;

    if (g_AreaCameraMoving == 0) {
        task                     = SELF(Actor);
        task->pos.x.fixed        = TO_COORD_HALF(31);
        task->voice_flags.raw    = 0;
        task->pos.y.fixed        = TO_COORD(26);
        task->pos.z.part.integer = -0x100;
        task->header.flags &= ~0x40;
        SELF(Actor)->unk_04++;
        i = 0;
        do {
            cell      = SELF(Actor)->clut_select;
            row       = (cell >> 3) * AREA_PALETTE_ROW;
            palette   = AREA_PALETTE_WORK + row;
            col       = (cell & 7) * AREA_PALETTE_UNIT;
            colors    = MEM_PTR(u16, col + palette);
            colors[i] = 0;
            i++;
        } while (i < 32);
        g_GfxPalettePending++;
        SELF(Actor)->param.unk_0B = 0;
        SELF(Actor)->unk_0A       = 2;
    }
    func_801F2ED4(300, 0xFF);
}
