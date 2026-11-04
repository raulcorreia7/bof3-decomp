#include "area172_13.h"

MATCH void func_801F30F8(void) {
    s32 var_s0;
    s32 var_s1;

    func_801F36C0(&g_SpadWork->x, g_SpadWork->unk_2E, 7);
    if (*g_ScriptVars == 0xA) {
        Area_ClearWorkColumn();
        var_s1 = 0x800E48C0;
        PushMatrix();
        var_s0 = 0;
        do {
            Area_InitSpin(var_s1);
            var_s0 += 1;
            var_s1 += 0x2C;
        } while ((u32)(var_s0 & 0xFF) < 0x20U);
        PopMatrix();
        g_SpadWork->unk_06            = 0;
        g_SpadWork->tint.bytes.unk_5D = 8;
        g_SpadWork->unk_09            = 0x78;
        g_SpadWork->unk_01 += 1;
    }
}
