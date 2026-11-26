#include "commu00_00.h"

/* Shapes the bytes prove: the pair handed to Area_HeightSample is read through the
 * D_801468BC/D_801468C0 byte views of the slot's packed fields (a
 * g_Self-relative read emits a materialized base plus zero-displacement
 * loads instead); variant_state and the distance pair go through the
 * g_Actors array expression while mode, state, unk_34/36/38/3a/3e,
 * source_index and resource_id go through the g_Self scratch pointer; the
 * unk_3A store precedes unk_38 and the unk3E store precedes source_index. No
 * .rodata table is involved, so the jump-table alignment residual of
 * Fairy_SpawnWorker cannot apply here. */
/* Packed coordinate pair of each task slot, reached through its own byte view
 * (slot stride 0x98, pair at +0x34/+0x38). */
/* Per-task rows of three bytes; byte 2 is the mode selector and bytes 0-1 seed
 * the packed coordinate pair. */

MATCH void func_801F0718(u8 source_index, u8 task_index) {
    s16 distance;

    g_Self              = &g_Actors[task_index];
    SELF(Actor)->unk_06 = 1;

    if (D_801F2568[task_index][2] != 0) {
        SELF(Actor)->header.mode    = 0;
        g_Actors[task_index].unk_78 = 2;
        SELF(Actor)->header.step    = 1;
    } else {
        SELF(Actor)->header.mode    = 6;
        g_Actors[task_index].unk_78 = 0;
        ACTOR_CLEAR_STEP();
    }

    COORD_INT(SELF(Actor)->pos.x)  = D_801F2568[task_index][0];
    COORD_FRAC(SELF(Actor)->pos.x) = 0;
    COORD_INT(SELF(Actor)->pos.y)  = D_801F2568[task_index][1];
    COORD_FRAC(SELF(Actor)->pos.y) = 0;
    distance                       = Area_HeightSample(g_Actors[task_index & BYTE_MASK].pos.x.fixed, g_Actors[task_index & BYTE_MASK].pos.y.fixed);
    COORD_INT(SELF(Actor)->pos.z)  = distance;
    SELF(Actor)->unk_05            = source_index;
    Area_SceneSelectRecord(D_801F24FC[SELF(Actor)->unk_05 % 6]);
    Script_DispatchSelector(SELF(Actor)->direction);
}
