#include "start_08.h"

MATCH void func_801E7000(void) {
    s32 resource;

    Menu_DrawClutStrip(g_WindowClut);
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
    TASK(Actor)->timer = TASK(Actor)->timer + 1;
    if (TASK(Actor)->timer >= 10) {
        TASK(Actor)->timer  = 0;
        TASK(Actor)->unk_06 = (TASK(Actor)->unk_06 + 1) & 0x7;
        Script_Select((TASK(Actor)->unk_06 + 8) & BYTE_MASK);
    }
    Area_AddActor();
    Script_AnimStepLoop();
}
