#include "area108_14.h"

MATCH void func_801F4B58(void) {
    Actor* flags_set;
    Actor* flags_clear;
    Actor* tint;

    g_CurrentActor->unk_93 = GFX_AllocPaletteFade(TASK_BYTES, 0U, 0U, 0U, 1);
    flags_set              = g_Task;
    flags_set->header.flags |= 0x20;
    flags_clear = g_Task;
    flags_clear->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->tint.bytes.flags       = 1;
    tint                           = g_Task;
    tint->tint.signed_bytes.unk_5F = -0x80;
    tint->tint.signed_bytes.unk_5E = -0x80;
    tint->tint.signed_bytes.unk_5D = -0x80;
    g_Task->unk_04                 = 1;
    g_CurrentActor->unk_7E         = (g_CurrentActor->unk_7E - 2);
}
