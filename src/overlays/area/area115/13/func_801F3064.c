#include "area115_13.h"

/* Each access reloads the work cell: the stores go through its pointer, which
 * the compiler must assume may alias the cell. */

MATCH void func_801F3064(void) {
    g_Task->flags_24 = 0x80;
    Area_FindSceneRecord(0x1C7);
    g_Task->unk_29            = 5;
    g_Task->unk_2A            = 0;
    g_Task->tint.bytes.unk_5D = 0;
    g_Task->tint.bytes.unk_5E = 0;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->mode              = 1;
}
