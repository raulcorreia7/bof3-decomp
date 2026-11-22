#include "area198_13.h"

MATCH void func_801F3A68(void) {
    TASK(Actor)->pos.x.fixed = g_Actors[TASK(Actor)->option_flags].pos.x.fixed;
    TASK(Actor)->pos.y.fixed = g_Actors[TASK(Actor)->option_flags].pos.y.fixed;
    TASK(Actor)->pos.z.fixed = g_Actors[TASK(Actor)->option_flags].pos.z.fixed;
    Area_SceneSelectRecord(D_801F43D8[TASK(Actor)->unk_06].scene_record);
    TASK(Actor)->unk_48       = 1;
    TASK(Actor)->active_flags = 0;
    TASK(Actor)->mirror       = 0;
    Script_Select(D_801F43D8[TASK(Actor)->unk_06].script);
    TASK(Actor)->header.mode = 1;
    func_801F3B98();
}
