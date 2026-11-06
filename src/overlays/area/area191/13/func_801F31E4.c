#include "area191_13.h"

MATCH void func_801F31E4(void) {
    g_Task->unk_48            = 2;
    g_Task->scale_x           = 0x10000;
    g_Task->scale_y           = 0x10000;
    g_Task->unk_0A            = 0xFF;
    g_Task->state_70.word     = 1;
    g_Task->tint.bytes.unk_5D = 0x50;
    g_Task->tint.bytes.unk_5E = 0x3C;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->unk_04            = 1;
    g_ScriptState->cursor -= 2;
}
