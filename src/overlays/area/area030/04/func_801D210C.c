#include "area030_04.h"

/* Seeds the AREA030 battle-intro scratch record: it captures the
 * world anchor pair, samples the ground height at it, with Area_SampleHeight, scales the
 * entry's height byte into the record's clip value, clamps the height plus 0x100,
 * and primes the table pointers and draw state for the next frame. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D210C(void) {
    s32 value;
    u32 index;

    FISHING_STATE->motion_34.unk_34 = D_80145EC4;
    FISHING_STATE->y_38.pos_y       = D_80145EC8 - 0x8000;
    FISHING_STATE->bounce_3C.half.key_3E =
        (s16)(Area_SampleHeight(FISHING_STATE->motion_34.unk_34, D_80145EC8 - 0x8000) + 0x100);

    value                       = D_801E320C->byte_02 * D_801440BC / 255 + 8;
    FISHING_STATE->cue_index_06 = (u8)(value / 15);
    if (FISHING_STATE->cue_index_06 >= 4) {
        FISHING_STATE->cue_index_06 = 3;
    }
    FISHING_STATE->cursor_10 = value;

    value                    = FISHING_STATE->y_38.pos_y - (FISHING_STATE->cursor_10 << 15);
    FISHING_STATE->cursor_10 = value;
    if (value > 0x3BFFFF) {
        g_AreaScrollTargetY = 0x3C0000;
    } else if (value > 0x14FFFF) {
        g_AreaScrollTargetY = value;
    } else {
        g_AreaScrollTargetY = 0x150000;
    }

    g_AreaCameraStep              = 0;
    g_SpadWork[0xC]               = 0;
    FISHING_STATE->step_14        = *(u32*)(D_801E1D38 + FISHING_STATE->cue_index_06 * 8);
    FISHING_STATE->flags_24       = 0;
    FISHING_STATE->step_limit_20  = *(u32*)(D_801E1D3C + FISHING_STATE->cue_index_06 * 8);
    FISHING_STATE->state_29       = 5;
    FISHING_STATE->counter_48     = 1;
    FISHING_STATE->flags_00       = (u8)(FISHING_STATE->flags_00 & ~ACTOR_FLAG_SEMI_TRANSPARENT);
    FISHING_STATE->saved_index_0B = 0;
    FISHING_STATE->tint_5D        = 0;
    FISHING_STATE->tint_5E        = 0;
    FISHING_STATE->tint_5F        = 0;
    FISHING_STATE->state_2A       = 0;
    FISHING_STATE->unk_60         = 0;
    FISHING_STATE->unk_64         = 0;
    FISHING_STATE->unk_68         = 0;
    FISHING_STATE->unk_6C         = 0;
    FISHING_STATE->counter_48     = 1;

    Area_FindSceneRecord(D_801E3210->unk_0C);
    Actor_SelectScript(1);
    index = (u32)Actor_FindFreeSlot() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_ActorSlots[index].flags_00 = 1;
        g_ActorSlots[index].type     = 10;
    }
    FISHING_STATE->counter_07       = D_801E3210->unk_0F;
    FISHING_STATE->handler_index_01 = (u8)(FISHING_STATE->handler_index_01 + 1);
}
#else
INCLUDE_ASM(func_801D210C);
#endif
