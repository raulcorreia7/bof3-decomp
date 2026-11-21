#include "game_00.h"

MATCH void func_8019B3A8(void) {
    Actor* work;

    Area_SelectSceneRecord(g_Task->param.scene_record_id);
    func_8019BF78();
    g_Task->draw_layer   = 6;
    g_Task->unk_48       = 1;
    g_Task->active_flags = 0;
    g_Task->mirror       = 0;
    ACTOR_CLEAR_TINT();
    work               = g_Task;
    work->option_flags = 0;
    work->vx           = 0;
    work->vy           = 0;
    work->vz           = 0;
    work->unk_18       = 0;
    work->unk_1C       = 0;
    work->gravity      = 0;
    g_Task->unk_0A     = 0;
    Script_Select(0);
    g_Task->header.mode++;
}
