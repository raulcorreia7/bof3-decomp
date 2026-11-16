#include "area091_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3228(void) {
    Actor* task;
    s32    i;
    u8     cell;
    u32    row;
    u32    col;
    u32    addr;
    u16*   colors;

    if (g_AreaCameraMoving == 0) {
        task                     = (Actor*)g_Task;
        task->pos.x.fixed        = TO_COORD_HALF(31);
        task->state_70.word      = 0;
        task->pos.y.fixed        = TO_COORD(26);
        task->pos.z.part.integer = -0x100;
        task->header.flags &= ~0x40;
        g_Task->unk_04++;
        i = 0;
        do {
            cell      = ((Actor*)g_Task)->unk_27;
            row       = (cell >> 3) * AREA_PALETTE_ROW;
            col       = (cell & 7) * AREA_PALETTE_UNIT;
            addr      = AREA_PALETTE_WORK + row + col;
            colors    = MEM_PTR(u16, addr);
            colors[i] = 0;
            i++;
        } while (i < 32);
        g_GfxPalettePending++;
        ((Actor*)g_Task)->param.unk_0B = 0;
        ((Actor*)g_Task)->unk_0A       = 2;
    }
    func_801F2ED4(300, 0xFF);
}
#else
INCLUDE_ASM(func_801F3228);
#endif
