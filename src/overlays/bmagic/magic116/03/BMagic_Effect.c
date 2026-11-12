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

MATCH u8* func_801EEFB8(void) {
    u8* record;
    u8  index;

    record = D_801EF2A8;
    for (index = 0; index < 128; index++, record += 0x3C) {
        if (*record == 0) {
            return record;
        }
    }
    return NULL;
}

MATCH void func_801EEFF4(void) {
    u8* record;
    u8  index;

    record = D_801EF2A8;
    index  = 0;
    do {
        *record = 0;
        index++;
        record += 0x3C;
    } while (index < 128);
}

MATCH void func_801EF020(u8* record) {
    s32 offset;

    record[0]                = 1;
    record[1]                = 0;
    record[2]                = 0x10;
    offset                   = (RANDOM_MASK(0x1FF) - 0x100) << 8;
    FIELD(s32, record, 0x04) = g_Task->pos.x.fixed + offset + offset;
    FIELD(s32, record, 0x08) = g_Task->pos.y.fixed + 0x20000;
    FIELD(s32, record, 0x0C) = g_Task->pos.z.fixed;
    FIELD(s32, record, 0x14) = g_Task->pos.x.fixed + offset;
    FIELD(s32, record, 0x18) = g_Task->pos.y.fixed;
    FIELD(s32, record, 0x1C) = g_Task->pos.z.fixed;
    record[0x34]             = RANDOM_MASK(1) << 7;
    record[0x35]             = RANDOM_MASK(1) << 7;
    record[0x36]             = RANDOM_MASK(1) << 7;
    FIELD(s32, record, 0x24) = offset >> 1;
    FIELD(s32, record, 0x28) = 0x10000;
    FIELD(s32, record, 0x2C) = 0;
    record[0x38]             = 0;
    record[0x39]             = 0;
    record[0x3A]             = 0;
}

INCLUDE_ASM(func_801EF118);

MATCH void func_801EF258(void) {
    u8* record;
    u8  i;

    for (i = 0; i < 8; i++) {
        record = func_801EEFB8();
        if (record != NULL) {
            func_801EF020(record);
        }
    }
}
