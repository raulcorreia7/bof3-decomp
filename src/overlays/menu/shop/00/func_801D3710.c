#include "shop_00.h"

/* File-local declarations: shop panel configuration bytes and halfwords. */

MATCH void func_801D3710(void) {
    u8* panel;
    s32 offset;

    panel    = (u8*)g_UIPanelTasks;
    panel[1] = 7;
    panel[2] = 0;
    panel[3] = 2;
    panel[0] = 1;
    panel += 0x24;
    D_80148334           = 0x14;
    /* FAKE: retail reads D_80148336 as s16. */
    (*(s16*)&D_80148336) = -0x14;
    D_80148340           = 0;
    panel[1]             = 7;
    panel[2]             = 1;
    panel[3]             = 2;
    panel[0]             = 1;
    panel += 0x24;
    D_80148358     = 0xC6;
    D_8014835A     = -0x14;
    panel[1]       = 7;
    panel[2]       = 2;
    panel[3]       = 2;
    panel[0]       = 1;
    offset         = 0x24;
    panel          = panel + 0x2AC;
    D_8014837C     = 0x66;
    D_8014837E     = -0x14;
    D_80148382     = 3;
    D_80148383     = 0xFF;
    D_80148625     = 7;
    D_80148626     = 3;
    panel[0]       = 0;
    D_80148601     = 7;
    D_80148602     = 4;
    panel[-offset] = 0;
    D_8014860A     = 0;
    D_8014860B     = 1;
}
