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

    Area_FindSceneRecord(g_SpadWork->unk_0B);
    func_8019BF78();
    g_SpadWork->unk_29            = 6;
    g_SpadWork->unk_48            = 1;
    g_SpadWork->flags_24          = 0;
    g_SpadWork->unk_2A            = 0;
    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    work                          = g_SpadWork;
    work->option_flags            = 0;
    motion                        = (GameMotionFields*)work;
    motion->unk_0C                = 0;
    motion->unk_10                = 0;
    motion->unk_14                = 0;
    motion->unk_18                = 0;
    motion->unk_1C                = 0;
    motion->unk_20                = 0;
    g_SpadWork->unk_0A            = 0;
    Actor_SelectScript(0);
    g_SpadWork->unk_01++;
}
