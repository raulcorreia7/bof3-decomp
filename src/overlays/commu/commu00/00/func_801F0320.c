#include "commu00_00.h"

/* 60 rows of 9 bytes (0x21C bytes); only the leading byte is read here. */

MATCH void func_801F0320(void) {
    u8* sum_10;
    u8* sum_11;
    s32 i;
    u8* new_var;
    u8* new_var2;
    u8  type;
    s32 type_10;
    s32 type_11;

    type_10    = FAIRY_JOB_CLEAR;
    type_11    = FAIRY_JOB_BUILD;
    sum_10     = &D_801455C5;
    sum_11     = sum_10 + 1;
    *sum_10    = 0;
    new_var    = sum_10;
    new_var2   = sum_11;
    D_801455C6 = 0;

    for (i = 0; i < FAIRY_VILLAGE_COUNT; i++) {
        if (g_FairyJobs[i].active != 0) {
            type = g_FairyJobs[i].type;
            if (type == type_10) {
                *new_var += D_801F2706[i][0];
            } else if (type == type_11) {
                *new_var2 += D_801F2706[i][0];
            }
        }
    }
}
