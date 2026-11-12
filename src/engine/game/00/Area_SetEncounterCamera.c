#include "game_00.h"

/* Sums the heights of the live candidate cells and the queued entries, then centres and installs
 * the battle camera matrix.
 */
/* func_801C7244 */
MATCH void Area_SetEncounterCamera(s32 mode) {
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
    FAKE_STACK_PADS(u8, 0x10);

    mode_index = mode;
    count      = 0;
    entry      = D_801463DC;
    index      = 0;
    D_801CD954 = 0;
    do {
        if (entry->active != 0) {
            count += 1;
            D_801CD954 += Area_SampleHeight(entry->pos.x, entry->pos.y);
        }
        entry++;
        index += 1;
    } while ((index & BYTE_MASK) < 8U);

    index = 0;
loop_5:
    if ((u8)index < (Party_CountOrder(PARTY_ORDER_BATTLE) & BYTE_MASK)) {
        count += 1;
        D_801CD954 += Area_SampleHeight(g_EncounterParty[(u8)index].x.fixed, g_EncounterParty[(u8)index].y.fixed);
        index += 1;
        goto loop_5;
    }
    rot        = &g_AreaCameraAngle;
    D_801CD954 = ((D_801CD954 / count) >> 5) << 5;
    RotMatrix(rot, &matrix);
    offset_x = D_801CD778[mode_index & BYTE_MASK].x;
    offset_y = D_801CD778[mode_index & BYTE_MASK].y;
    angle.vz = (D_801CD954 >> 1);
    angle.vx = 16384 - ((g_EncounterOriginX + (offset_x << 0x10)) >> 9);
    angle.vy = 16384 - ((g_EncounterOriginY + (offset_y << 0x10)) >> 9);
    ApplyMatrix(&matrix, &angle, &vec);
    matrix.t[0] = vec.vx + g_AreaCameraOffsetX;
    matrix.t[1] = vec.vy + g_AreaCameraOffsetY;
    matrix.t[2] = vec.vz + g_AreaCameraOffsetZ + 0x1194;
    RotMatrix(rot, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}
