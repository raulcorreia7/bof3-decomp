#include "commu00_00.h"

/* Shapes the bytes prove: the pair handed to Area_SampleHeight is read through the
 * D_801468BC/D_801468C0 byte views of the slot's packed fields (a
 * g_Task-relative read emits a materialized base plus zero-displacement
 * loads instead); variant_state and the distance pair go through the
 * g_Actors array expression while mode, state, unk_34/36/38/3a/3e,
 * source_index and resource_id go through the g_Task scratch pointer; the
 * unk_3A store precedes unk_38 and the unk_3E store precedes source_index. No
 * .rodata table is involved, so the jump-table alignment residual of
 * Fairy_SpawnWorker cannot apply here. */
/* Packed coordinate pair of each task slot, reached through its own byte view
 * (slot stride 0x98, pair at +0x34/+0x38). */
/* Per-task rows of three bytes; byte 2 is the mode selector and bytes 0-1 seed
 * the packed coordinate pair. */

MATCH void func_801F0718(u8 source_index, u8 task_index) {
    s16 distance;

    g_Task         = &g_Actors[task_index];
    g_Task->unk_06 = 1;

    if (D_801F2568[task_index][2] != 0) {
        g_Task->header.mode         = 0;
        g_Actors[task_index].unk_78 = 2;
        g_Task->header.step         = 1;
    } else {
        g_Task->header.mode         = 6;
        g_Actors[task_index].unk_78 = 0;
        ACTOR_CLEAR_STEP();
    }

    COORD_INT(g_Task->pos.x)  = D_801F2568[task_index][0];
    COORD_FRAC(g_Task->pos.x) = 0;
    COORD_INT(g_Task->pos.y)  = D_801F2568[task_index][1];
    COORD_FRAC(g_Task->pos.y) = 0;
    distance                  = Area_SampleHeight(*((u32*)&D_801468BC[(task_index & BYTE_MASK) * ACTOR_SIZE]), *((u32*)&D_801468C0[(task_index & BYTE_MASK) * ACTOR_SIZE]));
    COORD_INT(g_Task->pos.z)  = distance;
    g_Task->unk_05            = source_index;
    Area_SelectSceneRecord(D_801F24FC[g_Task->unk_05 % 6]);
    func_8015BAC4(g_Task->direction_08);
}
