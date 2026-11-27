#include "commu00_00.h"

MATCH void func_801F1064(u8 task_index, u8 record_type_index) {
    if (D_801F2928[record_type_index] != 0) {
        SELF(Actor)->unk_06                     = 1;
        g_Actors[task_index & BYTE_MASK].unk_7C = (D_801F2928[record_type_index] + 0xCF);
    } else {
        SELF(Actor)->unk_06                     = 5;
        SELF(Actor)->unk_18                     = 6;
        SELF(Actor)->unk_1C                     = 0;
        g_Actors[task_index & BYTE_MASK].unk_7C = 0xCB;
    }
}
