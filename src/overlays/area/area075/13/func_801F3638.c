#include "area075_13.h"

MATCH void func_801F3638(void) {
    SND_QueueSelectionFx(0x200);
    g_ScriptState->cursor -= 2;
    TASK_BYTES[0x4] = 1;
}
