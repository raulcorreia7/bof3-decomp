#include "start_08.h"

/* nonmatching 76.74%: retail reads D_801ED620 signed at 0x47D4 (lb) and
 * unsigned later, but the union view keeps the cell's address in s0 and falls
 * to 55.81%. resume: a form that reads it once as signed without materialising
 * the address. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D53AC(void) {
    s32 pressed;
    u8  old;

    Menu_DrawClutStrip(D_80144953);
    g_MenuPanelTasks[21].active = 1;
    g_MenuPanelTasks[21].y      = (u16)g_MenuPanelTasks[12].y + 4;
    g_MenuPanelTasks[13].flags  = 1;
    g_MenuPanelTasks[21].x      = (u16)g_MenuPanelTasks[12].x + (s8)D_801ED620 * 0x30;
    g_MenuPanelTasks[12].unk_0B = 0xFF;
    g_MenuPanelTasks[11].unk_10 = D_801EC440[(s8)D_801ED620];
    pressed                     = INPUT_GetRepeatedButtons(g_InputPressed & (PADLright | PADLleft));
    old                         = D_801ED620;
    if (pressed & PADLleft) {
        D_801ED620 = old - 1;
        if ((s8)(old - 1) < 0) {
            D_801ED620 = 3;
        }
    }
    if (pressed & PADLright) {
        D_801ED620 += 1;
        if ((s8)D_801ED620 >= 4) {
            D_801ED620 = 0;
        }
    }
    if ((s8)old != (s8)D_801ED620) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if (g_InputPressed & D_80145AC2) {
        u8* step;

        SND_PlayCue(EMI_CUE_ID(1, 4));
        step                        = &D_80148651;
        g_MenuPanelTasks[21].active = 0;
        g_MenuPanelTasks[12].unk_0B = D_801ED620;
        *step += 1;
        return;
    }
    if (g_InputPressed & D_80145AC4) {
        u8* step;

        SND_PlayCue(EMI_CUE_ID(1, 2));
        SND_PlayCue(EMI_CUE_ID(1, 6));
        step                        = &D_80148651;
        g_MenuPanelTasks[11].state  = 1;
        g_MenuPanelTasks[12].state  = 1;
        g_MenuPanelTasks[13].state  = 1;
        D_801485DC                  = 0;
        g_MenuPanelTasks[21].active = 0;
        D_80148654                  = 0;
        *step += 5;
    }
}
#else
INCLUDE_ASM(func_801D53AC);
#endif
