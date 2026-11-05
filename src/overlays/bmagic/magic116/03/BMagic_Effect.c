#include "magic116_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    PartyBattler* saved_work;

    g_Task->pos.x.raw = D_801EC2E0->target.party->pos.x.raw;
    g_Task->pos.y.raw = D_801EC2E0->target.party->pos.y.raw;
    g_Task->pos.z.raw = D_801EC2E0->target.party->pos.z.raw + 0x01000000;
    func_801EEFF4();
    saved_work = g_Task;
    g_Task     = D_801EC2E0->target.party;
    Actor_SelectScript(1U);
    g_Task = saved_work;
    saved_work->mode += 1;
}

MATCH void func_801EED2C(void) {
    PartyBattler* saved;

    saved  = g_Task;
    g_Task = D_801EC2E0->target.party;
    if (func_8014DAEC() & BYTE_MASK) {
        g_Task        = saved;
        saved->unk_09 = 0x78;
        g_Task->mode++;
        SND_PlayCue(0x100);
    }
    g_Task = saved;
}

/* Best 5 differences: lui v1 at 0x801EEDF0; adjust register allocation. */
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

INCLUDE_ASM(func_801EF020);

INCLUDE_ASM(func_801EF118);

MATCH void func_801EF258(void) {
    s32 result;
    u8  i;

    for (i = 0; i < 8; i++) {
        result = func_801EEFB8();
        if (result != 0) {
            func_801EF020(result);
        }
    }
}
