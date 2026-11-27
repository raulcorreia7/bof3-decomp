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
    SVECTOR vec;
    DVECTOR sxy;
    s32     p;
    s32     flag;
    s32     zero;

    s32       col;
    s32       key;
    const s8* table;
    s32       sort;
    s32       rot;
    Actor*    work;
    const s8* ptr;
    Actor*    task;
    s32       sum;

    if (SP_REF(Actor*, 0x44)->active_flags & 0x80) {
        Area_AddActor();
        return;
    }
    work = SP_REF(Actor*, 0x44);
    key  = COORD_INT(work->pos.x) - g_AreaTileOriginX;
    col  = COORD_INT(work->pos.y) - g_AreaTileOriginY;
    if (COORD_FRAC(work->pos.x) != 0) {
        col++;
    }
    key += col;

    zero  = (COORD_FRAC(SELF(Actor)->pos.x) == 0);
    table = &g_SpriteCellRotations[SELF(Actor)->unk_2B * 3];
    if (COORD_FRAC(SELF(Actor)->pos.y) == 0) {
        ptr = table + 1 + zero;
    } else {
        ptr = table + zero;
    }
    if (COORD_FRAC(SELF(Actor)->pos.y) != 0) {
        sum = key + (*ptr + 1);
    } else {
        sum = key + *ptr;
    }
    work->unk_32 = sum;
    task         = SELF(Actor);
    if ((u16)task->unk_32 >= 0x37) {
        task->header.flags |= ACTOR_FLAG_OFFSCREEN;
        return;
    }
    sort         = (u16)task->unk_32 << 8;
    task->unk_32 = sort;
    if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
        if (D_8014933F != 0) {
            sort |= (task->pos.x.fixed >> 15) & BYTE_MASK;
        } else {
            sort |= (task->pos.y.fixed >> 15) & BYTE_MASK;
        }
    } else {
        sort |= (((u16)COORD_INT(task->pos.z) >> 5) & BYTE_MASK) ^ 0x80;
    }
    task->unk_32 = sort;
    Actor_ReadValue();

    setVector(&vec, (SELF(Actor)->pos.x.fixed >> 9) - 0x4000, (SELF(Actor)->pos.y.fixed >> 9) - 0x4000, -COORD_INT(SELF(Actor)->pos.z) / 2);
    rot = RotTransPers(&vec, (s32*)&sxy, &p, &flag);

    SELF(Actor)->unk_60   = rot;
    SELF(Actor)->screen_x = (u16)sxy.vx;
    SELF(Actor)->screen_y = (u16)sxy.vy;
    if ((u8)g_AreaGridActorCount < 0x28) {
        g_AreaGridActors[(u8)g_AreaGridActorCount] = (s32)g_Self;
        g_AreaGridActorCount++;
        if (SELF(Actor)->header.flags & ACTOR_FLAG_SELECTION_EFFECT) {
            func_80161454((u32)g_Self);
        }
    }
}
#else
INCLUDE_ASM(Area_AddGridActor);
#endif
