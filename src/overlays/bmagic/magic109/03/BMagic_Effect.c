#include "magic109_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    RECT         rect;
    PartyMember* work;

    if (g_Battle.target_selector == 0x80 && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Task->header.mode = 1;
    }
    if (g_Battle.target_selector == 0x40 && !(g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT)) {
        g_Task->header.mode = 1;
    }
    if (g_Task->header.mode != 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->unk_09 = 2;
    work           = g_Task;
    rect.x         = work->unk_2E.half - work->unk_09;
    rect.y         = work->unk_30.half - work->unk_09 + g_FrameBufferIndex * 240;
    rect.h = rect.w = work->unk_09 * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x340, 0x100);
    GFX_AddPrim(3, sizeof(DR_MOVE));
    if (g_Battle.target_selector & 0x40) {
        g_Task->unk_2E.half = D_801EF9D8[g_Battle.scroll_dir].x;
        g_Task->unk_30.half = D_801EF9D8[g_Battle.scroll_dir].y;
    } else {
        g_Task->unk_2E.half = D_801EF9D8[g_Battle.scroll_dir ^ 2].x;
        g_Task->unk_30.half = D_801EF9D8[g_Battle.scroll_dir ^ 2].y;
    }
    g_Task->unk_64 = 0;
    g_Task->header.mode += 1;
}

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
