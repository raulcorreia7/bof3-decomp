#include "area191_13.h"

MATCH void func_801F31E4(void) {
    SELF(Actor)->unk_48           = 2;
    SELF(Actor)->scale.x          = 65536;
    SELF(Actor)->scale.y          = 65536;
    SELF(Actor)->unk_0A           = 0xFF;
    SELF(Actor)->voice_flags.raw  = 1;
    SELF(Actor)->tint.bytes.rgb.r = 0x50;
    SELF(Actor)->tint.bytes.rgb.g = 0x3C;
    SELF(Actor)->tint.bytes.rgb.b = 0;
    SELF(Actor)->unk_04           = 1;
    g_ScriptState->cursor -= 2;
}
