#include "area170_13.h"

MATCH void func_801F2D80(void) {
    Actor* work;
    u8     old;

    old = MEM_PTR(u8, g_Task->unk_4C)[0];
    if ((g_InputPressed & PADLleft) != 0) {
        MEM_PTR(u8, g_Task->unk_4C)[0] = old + 1;
        if (MEM_PTR(u8, g_Task->unk_4C)[0] >= 9) {
            MEM_PTR(u8, g_Task->unk_4C)[0] = 0;
        }
    }
    if ((g_InputPressed & PADLright) != 0) {
        MEM_PTR(u8, g_Task->unk_4C)[0] -= 1;
        if (MEM_PTR(s8, g_Task->unk_4C)[0] < 0) {
            MEM_PTR(u8, g_Task->unk_4C)[0] = 8;
        }
    }
    if (old != MEM_PTR(u8, g_Task->unk_4C)[0]) {
        SND_PlayCue(0x204);
    }

    if ((g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        SND_PlayCue(0x205);
        work                     = g_Task;
        D_801F5990[work->unk_06] = MEM_PTR(u8, work->unk_4C)[0];
        D_801448EE               = 1;
        g_Task->header.mode += 1;
    } else if ((g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_PlayCue(0x206);
        D_801448EE = 0xFF;
        g_Task->header.mode += 2;
    }

    func_801F31DC(LOH(g_Task->screen_x), LOH(g_Task->screen_y));
}
