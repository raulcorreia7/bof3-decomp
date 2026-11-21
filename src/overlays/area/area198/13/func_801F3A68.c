#include "area198_13.h"

MATCH void func_801F3A68(void) {
    g_Task->pos.x.fixed = g_Actors[g_Task->option_flags].pos.x.fixed;
    g_Task->pos.y.fixed = g_Actors[g_Task->option_flags].pos.y.fixed;
    g_Task->pos.z.fixed = g_Actors[g_Task->option_flags].pos.z.fixed;
    Area_SelectSceneRecord(D_801F43D8[g_Task->unk_06].scene_record);
    g_Task->unk_48       = 1;
    g_Task->active_flags = 0;
    g_Task->mirror       = 0;
    Actor_SelectScript(D_801F43D8[g_Task->unk_06].script);
    g_Task->header.mode = 1;
    func_801F3B98();
}
