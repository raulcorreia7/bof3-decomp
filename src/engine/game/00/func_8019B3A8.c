#include "game_00.h"

/* Per-frame movement accumulators of the work record; the shared layout still
 * carries 0x0C-0x20 as padding, so the span gets a local typed view. */
typedef struct {
    u8  pad_00[0x0C];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
} GameMotionFields;

ASSERT_SIZE(GameMotionFields, 0x24);

MATCH void func_8019B3A8(void) {
    Actor*            work;
    GameMotionFields* motion;

    Area_SelectSceneRecord(g_Task->param.scene_record_id);
    func_8019BF78();
    g_Task->draw_layer   = 6;
    g_Task->unk_48       = 1;
    g_Task->active_flags = 0;
    g_Task->unk_2A       = 0;
    ACTOR_CLEAR_TINT();
    work               = g_Task;
    work->option_flags = 0;
    motion             = (GameMotionFields*)work;
    motion->unk_0C     = 0;
    motion->unk_10     = 0;
    motion->unk_14     = 0;
    motion->unk_18     = 0;
    motion->unk_1C     = 0;
    motion->unk_20     = 0;
    g_Task->unk_0A     = 0;
    Actor_SelectScript(0);
    g_Task->header.mode++;
}
