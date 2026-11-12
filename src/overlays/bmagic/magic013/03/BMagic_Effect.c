#include "magic013_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic010SharedSteps handlers = D_801EEC04;
    PartyMember*        saved_task;
    PartyMember*        saved_battler;
    u8                  i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            func_801EFDB4();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED28);

#include "overlays/bmagic/Effect_Pause.h"

MATCH void func_801EEEA0(void) {
    u8*          selector;
    u32          slot;
    PartyMember* work;

    selector = (u8*)&g_Battle.target_selector;
    if (!(Battle_SlotIsBlocked(*selector) & BYTE_MASK) && (func_800AED5C(1, *selector) & BYTE_MASK)) {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].unk_04       = 4;
        g_BattleEffects[slot].arg.unk_09   = 0x18;
        g_BattleEffects[slot].unk_0A       = 4;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEFD0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(D_801F03C0, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_801EF4F0();
        func_801EF79C();
        PopMatrix();
        func_801EF648();
        func_801EFAA8();
        PopMatrix();
    }
}

MATCH void func_801EF0A4(void) {
    g_Task->facing = g_BattleEffectBattler->facing;
    g_Task->unk_0C = 0x20000;
    g_Task->unk_10 = 0;
    func_801DD350(g_Task);
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(256);
    g_Task->unk_0C      = -0x6000;
    g_Task->unk_10      = 0;
    func_801DD350(g_Task);
    g_Task->unk_04       = 0;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->timer        = 4;
    g_Task->header.step += 1;
}

#include "overlays/bmagic/Effect_CountUpWorkByteAndStep.h"

INCLUDE_ASM(func_801EF1F0);

INCLUDE_ASM(func_801EF36C);

MATCH void func_801EF484(void) {
    PartyMember* work;
    PartyMember* active;

    work = g_Task;
    if (work->param.unk_0B == 0) {
        work->unk_04 = work->unk_04 - 1;
        if (work->unk_04 == 0) {
            active               = BATTLE_ACTIVE_WORK;
            active->param.unk_0B = active->param.unk_0B - 1;
            func_801E5988();
        }
    }
}

INCLUDE_ASM(func_801EF4F0);

INCLUDE_ASM(func_801EF648);

INCLUDE_ASM(func_801EF79C);

INCLUDE_ASM(func_801EFAA8);

MATCH void func_801EFDB4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 1, g_Task);
}

MATCH void func_801EFDF8(void) {
    SYS_DISPATCH_BYTE(D_801F03DC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->unk_09 != 0) {
        func_801F00A8();
        func_801F0164();
        PopMatrix();
    }
}

MATCH void func_801EFE80(void) {
    PartyMember* actor;
    s32*         angle_cell;
    u8           count;
    u8           phase;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        phase               = g_Task->param.unk_0B;
        angle_cell          = &D_1F800004;
        *angle_cell         = phase << 7;
        actor               = g_Battle.selected_actor;
        g_Task->pos.x.fixed = actor->pos.x.fixed + ((rsin(*angle_cell) * 0x100) >> 9);
        g_Task->pos.y.fixed = actor->pos.y.fixed + ((rcos(*angle_cell) * 0x100) >> 9);
        g_Task->pos.z.fixed = actor->pos.z.fixed;
        g_Task->unk_14      = RANDOM_MASK(7) + 0x80;
        g_Task->unk_20      = -0xC;
        g_Task->unk_09      = 16;
        g_Task->header.step++;
    }
}

INCLUDE_ASM(func_801EFF88);

MATCH void func_801F00A8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = g_Task->unk_09 << 6;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

MATCH void func_801F0164(void) {
    POLY_F3* prim;
    long     depth;
    long     flag;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), NULL);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(prim);
    SetSemiTrans(prim, 1);
    D_1F800014[0].vx = (u32)rsin(0) >> 8;
    D_1F800014[0].vy = (u32)rcos(0) >> 8;
    D_1F800014[0].vz = 0;
    D_1F800014[1].vx = (u32)rsin(DEG(120)) >> 8;
    D_1F800014[1].vy = (u32)rcos(DEG(120)) >> 8;
    D_1F800014[1].vz = 0;
    D_1F800014[2].vx = (u32)rsin(DEG(240)) >> 8;
    D_1F800014[2].vy = (u32)rcos(DEG(240)) >> 8;
    D_1F800014[2].vz = 0;
    RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    prim->r0 = (rand() & 0xF) * g_Task->unk_09;
    prim->g0 = (rand() & 0xF) * g_Task->unk_09;
    prim->b0 = (rand() & 0xF) * g_Task->unk_09;
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_F3));
}

/* func_801F0358 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
