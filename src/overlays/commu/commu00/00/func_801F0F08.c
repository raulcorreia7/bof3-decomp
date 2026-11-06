#include "commu00_00.h"

MATCH void func_801F0F08(u8 source_index, u8 task_index, u8 record_kind_index) {
    u32 elapsed;
    u32 bucket;

    g_Task->unk_06 = 1;

    elapsed = g_SaveData.battle_count - g_SaveData.fairy_jobs[source_index].progress_anchor;
    if (elapsed < 20) {
        bucket = 0;
    } else if (elapsed < 40) {
        bucket = 1;
    } else {
        bucket = 2;
    }

    g_Actors[task_index].unk_7C = D_801F2930[bucket][D_801F2928[record_kind_index]];
}
