#include "magic116_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    PartyMember* saved_work;

    g_Task->pos.x.fixed = D_801EC2E0->target.party->pos.x.fixed;
    g_Task->pos.y.fixed = D_801EC2E0->target.party->pos.y.fixed;
    g_Task->pos.z.fixed = D_801EC2E0->target.party->pos.z.fixed + 0x01000000;
    func_801EEFF4();
    saved_work = g_Task;
    g_Task     = D_801EC2E0->target.party;
    Script_Select(1U);
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
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    }
    g_Task = saved;
}

MATCH void func_801EEDB0(void) {
    u8 timer;

    func_801EF258();
    func_801EF118();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
        func_800A9820(g_Battle.target_selector);
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0x01));
    }
}

MATCH void func_801EEE34(void) {
    u16* flags;

    if ((func_801EF118() & BYTE_MASK) == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        Effect_Reset();
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
    point[0] = segment->head.vx + 0x1000;
    point[1] = segment->head.vy;
    point[2] = segment->head.vz;
    Camera_ProjectPoint(point, POLY_XY(prim, 0));
    point[0] = segment->head.vx - 0x1000;
    Camera_ProjectPoint(point, POLY_XY(prim, 1));
    point[0] = segment->tail.vx + 0x1000;
    point[1] = segment->tail.vy;
    point[2] = segment->tail.vz;
    Camera_ProjectPoint(point, POLY_XY(prim, 2));
    point[0] = segment->tail.vx - 0x1000;
    Camera_ProjectPoint(point, POLY_XY(prim, 3));
    setRGB0(prim, prim->r1 = segment->head_color.r, prim->g1 = segment->head_color.g, prim->b1 = segment->head_color.b);
    setRGB2(prim, prim->r3 = segment->tail_color.r, prim->g3 = segment->tail_color.g, prim->b3 = segment->tail_color.b);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
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

MATCH void func_801EF020(BMagicStreakSegment* record) {
    s32 offset;

    record->active       = 1;
    record->unk_01       = 0;
    record->life         = 16;
    offset               = (RANDOM_MASK(0x1FF) - 0x100) << 8;
    record->head.vx      = g_Task->pos.x.fixed + offset + offset;
    record->head.vy      = g_Task->pos.y.fixed + 0x20000;
    record->head.vz      = g_Task->pos.z.fixed;
    record->tail.vx      = g_Task->pos.x.fixed + offset;
    record->tail.vy      = g_Task->pos.y.fixed;
    record->tail.vz      = g_Task->pos.z.fixed;
    record->head_color.r = RANDOM_MASK(1) << 7;
    record->head_color.g = RANDOM_MASK(1) << 7;
    record->head_color.b = RANDOM_MASK(1) << 7;
    record->velocity.vx  = offset >> 1;
    record->velocity.vy  = 0x10000;
    record->velocity.vz  = 0;
    record->tail_color.r = 0;
    record->tail_color.g = 0;
    record->tail_color.b = 0;
}

MATCH u8 func_801EF118(void) {
    BMagicStreakSegment* record;
    u8                   i;
    u8                   drawn;

    drawn = 0;
    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100) & HALF_MASK);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MODE));
    func_801AFE18();
    for (record = D_801EF2A8, i = 0; i < 128; record++, i++) {
        if (record->active != 0) {
            func_801EEE7C(record);
            drawn = 1;
            record->head.vx += record->velocity.vx;
            record->head.vy += record->velocity.vy;
            record->head.vz += record->velocity.vz;
            record->tail.vx += record->velocity.vx;
            record->tail.vy += record->velocity.vy;
            record->tail.vz += record->velocity.vz;
            if (--record->life == 0) {
                record->active = 0;
            }
        }
    }
    return drawn;
}

MATCH void func_801EF258(void) {
    BMagicStreakSegment* record;
    u8                   i;

    for (i = 0; i < 8; i++) {
        record = func_801EEFB8();
        if (record != NULL) {
            func_801EF020(record);
        }
    }
}
