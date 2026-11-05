#include "commu00_00.h"

/* Variant rows: 8 record indices, 3 variants each, 3 bytes per variant. */

MATCH void func_801F08D8(u8 source_index, u8 task_index) {
    u8  variant_index;
    s32 record_index;
    u8  index;
    s16 distance;
    record_index                = g_FairyJobs[source_index].type - 1;
    index                       = (u8)record_index;
    g_SpadWork                  = &g_Actors[task_index];
    g_SpadWork->unk_05          = source_index;
    g_SpadWork->unk_01          = 6;
    g_Actors[task_index].unk_78 = 0;
    ACTOR_CLEAR_STATE();
    /* Each pair is written value half first, then the zero half the caller
     * reads back as one 32-bit coordinate word. */
    g_SpadWork->x.part.integer  = D_801F25A4[index][D_801F2928[index]][0];
    g_SpadWork->x.part.fraction = 0;
    variant_index               = index;
    g_SpadWork->y.part.integer  = D_801F25A4[index][D_801F2928[index]][1];
    g_SpadWork->y.part.fraction = 0;
    distance = Area_SampleHeight(*((u32*)(&g_SpadWork->x.part.fraction)), *((u32*)(&g_SpadWork->y.part.fraction)));
    g_SpadWork->z.part.integer = distance;
    g_SpadWork->direction_08   = D_801F25A4[variant_index][D_801F2928[variant_index]][2];
    g_SpadWork->unk_48         = 0;
    Area_FindSceneRecord(D_801F24FC[g_SpadWork->unk_05 % 6]);
    func_8015BAC4(g_SpadWork->direction_08);
    switch (g_FairyRooms[variant_index * 8]) {
        case 0:
            func_801F0BF4(task_index);
            break;

        case 4:
            func_801F0C6C(task_index, (u8)record_index);
            break;

        case 5:
            func_801F0D3C(task_index, (u8)record_index);
            break;

        case 6:
            func_801F0E1C(task_index, (u8)record_index);
            break;

        case 7:
            func_801F0EC8(task_index);
            break;

        case 8:
            func_801F0F08(source_index, task_index, (u8)record_index);
            break;

        case 9:
            func_801F0FBC(source_index, task_index, (u8)record_index);
            break;

        case 10:
            func_801F1064(task_index, (u8)record_index);
            break;

        case 11:
            func_801F1110(task_index, (u8)record_index);
            break;

        case 12:
            func_801F1204(task_index, (u8)record_index);
            break;

        case 13:
            func_801F1254(task_index);
            break;
    }

    D_801F2928[(u8)record_index] += 1;
}
