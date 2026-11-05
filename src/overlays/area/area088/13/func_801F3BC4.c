#include "area088_13.h"

MATCH void func_801F3BC4(void) {
    g_Task->flags_24 = 0x80;
    Area_FindSceneRecord(0x157);
    g_Task->unk_29 = 5;
    g_Task->unk_2A = 0;
    ACTOR_CLEAR_TINT();
    g_Task->mode = 1;
}
