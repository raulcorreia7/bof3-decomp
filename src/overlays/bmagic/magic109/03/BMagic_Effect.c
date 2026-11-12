#include "magic109_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

MATCH void func_801EEEAC(void) {
    u8 count;

    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x54) {
        g_Task->header.mode += 1;
        g_Task->timer = 64;
    }
    func_801EF0F8(g_Task->unk_64);
}

MATCH void func_801EEF30(void) {
    s32 raised_offset;
    s32 lowered_offset;
    u8  timer;

    timer         = g_Task->timer;
    g_Task->timer = timer + 0xFF;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->header.mode += 1;
    }
    func_801EF0F8(g_Task->unk_64);
    if (g_Task->param.unk_0B == 0) {
        raised_offset  = g_Task->unk_64 + 8;
        g_Task->unk_64 = raised_offset;
        if (raised_offset >= 0x80) {
            g_Task->param.unk_0B = 1;
        }
    } else {
        lowered_offset = g_Task->unk_64 - 8;
        g_Task->unk_64 = lowered_offset;
        if (lowered_offset < -0x7F) {
            g_Task->param.unk_0B = 0;
        }
    }
}

MATCH void func_801EF008(void) {
    u8  timer;
    s32 offset;

    timer          = g_Task->unk_09 - 2;
    g_Task->unk_09 = timer;
    if (timer == 2) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    func_801EF0F8(g_Task->unk_64);
    if (g_Task->param.unk_0B == 0) {
        offset         = g_Task->unk_64 + 8;
        g_Task->unk_64 = offset;
        if (offset >= 0x80) {
            g_Task->param.unk_0B = 1;
        }
    } else {
        offset         = g_Task->unk_64 - 8;
        g_Task->unk_64 = offset;
        if (offset < -0x7F) {
            g_Task->param.unk_0B = 0;
        }
    }
}

INCLUDE_ASM(func_801EF0F8);
