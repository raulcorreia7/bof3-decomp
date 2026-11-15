#include "area170_13.h"

MATCH void func_801F2D80(void) {
    Actor* work;
    u8     old;

    old = *(u8*)g_Task->unk_4C;
    if ((g_InputPressed & PADLleft) != 0) {
        *(u8*)g_Task->unk_4C = old + 1;
        if (*(u8*)g_Task->unk_4C >= 9) {
            *(u8*)g_Task->unk_4C = 0;
        }
    }
    if ((g_InputPressed & PADLright) != 0) {
        *(u8*)g_Task->unk_4C -= 1;
        if ((s8) * (u8*)g_Task->unk_4C < 0) {
            *(u8*)g_Task->unk_4C = 8;
        }
    }
    if (old != *(u8*)g_Task->unk_4C) {
        SND_PlayCue(0x204);
    }

    if ((g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        SND_PlayCue(0x205);
        work                     = g_Task;
        D_801F5990[work->unk_06] = *(u8*)work->unk_4C;
        D_801448EE               = 1;
        g_Task->header.mode += 1;
    } else if ((g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_PlayCue(0x206);
        D_801448EE = 0xFF;
        g_Task->header.mode += 2;
    }

    func_801F31DC((s16)g_Task->screen_x, (s16)g_Task->screen_y);
}
