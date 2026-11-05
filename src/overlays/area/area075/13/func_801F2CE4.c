#include "area075_13.h"

MATCH void func_801F2CE4(void) {
    FIELD(u8, &D_801F58CE, g_SpadWork->unk_0B) = (u8)((s32)(((s32)g_SpadWork - (s32)g_ActorSlots) * 0x4F72C235) >> 2);
    g_SpadWork->unk_0A                         = 0x80;
    g_SpadWork->unk_0C                         = 0;
    g_SpadWork->unk_06                         = 0x1E;
    g_SpadWork->tint.signed_bytes.unk_5D       = -0x80;
    g_SpadWork->unk_01 += 1;
}
