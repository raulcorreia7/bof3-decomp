#include "commu00_00.h"

MATCH void func_801F1110(u8 task_index, u8 record_kind_index) {
    u32 variant;

    g_Task->unk_06 = 1;
    variant        = ((u8*)D_801F24FC_Data.variant_counter)[record_kind_index];

    if (variant == 0) {
        g_Actors[task_index].unk_7C = 0xC009;
    } else if (variant == 1) {
        if (SYS_TestFlag(g_SceneEventFlags, 0x92)) {
            g_Actors[task_index].unk_7C = 0xC00B;
        } else {
            g_Actors[task_index].unk_7C = 0xD4;
        }
    } else {
        g_Actors[task_index].unk_7C = 0xD5;
    }
}
