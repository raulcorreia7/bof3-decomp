#include "engine/slus/slus.h"

/* advances the scratchpad work record's sort key from its grid
 * position, retires the record when the key leaves the ordering table, and
 * otherwise writes the packed key, projects its 16.16 position through the GTE
 * and publishes the resulting screen pair.
 */
/* nonmatching 68.24%: first mismatch +0x0020; assigning work after the early return gives retail's
 * single load and copy, but the copy lands in a2 (retail a3) and the col/row loads are emitted in the
 * other order; swapping the two statements is flat. resume: a shape that gives the work copy a3. */
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

    if (g_SpadWork->flags_24 & 0x80) {
        Area_AddActor();
        return;
    }
    work = g_SpadWork;

    col = g_SpadWork->y.part.integer - g_AreaTileOriginY;
    row = g_SpadWork->x.part.integer - g_AreaTileOriginX;
    if (g_SpadWork->x.part.fraction != 0) {
        col++;
    }
    key = row + col;

    zero  = (g_SpadWork->x.part.fraction == 0);
    table = &g_SpriteCellRotations[g_SpadWork->unk_2B * 3];
    if (g_SpadWork->y.part.fraction == 0) {
        table += 1 + zero;
    } else {
        table += zero;
    }
    offset = *table;
    if (g_SpadWork->y.part.fraction != 0) {
        key += (offset + 1);
    } else {
        key += offset;
    }
    work->unk_32 = key;

    if (g_SpadWork->unk_32 >= 0x37) {
        g_SpadWork->flags_00 |= ACTOR_FLAG_OFFSCREEN;
        return;
    }
    sort               = g_SpadWork->unk_32 << 8;
    g_SpadWork->unk_32 = sort;
    if (g_AreaDrawMode == 4) {
        if (D_8014933F != 0) {
            sort |= (g_SpadWork->x.fixed >> 15) & BYTE_MASK;
        } else {
            sort |= (g_SpadWork->y.fixed >> 15) & BYTE_MASK;
        }
    } else {
        sort |= (((u16)g_SpadWork->z.part.integer >> 5) & BYTE_MASK) ^ 0x80;
    }
    g_SpadWork->unk_32 = sort;
    Actor_ReadValue();

    vec.vx = (g_SpadWork->x.fixed >> 9) - 0x4000;
    vec.vy = (g_SpadWork->y.fixed >> 9) - 0x4000;
    vec.vz = -g_SpadWork->z.part.integer / 2;
    rot    = RotTransPers(&vec, &sxy, &p, &flag);

    FIELD(s32, g_SpadWork, 0x60) = rot;
    FIELD(u16, g_SpadWork, 0x2E) = (u16)sxy;
    FIELD(u16, g_SpadWork, 0x30) = (u16)(sxy >> 16);
    if (D_8014832D < 0x28) {
        D_8014828C[D_8014832D] = (s32)g_SpadWork;
        D_8014832D++;
        if (g_SpadWork->flags_00 & 8) {
            func_80161454((u32)g_SpadWork);
        }
    }
}
#else
INCLUDE_ASM(func_8014D290);
#endif
