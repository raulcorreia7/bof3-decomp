#include "magic108_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED1C};
    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

MATCH void func_801EEC5C(void) {
    PartyBattler* src;
    u32           offset;

    src                                         = g_BattleSelectedActor;
    offset                                      = (Battle_AllocEffect(1, 0x1A) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
    FIELD(PartyBattler*, D_801EC3A4, offset)    = g_SpadWork;
    FIELD(u8, D_801EC338, offset)               = src->word_08.byte.facing_08;
    FIELD(BattleFix32, D_801EC364, offset)      = src->coord_x_34;
    FIELD(BattleFix32, D_801EC368, offset)      = src->coord_y_38;
    FIELD(BattleWorkWord3C, D_801EC36C, offset) = src->word_3C;
    g_SpadWork->word_08.byte.unk_0B             = 0;
    g_SpadWork->step_01 += 1;
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EED7C(void) {
    SYS_DISPATCH_BYTE(D_801EFC9C, g_SpadWork->step_01);
    if (g_SpadWork->flags_00 != 0) {
        func_801EF5C0();
        func_801EF6C0();
        PopMatrix();
        func_801EF180();
        func_801EF2D4();
        PopMatrix();
    }
}

MATCH void func_801EEE0C(void) {
    PartyBattler* battler;
    u32           slot;

    g_SpadWork->unk_0C = 0x20000;
    g_SpadWork->unk_10 = 0;
    func_801DD350(g_SpadWork);
    g_SpadWork->coord_x_34.raw += g_SpadWork->unk_0C;
    g_SpadWork->coord_y_38.raw += g_SpadWork->unk_10;
    g_SpadWork->word_3C.half.span_3E = (u16)g_SpadWork->word_3C.half.span_3E + 0xC0;
    g_SpadWork->unk_18               = g_SpadWork->coord_x_34.raw;
    g_SpadWork->unk_1C               = g_SpadWork->coord_y_38.raw;
    g_SpadWork->unk_20               = g_SpadWork->word_3C.word;
    MATCH_FAKE_BARRIER(); /* FAKE: keeps the g_BattleActiveBattler read below the coord copy stores */
    slot = g_BattleActiveBattler;
    if (slot < BATTLE_PARTY_SLOT_COUNT) {
        battler = &g_BattlePartyBattlers[slot];
    } else {
        battler = (PartyBattler*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    g_SpadWork->coord_x_34.raw        = battler->coord_x_34.raw;
    g_SpadWork->coord_y_38.raw        = battler->coord_y_38.raw;
    g_SpadWork->word_3C.word          = battler->word_3C.word + 0xC00000;
    g_SpadWork->word_08.byte.unk_0B   = 0;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->step_01 += 1;
    SND_QueueSelectionFx(0x100);
}

MATCH void func_801EEF48(void) {
    s32 vec[4];

    g_SpadWork->word_08.byte.timer_0A += 1;
    vec[0] = ((s32)g_SpadWork->unk_18 >> 9) - 0x4000;
    vec[1] = ((s32)g_SpadWork->unk_1C >> 9) - 0x4000;
    vec[2] = (s32)g_SpadWork->unk_20 >> 0x11;
    /* The retail build passes the never-written slot after the vector. */
    func_800AF3A0(vec[0], vec[1], vec[2], vec[3], 0x20);
    if (func_800AF6B8(g_SpadWork->unk_18, g_SpadWork->unk_1C, g_SpadWork->unk_20, 0x8000) != 0) {
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EF020(void) {
    u8 temp_v0;

    temp_v0                           = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v0;
    if (!(temp_v0 & 0x1F)) {
        SND_QueueSelectionFx(0x101);
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->step_01 += 1;
    }
}

#include "overlays/bmagic/Effect_AdvanceOnTick.h"

MATCH void func_801EF0E0(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 96) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EF130(void) {
    u8 temp_v1;

    temp_v1                           = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = temp_v1;
    if ((temp_v1 & 0xFF) == 0x80) {
        D_801EB4E0->word_08.byte.unk_0B = 0xFF;
        func_801E5988();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF180(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    u8      timer;

    PushMatrix();
    switch (g_SpadWork->word_08.byte.facing_08) {
        case 0:
            timer  = g_SpadWork->word_08.byte.timer_0A;
            rot.vy = 0;
            rot.vz = 0x800;
            rot.vx = (~timer & 0x1F) << 7;
            break;
        case 1:
            rot.vx = 0;
            timer  = g_SpadWork->word_08.byte.timer_0A;
            rot.vz = 0xC00;
            rot.vy = (~timer & 0x1F) << 7;
            break;
        case 2:
            timer  = g_SpadWork->word_08.byte.timer_0A;
            rot.vy = 0;
            rot.vz = 0;
            rot.vx = (~timer & 0x1F) << 7;
            break;
        case 3:
            rot.vx = 0;
            timer  = g_SpadWork->word_08.byte.timer_0A;
            rot.vz = 0x400;
            rot.vy = (~timer & 0x1F) << 7;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_SpadWork);
}
#else
INCLUDE_ASM(func_801EF180);
#endif

INCLUDE_ASM(func_801EF2D4);

INCLUDE_ASM(func_801EF5C0);

INCLUDE_ASM(func_801EF6C0);
