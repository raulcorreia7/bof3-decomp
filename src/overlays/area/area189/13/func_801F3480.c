#include "area189_13.h"

MATCH void func_801F3480(void) {
    Area_SceneSelectRecord(680);
    TASK(Actor)->active_flags = 0;
    Script_Select(0);
    TASK(Actor)->draw_layer = 6;
    TASK(Actor)->unk_48     = 0;
    TASK(Actor)->header.step++;
}
