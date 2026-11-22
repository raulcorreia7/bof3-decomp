#include "engine/slus/slus.h"

/* advances the scratchpad work record's sort key from its grid
 * position, retires the record when the key leaves the ordering table, and
 * otherwise writes the packed key, projects its 16.16 position through the GTE
 * and publishes the resulting screen pair.
 */
/* FAKE: the key readers load unk_32 unsigned; the s16 member takes a (u16) cast at the two reads. */
/* func_8014D290 */
#ifdef NON_MATCHING
NON_MATCHING void Area_AddGridActor(void) {
    SVECTOR   vec;
    DVECTOR   sxy;
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

    if (TASK(Actor)->active_flags & 0x80) {
        Area_AddActor();
        return;
    }
    work = TASK(Actor);

    row = COORD_INT(work->pos.x) - g_AreaTileOriginX;
    col = COORD_INT(work->pos.y) - g_AreaTileOriginY;
    if (COORD_FRAC(work->pos.x) != 0) {
        col++;
    }
    key = row + col;

    zero  = (COORD_FRAC(TASK(Actor)->pos.x) == 0);
    table = &g_SpriteCellRotations[TASK(Actor)->unk_2B * 3];
    if (COORD_FRAC(TASK(Actor)->pos.y) == 0) {
        table += 1 + zero;
    } else {
        table += zero;
    }
    offset = *table;
    if (COORD_FRAC(TASK(Actor)->pos.y) != 0) {
        key += offset + 1;
    } else {
        key += offset;
    }
    work->unk_32 = key;

    if ((u16)TASK(Actor)->unk_32 >= 0x37) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_OFFSCREEN;
        return;
    }
    sort                = (u16)TASK(Actor)->unk_32 << 8;
    TASK(Actor)->unk_32 = sort;
    if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
        if (D_8014933F != 0) {
            sort |= (TASK(Actor)->pos.x.fixed >> 15) & BYTE_MASK;
        } else {
            sort |= (TASK(Actor)->pos.y.fixed >> 15) & BYTE_MASK;
        }
    } else {
        sort |= (((u16)COORD_INT(TASK(Actor)->pos.z) >> 5) & BYTE_MASK) ^ 0x80;
    }
    TASK(Actor)->unk_32 = sort;
    Actor_ReadValue();

    setVector(&vec, (TASK(Actor)->pos.x.fixed >> 9) - 0x4000, (TASK(Actor)->pos.y.fixed >> 9) - 0x4000, -COORD_INT(TASK(Actor)->pos.z) / 2);
    rot = RotTransPers(&vec, (s32*)&sxy, &p, &flag);

    FIELD(s32, g_Task, 0x60) = rot;
    TASK(Actor)->screen_x    = (u16)sxy.vx;
    TASK(Actor)->screen_y    = (u16)sxy.vy;
    if ((u8)g_AreaGridActorCount < 0x28) {
        g_AreaGridActors[(u8)g_AreaGridActorCount] = (s32)g_Task;
        g_AreaGridActorCount++;
        if (TASK(Actor)->header.flags & ACTOR_FLAG_SELECTION_EFFECT) {
            func_80161454((u32)g_Task);
        }
    }
}
#else
INCLUDE_ASM(Area_AddGridActor);
#endif
