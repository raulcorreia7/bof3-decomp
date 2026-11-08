#include "start_08.h"

MATCH void func_801E7000(void) {
    s32 resource;

    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    resource = 0xBB;
    if (g_FrameCount & 0x40) {
        resource = 0xBA;
    }
    WinDrawCueText(28, 21, resource);
    func_801E6388(0x20, 0x2B);
    Start_DrawNameEntryControls(D_801ED7E8, 0xA8, 0x2B);
    Menu_DrawWindowFrame(0x12, 0x61, 0x24, 0x11);
    Start_DrawNameEntryGrid(D_801ED7E8, 0x18, 0x67);
    TASK_BYTES[9] = TASK_BYTES[9] + 1;
    if (TASK_BYTES[9] >= 0xA) {
        TASK_BYTES[9] = 0;
        TASK_BYTES[6] = (TASK_BYTES[6] + 1) & 7;
        Actor_SelectScript((TASK_BYTES[6] + 8) & BYTE_MASK);
    }
    Area_AddActor();
    func_8014D978();
}
