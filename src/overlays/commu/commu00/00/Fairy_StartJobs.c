#include "commu00_00.h"

MATCH void Fairy_StartJobs(void) {
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
        if (kind == FAIRY_JOB_IDLE) {
            func_801F0BF4(task);
            func_801F0718(record, task);
            task++;
        } else if (kind < FAIRY_JOB_HUNT) {
            func_801F08D8(record, task);
            task++;
        } else if (kind == FAIRY_JOB_CLEAR) {
            if (g_GameAreaId >= AREA_ID_FAIRY_VILLAGE_182) {
                label = 0xCD;
            } else {
                variant = RANDOM_MASK(0x7);
                if (variant >= 6) {
                    variant -= 5;
                }
                label = ((variant & BYTE_MASK) + 0xB6);
            }

            g_Actors[task].unk_7C = label;
            func_801F0718(record, task);
            task++;
        } else if (kind == FAIRY_JOB_BUILD) {
            scene = g_GameAreaId;
            if (scene == AREA_ID_FAIRY_VILLAGE_DOLPHIN || scene == AREA_ID_FAIRY_VILLAGE_178 ||
                scene == AREA_ID_FAIRY_VILLAGE_181 || scene == AREA_ID_FAIRY_VILLAGE_185) {
                label = 0xCE;
            } else {
                variant = RANDOM_MASK(0x7);
                if (variant >= 6) {
                    variant -= 5;
                }
                label = ((variant & BYTE_MASK) + 0xBC);
            }

            g_Actors[task].unk_7C = label;
            func_801F0718(record, task);
            task++;
        }
    }

    while (task < 20) {
        g_Actors[task].header.flags = 0;
        task++;
    }
}
