#include "area191_13.h"

MATCH void func_801F31E4(void) {
    TASK(Actor)->unk_48           = 2;
    TASK(Actor)->scale.x          = 65536;
    TASK(Actor)->scale.y          = 65536;
    TASK(Actor)->unk_0A           = 0xFF;
    TASK(Actor)->voice_flags.raw  = 1;
    TASK(Actor)->tint.bytes.rgb.r = 0x50;
    TASK(Actor)->tint.bytes.rgb.g = 0x3C;
    TASK(Actor)->tint.bytes.rgb.b = 0;
    TASK(Actor)->unk_04           = 1;
    g_ScriptState->cursor -= 2;
}
