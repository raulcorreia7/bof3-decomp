#include "area198_13.h"

MATCH void func_801F3A68(void) {
    SELF(Actor)->pos.x.fixed = g_Actors[SELF(Actor)->option_flags].pos.x.fixed;
    SELF(Actor)->pos.y.fixed = g_Actors[SELF(Actor)->option_flags].pos.y.fixed;
    SELF(Actor)->pos.z.fixed = g_Actors[SELF(Actor)->option_flags].pos.z.fixed;
    Area_SceneSelectRecord(D_801F43D8[SELF(Actor)->unk_06].scene_record);
    SELF(Actor)->unk_48       = 1;
    SELF(Actor)->active_flags = 0;
    SELF(Actor)->mirror       = 0;
    Script_Select(D_801F43D8[SELF(Actor)->unk_06].script);
    SELF(Actor)->header.mode = 1;
    func_801F3B98();
}
