#include "engine/slus/slus.h"

/* advances the scratchpad work record's sort key from its grid
 * position, retires the record when the key leaves the ordering table, and
 * otherwise writes the packed key, projects its 16.16 position through the GTE
 * and publishes the resulting screen pair.
 */
/* Pinned or opaque work pointers change the prologue; a barrier and coordinate loads through work differ at +0x20. */
#ifdef NON_MATCHING
NON_MATCHING void func_8014D290(void) {
    SVECTOR   vec;
    s32       sxy;
    s32       p;
    s32       flag;
    s32       zero;
    s32       row;
    s32       col;
    s32       key;
    s32       offset;
    const s8* table;
    s32       sort;
    s32       rot;
    Actor*    work;

    if (g_Task->active_flags & 0x80) {
        Area_AddActor();
        return;
    }
    work = g_Task;

    col = COORD_INT(g_Task->pos.y) - g_AreaTileOriginY;
    row = COORD_INT(g_Task->pos.x) - g_AreaTileOriginX;
    if (COORD_FRAC(g_Task->pos.x) != 0) {
        col++;
    }
    key = row + col;

    zero  = (COORD_FRAC(g_Task->pos.x) == 0);
    table = &g_SpriteCellRotations[g_Task->unk_2B * 3];
    if (COORD_FRAC(g_Task->pos.y) == 0) {
        table += 1 + zero;
    } else {
        table += zero;
    }
    offset = *table;
    if (COORD_FRAC(g_Task->pos.y) != 0) {
        key += (offset + 1);
    } else {
        key += offset;
    }
    work->unk_32 = key;

    if (g_Task->unk_32 >= 0x37) {
        g_Task->header.flags |= ACTOR_FLAG_OFFSCREEN;
        return;
    }
    sort           = g_Task->unk_32 << 8;
    g_Task->unk_32 = sort;
    if (g_AreaDrawMode == 4) {
        if (D_8014933F != 0) {
            sort |= (g_Task->pos.x.fixed >> 15) & BYTE_MASK;
        } else {
            sort |= (g_Task->pos.y.fixed >> 15) & BYTE_MASK;
        }
    } else {
        sort |= (((u16)COORD_INT(g_Task->pos.z) >> 5) & BYTE_MASK) ^ 0x80;
    }
    g_Task->unk_32 = sort;
    Actor_ReadValue();

    vec.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    vec.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    vec.vz = -COORD_INT(g_Task->pos.z) / 2;
    rot    = RotTransPers(&vec, &sxy, &p, &flag);

    FIELD(s32, g_Task, 0x60) = rot;
    FIELD(u16, g_Task, 0x2E) = (u16)sxy;
    FIELD(u16, g_Task, 0x30) = (u16)(sxy >> 16);
    if (D_8014832D < 0x28) {
        D_8014828C[D_8014832D] = (s32)g_Task;
        D_8014832D++;
        if (g_Task->header.flags & ACTOR_FLAG_SELECTION_EFFECT) {
            func_80161454((u32)g_Task);
        }
    }
}
#else
INCLUDE_ASM(func_8014D290);
#endif
