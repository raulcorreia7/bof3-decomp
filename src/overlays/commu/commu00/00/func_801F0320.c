#include "commu00_00.h"

/* 60 rows of 9 bytes (0x21C bytes); only the leading byte is read here. */

MATCH void func_801F0320(void) {
    u8* sum_10;
    u8* sum_11;
    s32 i;
    u8* new_var;
    u8* new_var2;
    u8  kind;
    s32 kind_10;
    s32 kind_11;

    kind_10    = FAIRY_JOB_CLEAR;
    kind_11    = FAIRY_JOB_BUILD;
    sum_10     = &D_801455C5;
    sum_11     = sum_10 + 1;
    *sum_10    = 0;
    new_var    = sum_10;
    new_var2   = sum_11;
    D_801455C6 = 0;

    for (i = 0; i < 60; i++) {
        if (g_SaveData.fairy_jobs[i].active != 0) {
            kind = g_SaveData.fairy_jobs[i].type;
            if (kind == kind_10) {
                *new_var += D_801F2706[i][0];
            } else if (kind == kind_11) {
                *new_var2 += D_801F2706[i][0];
            }
        }
    }
}
