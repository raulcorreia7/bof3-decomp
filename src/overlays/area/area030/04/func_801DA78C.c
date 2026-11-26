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
        SELF(FishingState)->mode_index = 3;
        SELF(FishingState)->sub_index  = 0;
    } else {
        if ((g_SpawnedActors[0].unk_14 == 0) && (g_PadStates[0].pressed & PADRdown) && (g_SpawnedActors[0].selection > 0x110000)) {
            g_SpawnedActors[0].selection -= 0x4000;
        }
        work = SELF(FishingState);
        if (work->saved_index == 0) {
            if (work->counter_07 == 0) {
                direction = g_PadStates[0].held & (PADLright | PADLleft);
                if (direction != 0) {
                    work->pos_x = direction;
                    if (direction == PADLleft) {
                        record->vx = -0x800;
                    } else {
                        record->vx = 0x800;
                    }
                    SELF(FishingState)->counter_07 = 1;
                }
            } else if (!(g_PadStates[0].held & work->pos_x) || ((record->pos.x.fixed + 0xFFF9FFFF) > 0xEFFFEU)) {
                record->vx        = 0;
                work->saved_index = 1;
            }
        }
    }
    Script_AnimStepLoop();
}
