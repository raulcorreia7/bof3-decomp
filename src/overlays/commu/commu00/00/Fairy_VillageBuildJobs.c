#include "commu00_00.h"

MATCH void Fairy_VillageBuildJobs(void) {
    s32 record;
    s32 task;
    u8  kind;
    u8  variant;
    u16 label;
    u16 scene;
    u8* kinds;

    record = 7;
    kinds  = (u8*)D_801F24FC_Data.variant_counter + 7;
    while (record >= 0) {
        *kinds = 0;
        kinds--;
        record--;
    }

    record = 0;
    task   = 0;
    for (; record < 60; record++) {
        if (g_FairyJobs[record].active == 0) {
            continue;
        }

        kind = g_FairyJobs[record].type;
        if (kind == 0) {
            func_801F0BF4((u8)task);
            func_801F0718((u8)record, (u8)task);
            task++;
        } else if (kind < 9) {
            func_801F08D8((u8)record, (u8)task);
            task++;
        } else if (kind == 10) {
            if (g_GameAreaId >= 182) {
                label = 0xCD;
            } else {
                variant = RANDOM_MASK(0x7);
                if (variant >= 6) {
                    variant -= 5;
                }
                label = (u16)((variant & BYTE_MASK) + 0xB6);
            }

            D_80146904[task * ACTOR_SIZE / 2] = label;
            func_801F0718((u8)record, (u8)task);
            task++;
        } else if (kind == 11) {
            scene = g_GameAreaId;
            if (scene == 175 || scene == 178 || scene == 181 || scene == 185) {
                label = 0xCE;
            } else {
                variant = RANDOM_MASK(0x7);
                if (variant >= 6) {
                    variant -= 5;
                }
                label = (u16)((variant & BYTE_MASK) + 0xBC);
            }

            D_80146904[task * ACTOR_SIZE / 2] = label;
            func_801F0718((u8)record, (u8)task);
            task++;
        }
    }

    while (task < 20) {
        g_Actors[task].flags_00 = 0;
        task++;
    }
}
