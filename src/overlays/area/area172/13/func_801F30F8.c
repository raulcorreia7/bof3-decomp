#include "area172_13.h"

MATCH void func_801F30F8(void) {
    s32 i;
    s32 value;

    func_801F36C0(&g_Task->pos.x, (s16)g_Task->screen_x, 7);
    if (*g_ScriptVars == 0xA) {
        Area_ClearWorkColumn();
        value = 0x800E48C0;
        PushMatrix();
        i = 0;
        do {
            Area_InitSpin(value);
            i += 1;
            value += 0x2C;
        } while ((i & BYTE_MASK) < 0x20U);
        PopMatrix();
        g_Task->unk_06            = 0;
        g_Task->tint.bytes.unk_5D = 8;
        g_Task->timer             = 120;
        g_Task->header.mode += 1;
    }
}
