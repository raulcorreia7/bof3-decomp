#include "battle_15.h"

/* func_800AF764 */
MATCH void Battle_ProjectRange(void) {
    s16         vec[3];
    long        flags[2];
    TILE_1*     primitive;
    BattleWork* work;
    BattleWork* store;

    work      = (BattleWork*)g_Task;
    vec[0]    = ((s32)work->range_axis_34 >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = ((s32)work->range_axis_38 >> 9) - 0x4000;
    vec[2]    = -((s16)work->unk_3E / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, &flags[0], &flags[1]);
    store         = (BattleWork*)g_Task;
    store->unk_2E = primitive->x0;
    store->unk_30 = primitive->y0;
}
