#include "boss008_16.h"

MATCH void func_800C1B48(void) {
    u32 value;
    u32 value2;
    u8  value3;

    func_800C236C(g_SpadWork->word_08.byte.unk_09);
    value3 = g_SpadWork->word_08.byte.unk_09;
    if (value3 == 0) {
        g_SpadWork->unk_48 = 0;
        Area_FindSceneRecord(0x83);
        Actor_SelectScript(0U);
        func_801E54EC();
        g_SpadWork->flags_00 &= 0xBF;
        g_SpadWork->step_01 = 6;
        g_SpadWork->unk_02  = 4;
        g_SpadWork->unk_03 += 1;
        g_SpadWork->unk_04 = 0;
        return;
    }
    g_SpadWork->word_08.byte.unk_09 = value3 - 4;
    value                           = g_SpadWork->unk_40;
    if ((s32)value > 0) {
        g_SpadWork->unk_40 = value - 0x2000;
    } else {
        g_SpadWork->unk_40 = 0;
    }
    value2 = g_SpadWork->unk_44;
    if ((s32)value2 > 0) {
        g_SpadWork->unk_44 = value2 - 0x2000;
        return;
    }
    g_SpadWork->unk_44 = 0;
}
