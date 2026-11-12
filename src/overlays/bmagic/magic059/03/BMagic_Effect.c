#include "magic059_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED0C, func_801EF118);
    Battle_ProjectRange();

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F0694[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F0694[i];
            g_BattleEffectBattler = D_801F0694[i].target.party;
            func_801EFE48();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED0C);

INCLUDE_ASM(func_801EF118);

/* func_801EF1E0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

INCLUDE_ASM(func_801EF224);

MATCH void func_801EF4C4(void) {
    u8* work;

    *(u8*)((u8*)g_Task + 0x09) = 0;
    g_Task->timer              = 0;
    work                       = (u8*)g_Task;
    work[2] += 1;
}

MATCH void func_801EF504(void) {
    PartyMember* work;

    work = g_Task;
    work->unk_09++;
    work = g_Task;
    work->timer += 2;
    if (work->timer == 32) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF570(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 160) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

/* func_801EF5C0 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

MATCH void func_801EF638(void) {
    PartyMember* src;
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;

    PushMatrix();
    src                      = (PartyMember*)g_BattleEffectBattler;
    rot.vx                   = 0;
    rot.vy                   = 0;
    rot.vz                   = 0;
    g_Task->pos.x.fixed      = src->pos.x.fixed;
    g_Task->pos.y.fixed      = src->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(src->pos.z);
    pos.vx                   = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy                   = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz                   = -COORD_INT(g_Task->pos.z) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

INCLUDE_ASM(func_801EF70C);

MATCH void func_801EFE48(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 5, 1, g_Task);
}

INCLUDE_ASM(func_801EFE8C);

MATCH void func_801F0018(void) {
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + g_Task->unk_14;
    g_Task->timer       = 0;
    g_Task->header.step++;
}

MATCH void func_801F0070(void) {
    PartyMember* work;

    work = g_Task;
    work->unk_09++;
    work = g_Task;
    work->timer++;
    if (work->timer == 32) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F00DC(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 160) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F012C(void) {
    PartyMember* work;
    u8           count;

    work = g_Task;
    work->unk_09++;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Actor_Clear();
    }
}

MATCH void func_801F01A4(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[0] = 32;
    prim->x0                         = g_Task->unk_2E.half + FIXED_MUL(rcos(3328), D_1F800000.view.effect.params[0]);
    prim->y0                         = g_Task->unk_30.half + FIXED_MUL(rsin(3328), D_1F800000.view.effect.params[0]);
    prim->x1                         = g_Task->unk_2E.half + FIXED_MUL(rcos(2560), D_1F800000.view.effect.params[0]);
    prim->y1                         = g_Task->unk_30.half + FIXED_MUL(rsin(2560), D_1F800000.view.effect.params[0]);
    prim->x2                         = g_Task->unk_2E.half + FIXED_MUL(rcos(512), D_1F800000.view.effect.params[0]);
    prim->y2                         = g_Task->unk_30.half + FIXED_MUL(rsin(512), D_1F800000.view.effect.params[0]);
    prim->x3                         = g_Task->unk_2E.half + FIXED_MUL(rcos(1536), D_1F800000.view.effect.params[0]);
    prim->y3                         = g_Task->unk_30.half + FIXED_MUL(rsin(1536), D_1F800000.view.effect.params[0]);
    prim->tpage                      = GetTPage(0, 1, 832, 256);
    prim->clut                       = GetClut(0, 506);
    prim->u0                         = 0;
    prim->v0                         = 0;
    prim->u1                         = 31;
    prim->v1                         = 0;
    prim->u2                         = 0;
    prim->v2                         = 32;
    prim->u3                         = 31;
    prim->v3                         = 32;
    D_1F800000.view.effect.params[6] = g_Task->timer * g_Task->param.unk_0B;
    prim->r0                         = D_1F800000.view.effect.params[6];
    prim->g0                         = D_1F800000.view.effect.params[6];
    prim->b0                         = D_1F800000.view.effect.params[6];
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F0490 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F04F4 */
#include "overlays/bmagic/Actor_Clear.h"

INCLUDE_ASM(func_801F0544);
