#include "area030_04.h"

/* Advances the area's entry state: while the record's state byte is
 * not 3, the held d-pad direction nudges the record's selection word, and the work area either
 * latches the pressed 0xA000 direction into its 0x0C word and the record's
 * speed word, or releases the record once the direction is no longer held and
 * its 0x34 word leaves the accepted range; it then runs the shared refresh. */
MATCH void func_801DA78C(void) {
    SpawnedActor* record;
    FishingState* work;
    s32           direction;
    s32           speed;

    record = g_SpawnedActors;
    if (g_SpawnedActors[0].header.mode == 3) {
        FISHING_STATE->mode_index_02 = 3;
        FISHING_STATE->sub_index_03  = 0;
    } else {
        if ((g_SpawnedActors[0].unk_14 == 0) && (g_InputPressed & PADRdown) && (g_SpawnedActors[0].selection > 0x110000)) {
            g_SpawnedActors[0].selection -= 0x4000;
        }
        work = FISHING_STATE;
        if (work->saved_index_0B == 0) {
            if (work->counter_07 == 0) {
                direction = g_InputHeld & (PADLright | PADLleft);
                if (direction != 0) {
                    work->pos_x_0C = direction;
                    if (direction == PADLleft) {
                        record->scene_step = -0x800;
                    } else {
                        record->scene_step = 0x800;
                    }
                    FISHING_STATE->counter_07 = 1;
                }
            } else if (!(g_InputHeld & work->pos_x_0C) || ((record->pos.x.fixed + 0xFFF9FFFF) > 0xEFFFEU)) {
                record->scene_step   = 0;
                work->saved_index_0B = 1;
            }
        }
    }
    Actor_StepAnimLoop();
}
