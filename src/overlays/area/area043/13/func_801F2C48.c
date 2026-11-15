#include "area043_13.h"

MATCH void func_801F2C48(void) {
    Actor* tint;

    g_CurrentActor->unk_93 = GFX_AllocPaletteFade(g_Task, 0, 0, 0, 1);
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    /* The ActorTint word: its flags byte and three signed fade steps; unk_48, unk_04 and
     * unk_7E have no names. */
    tint                                = g_Task;
    tint->tint.signed_bytes.delta.blue  = -0x40;
    tint->tint.signed_bytes.delta.green = -0x40;
    tint->tint.signed_bytes.delta.red   = -0x40;
    g_Task->tint.bytes.flags            = 1;
    g_Task->unk_48                      = 2;
    g_Task->unk_04                      = 1;
    g_CurrentActor->unk_7E              = g_CurrentActor->unk_7E - 2;
}
