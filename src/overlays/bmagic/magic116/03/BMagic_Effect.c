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

MATCH void func_801EEE7C(BMagicStreakSegment* segment) {
    POLY_G4* prim;
    /* FAKE: retail reserves 8 bytes below point[] that no statement uses; pure C 60 of 79 instructions. */
    FAKE_STACK_PADS(u8, 8);
    s32 point[3];

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    point[0] = segment->head.x + 0x1000;
    point[1] = segment->head.y;
    point[2] = segment->head.z;
    Area_ProjectPoint(point, POLY_XY(prim, 0));
    point[0] = segment->head.x - 0x1000;
    Area_ProjectPoint(point, POLY_XY(prim, 1));
    point[0] = segment->tail.x + 0x1000;
    point[1] = segment->tail.y;
    point[2] = segment->tail.z;
    Area_ProjectPoint(point, POLY_XY(prim, 2));
    point[0] = segment->tail.x - 0x1000;
    Area_ProjectPoint(point, POLY_XY(prim, 3));
    prim->r0 = prim->r1 = segment->head_red;
    prim->g0 = prim->g1 = segment->head_green;
    prim->b0 = prim->b1 = segment->head_blue;
    prim->r2 = prim->r3 = segment->tail_red;
    prim->g2 = prim->g3 = segment->tail_green;
    prim->b2 = prim->b3 = segment->tail_blue;
    GFX_AddPrim(3, sizeof(POLY_G4));
}

MATCH BMagicStreakSegment* func_801EEFB8(void) {
    BMagicStreakSegment* record;
    u8                   index;

    record = D_801EF2A8;
    for (index = 0; index < 128; index++, record++) {
        if (record->active == 0) {
            return record;
        }
    }
    return NULL;
}

MATCH void func_801EEFF4(void) {
    BMagicStreakSegment* record;
    u8                   index;

    record = D_801EF2A8;
    index  = 0;
    do {
        record->active = 0;
        index++;
        record++;
    } while (index < 128);
}

INCLUDE_ASM(func_801EF020);

INCLUDE_ASM(func_801EF118);

MATCH void func_801EF258(void) {
    BMagicStreakSegment* result;
    u8                   i;

    for (i = 0; i < 8; i++) {
        result = func_801EEFB8();
        if (result != NULL) {
            func_801EF020(result);
        }
    }
}
