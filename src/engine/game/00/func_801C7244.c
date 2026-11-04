#include "game_00.h"

/* Sums the heights of the live candidate cells and the queued entries, then centres and installs
 * the battle camera matrix.
 */
MATCH void func_801C7244(s32 mode) {
    EncounterEnemy* entry;
    SVECTOR*        rot;
    SVECTOR         angle;
    VECTOR          vec;
    MATRIX          matrix;
    s32             index;
    s32             count;
    s32             mode_index;
    s32             offset_x;
    s32             offset_y;
    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    STACK_PADS(u8, 0x10);

    mode_index = mode;
    count      = 0;
    entry      = D_801463DC;
    index      = 0;
    D_801CD954 = 0;
    do {
        if (entry->active != 0) {
            count += 1;
            D_801CD954 += Area_SampleHeight(entry->x, entry->y);
        }
        entry++;
        index += 1;
    } while ((u32)(index & BYTE_MASK) < 8U);

    index = 0;
loop_5:
    if ((u32)(u8)index < (u32)(Party_CountOrder(1) & BYTE_MASK)) {
        count += 1;
        D_801CD954 += Area_SampleHeight(*(s32*)(D_80143F2C + ((u8)index << 3)), *(s32*)(D_80143F30 + ((u8)index << 3)));
        index += 1;
        goto loop_5;
    }
    rot        = &g_AreaCameraAngle;
    D_801CD954 = (((s32)D_801CD954 / count) >> 5) << 5;
    RotMatrix(rot, &matrix);
    offset_x = D_801CD778[mode_index & BYTE_MASK].x;
    offset_y = D_801CD778[mode_index & BYTE_MASK].y;
    angle.vz = (s16)((s32)D_801CD954 >> 1);
    angle.vx = 0x4000 - ((s32)(D_80143F24 + (offset_x << 0x10)) >> 9);
    angle.vy = 0x4000 - ((s32)(D_80143F28 + (offset_y << 0x10)) >> 9);
    ApplyMatrix(&matrix, &angle, &vec);
    matrix.t[0] = vec.vx + g_AreaCameraOffsetX;
    matrix.t[1] = vec.vy + g_AreaCameraOffsetY;
    matrix.t[2] = vec.vz + g_AreaCameraOffsetZ + 0x1194;
    RotMatrix(rot, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}
