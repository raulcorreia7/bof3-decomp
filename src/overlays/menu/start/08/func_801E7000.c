#include "start_08.h"
#include "area/spad.h"

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
    Menu_DrawNameEntryControls(D_801ED7E8, 0xA8, 0x2B);
    Menu_DrawWindowFrame(18, 97, 36, 17);
    Menu_DrawNameEntryGrid(D_801ED7E8, 0x18, 0x67);
    g_Task->timer = g_Task->timer + 1;
    if (g_Task->timer >= 10) {
        g_Task->timer  = 0;
        g_Task->unk_06 = (g_Task->unk_06 + 1) & 0x7;
        Actor_SelectScript((g_Task->unk_06 + 8) & BYTE_MASK);
    }
    Area_AddActor();
    Actor_StepAnimLoop();
}
