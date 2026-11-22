#include "game_00.h"

MATCH void func_8019B3A8(void) {
    Actor* work;

    Area_SceneSelectRecord(TASK(Actor)->param.scene_record_id);
    func_8019BF78();
    TASK(Actor)->draw_layer   = 6;
    TASK(Actor)->unk_48       = 1;
    TASK(Actor)->active_flags = 0;
    TASK(Actor)->mirror       = 0;
    ACTOR_CLEAR_TINT();
    work               = TASK(Actor);
    work->option_flags = 0;
    setVector(work, 0, 0, 0);
    work->unk_18        = 0;
    work->unk_1C        = 0;
    work->gravity       = 0;
    TASK(Actor)->unk_0A = 0;
    Script_Select(0);
    TASK(Actor)->header.mode++;
}
