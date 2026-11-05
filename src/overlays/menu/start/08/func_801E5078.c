#include "start_08.h"

/* start_08.h declares the card-port cell u8; retail stores it with `sw`, and
 * the etc/start/09 view owns the same cell as an s32. */

MATCH void func_801E5078(void) {
    s32 port;
    s32 prev;
    s32 curr;

    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, (s32)D_80144952);
    UI_DrawText(28, 21, 0, 0xFFU, Resource_GetText(0xA8));
    g_SaveCardPort = 0;
    CardAccessFile(0, 0, 0, 0, 0);
    port           = 1;
    prev           = g_SaveCardStatus;
    g_SaveCardPort = port;
    CardAccessFile(0, 0, 0, 0, 0);
    curr = g_SaveCardStatus;
    if ((prev == 0) || (prev == 2)) {
        if ((curr == 0) || (curr == 2)) {
            D_801ED7F8     = 1;
            g_SaveCardPort = 0;
            D_801ED7F4     = 0;
            D_801ED870     = 3;
        } else {
            g_SaveCardPort = 0;
            D_801ED7F4     = 0;
            D_801ED7F8     = 0;
            D_801ED870     = 1;
        }
    } else if ((curr == 0) || (curr == 2)) {
        D_801ED7F4     = 1;
        D_801ED7F8     = 1;
        g_SaveCardPort = port;
        D_801ED870     = 2;
    } else {
        SND_PlayCue(EMI_CUE_ID(1, 7));
        g_SaveCardStatus = 8;
        g_MenuStartStep  = 0xD;
        D_801ED870       = 0;
        return;
    }
    g_MenuStartTimer = 4;
    g_MenuStartStep += 1;
}
