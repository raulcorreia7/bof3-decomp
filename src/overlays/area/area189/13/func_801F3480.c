#include "area189_13.h"

MATCH void func_801F3480(void) {
    Area_SceneSelectRecord(680);
    SELF(Actor)->active_flags = 0;
    Script_Select(0);
    SELF(Actor)->draw_layer = 6;
    SELF(Actor)->unk_48     = 0;
    SELF(Actor)->header.step++;
}
