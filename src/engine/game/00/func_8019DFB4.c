#include "game_00.h"

MATCH void func_8019DFB4(void) {
    s32    jitter;
    s32    step_x;
    s32    step_y;
    s32    value;
    s32    cue_id;
    s32    index;
    u16    world_id;
    u8     active;
    u16    counter;
    Actor* work_a;
    Actor* work_b;
    Actor* work_c;
    Actor* work_d;
    Actor* work_e;
    Actor* work_f;
    Actor* work_g;

    world_id = g_GameAreaId;
    index    = 8;
loop_1: /* scan the world-id table down from index 8 */
    if (s_AreaSeIds[index] != world_id) {
        index -= 1;
        if (index >= 0) {
            goto loop_1; /* keep scanning while the id does not match */
        }
    }
    cue_id = 0x212;
    if (index < 0) {
        cue_id = 0x1B;
    }
    if (Area_SceneSelectRecord(cue_id) & BYTE_MASK) {
        Actor_Clear();
        return;
    }
    jitter                    = rand();
    work_a                    = SELF(Actor);
    counter                   = COORD_INT(work_a->pos.z);
    work_a->active_flags      = 0;
    work_b                    = SELF(Actor);
    COORD_FRAC(work_a->pos.z) = 0;
    COORD_INT(work_a->pos.z)  = (u16)(counter + (jitter & 0x7F));
    work_b->mirror            = 0;
    work_c                    = SELF(Actor);
    work_c->unk_2B            = (u8)(work_c->unk_2B + 1);
    SELF(Actor)->unk_48       = 0;
    step_x                    = RANDOM_MASK(0x7FFF);
    work_d                    = SELF(Actor);
    work_d->pos.x.fixed += step_x;
    step_y     = rand();
    work_e     = SELF(Actor);
    work_e->vz = 0xFFF80000;
    work_e->pos.y.fixed += (step_y & 0x7FFF);
    SELF(Actor)->vx = (s32)RANDOM_MASK(0xFFF);
    value           = RANDOM_MASK(0xFFF);
    work_f          = SELF(Actor);
    work_f->vy      = value;
    if (work_f->vx >= 2049) {
        active = 1;
    } else if (value >= 0x801) {
        work_f->mirror = 1;
        active         = 1;
    } else {
        active = 0;
    }
    Script_Select(active);
    ACTOR_CLEAR_TINT();
    SELF(Actor)->timer  = 16;
    SELF(Actor)->unk_0A = 8;
    work_g              = SELF(Actor);
    work_g->header.step = (u8)(work_g->header.step + 1);
}
