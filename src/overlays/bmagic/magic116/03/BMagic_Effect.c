#include "magic116_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    PartyMember* saved_work;

    g_Task->pos.x.fixed = D_801EC2E0->target.party->pos.x.fixed;
    g_Task->pos.y.fixed = D_801EC2E0->target.party->pos.y.fixed;
    g_Task->pos.z.fixed = D_801EC2E0->target.party->pos.z.fixed + 0x01000000;
    func_801EEFF4();
    saved_work = g_Task;
    g_Task     = D_801EC2E0->target.party;
    Actor_SelectScript(1U);
    g_Task = saved_work;
    saved_work->header.mode += 1;
}

MATCH void func_801EED2C(void) {
    PartyMember* saved;

    saved  = g_Task;
    g_Task = D_801EC2E0->target.party;
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_Task        = saved;
        saved->unk_09 = 0x78;
        g_Task->header.mode++;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    }
    g_Task = saved;
}

INCLUDE_ASM(func_801EEDB0);

MATCH void func_801EEE34(void) {
    u16* flags;

    if ((func_801EF118() & BYTE_MASK) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EEE7C);

MATCH Magic116Quad* func_801EEFB8(void) {
    Magic116Quad* record;
    u8            index;

    record = D_801EF2A8;
    for (index = 0; index < 128; index++, record++) {
        if (record->state == 0) {
            return record;
        }
    }
    return NULL;
}

MATCH void func_801EEFF4(void) {
    Magic116Quad* record;
    u8            index;

    record = D_801EF2A8;
    index  = 0;
    do {
        record->state = 0;
        index++;
        record++;
    } while (index < 128);
}

MATCH void func_801EF020(Magic116Quad* record) {
    s32 offset;

    record->state          = 1;
    record->unk_01         = 0;
    record->timer          = 16;
    offset                 = (RANDOM_MASK(0x1FF) - 0x100) << 8;
    record->pos.x.fixed    = g_Task->pos.x.fixed + offset + offset;
    record->pos.y.fixed    = g_Task->pos.y.fixed + 0x20000;
    record->pos.z.fixed    = g_Task->pos.z.fixed;
    record->unk_14.x.fixed = g_Task->pos.x.fixed + offset;
    record->unk_14.y.fixed = g_Task->pos.y.fixed;
    record->unk_14.z.fixed = g_Task->pos.z.fixed;
    record->color[0]       = RANDOM_MASK(1) << 7;
    record->color[1]       = RANDOM_MASK(1) << 7;
    record->color[2]       = RANDOM_MASK(1) << 7;
    record->speed.x.fixed  = offset >> 1;
    record->speed.y.fixed  = 0x10000;
    record->speed.z.fixed  = 0;
    record->unk_38[0]      = 0;
    record->unk_38[1]      = 0;
    record->unk_38[2]      = 0;
}

INCLUDE_ASM(func_801EF118);

MATCH void func_801EF258(void) {
    Magic116Quad* record;
    u8            i;

    for (i = 0; i < 8; i++) {
        record = func_801EEFB8();
        if (record != NULL) {
            func_801EF020(record);
        }
    }
}
