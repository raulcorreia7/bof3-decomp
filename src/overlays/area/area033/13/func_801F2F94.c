#include "area033_13.h"

/* Each access reloads the work cell through g_SpadWork. */
MATCH void func_801F2F94(void) {
    g_SpadWork->flags_24 = 0x80;
    Area_FindSceneRecord(0xF);
    g_SpadWork->unk_29            = 5;
    g_SpadWork->unk_2A            = 0;
    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    ((u8*)g_SpadWork)[1]          = 1;
}
