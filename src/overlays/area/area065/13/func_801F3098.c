#include "area065_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F3098(void) {
    g_SpadWork->flags_24 = 0x80;
    Area_FindSceneRecord(0x53);
    g_SpadWork->unk_29 = 5;
    g_SpadWork->unk_2A = 0;
    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    g_SpadWork->unk_01 = 1;
}
