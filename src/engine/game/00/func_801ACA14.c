#include "game_00.h"

MATCH void func_801ACA14(void) {
    Actor* flags_set;
    Actor* tint;
    Actor* work;

    g_CurrentActor->unk_93 = GFX_AllocPaletteFade(TASK_BYTES, 0U, 0U, 0U, 1);
    flags_set              = g_Task;
    *(u8*)flags_set |= 0x20;
    tint                            = g_Task;
    tint->tint.signed_bytes.unk_5F  = -0x40;
    tint->tint.signed_bytes.unk_5E  = -0x40;
    tint->tint.signed_bytes.unk_5D  = -0x40;
    g_Task->tint.signed_bytes.flags = 1;
    work                            = g_Task;
    g_CurrentActor->unk_7E          = (g_CurrentActor->unk_7E - 1);
    work->unk_04                    = 1;
}
