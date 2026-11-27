#include "area146_13.h"

MATCH void func_801F2C68(void) {
    g_Game.current->status.field.flags.unsigned_value &= 0xFE;
    SELF(Actor)->draw_layer = g_AreaDrawMode;
}
