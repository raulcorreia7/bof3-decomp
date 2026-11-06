#include "commu00_00.h"

MATCH void func_801F01F4(void) {
    u8 index;
    u8 start;
    u8 flag;

    flag  = 0;
    index = rand() & 0x3F;
    if (index >= 60) {
        index -= 0x3C;
    }
    start = index;
    for (;;) {
        if (g_FairyJobs[index].active != 0) {
            if (g_FairyJobs[index].type != FAIRY_JOB_HUNT || flag != 0) {
                g_FairyJobs[index].active = 0;
                D_80145E30[D_80145E44]    = index;
                D_80145E44                = D_80145E44 + 1;
                return;
            }
        }
        index = index + 1;
        if (index >= 60) {
            index = 0;
        }
        if (index != start) {
            continue;
        }
        flag = 1;
    }
}
