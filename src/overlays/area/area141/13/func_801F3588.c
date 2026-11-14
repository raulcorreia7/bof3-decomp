#include "area141_13.h"

MATCH void func_801F3588(void) {
    Actor* actor;

    g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    actor                       = g_Task;
    actor->tint.bytes.rgb.blue  = 0;
    actor->tint.bytes.rgb.green = 0;
    actor->tint.bytes.rgb.red   = 0;
    actor->tint.bytes.flags     = 0;
    GFX_FreePaletteFadeTarget(g_Task);
}
