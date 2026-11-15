/* Every row re-reads the scratchpad cell. */
#define TASK_VOLATILE
#include "area134_13.h"

/* Runs the four-stage size and colour ramp of every stamped work row, then
 * integrates and draws it. */
MATCH s32 func_801F49A0(void) {
    AreaQuadSprite* record;
    u8              scratch[0x30];
    u8              i;
    u8              handled;
    u8              count;
    s32             y;

    Area_SetCameraMatrix(scratch);
    handled = 0;
    record  = MEM_PTR(AreaQuadSprite, AREA_WORK);
    i       = 0;
    do {
        if (record->unk_00[0] == g_Task->unk_06) {
            handled = 1;
            switch (record->unk_00[1]) {
                case 0:
                    record->half_size += 4;
                    count = record->unk_00[2] += 1;
                    if (count == 8) {
                        record->unk_00[1] += 1;
                    }
                    break;
                case 1:
                    record->flags_03 -= 8;
                    count = record->unk_00[2] += 1;
                    if (count == 0x10) {
                        record->unk_00[1] += 1;
                    }
                    break;
                case 2:
                    record->half_size -= 0x10;
                    count = record->unk_00[2] += 1;
                    if (count == 0x18) {
                        record->unk_00[1] += 1;
                    }
                    break;
                case 3:
                    record->half_size -= 0x10;
                    count = record->unk_00[2] += 1;
                    if (count == 0x20) {
                        record->unk_00[0] = 0;
                    }
                    break;
            }
            record->origin.x += record->unk_18;
            record->half_size += 8;
            y                = record->origin.y + record->unk_1C;
            record->origin.y = y;
            record->unk_10   = Area_SampleHeight(record->origin.x, y) << 16;
            func_801F46EC(record);
        }
        record++;
        i++;
    } while (i < 0x20);

    return handled;
}
