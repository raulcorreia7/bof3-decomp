#include "magic101_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Magic101Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);
    if (g_Task->timer != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF07C();
        PopMatrix();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EECCC(void) {
    u32 slot;
    u32 counter;
    u32 wave;
    u8  facing;

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (g_Battle.active_battler >= BATTLE_PARTY_CHARACTERS_COUNT) {
            facing = ((PartyMember*)D_8014637C)->facing;
            goto have_facing;
        }
    } else if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        facing = ((PartyMember*)D_8014637C)->facing;
        goto have_facing;
    }
    facing = ((PartyMember*)D_8014637C)->facing ^ 0x2;
have_facing:
    g_Task->facing = facing;
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0x30;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;
    counter = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x1B) & BYTE_MASK;
        wave                               = (counter >> 2) * 3;
        wave                               = (wave << 2) + 1;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = counter;
        g_BattleEffects[slot].arg.unk_09   = wave;
        g_BattleEffects[slot].target.party = g_Task;
        g_Task->param.unk_0B += 1;
        counter += 1;
    } while (counter < 0x10);
    SND_QueueSelectionFx(0x100);
}
#else
INCLUDE_ASM(func_801EECCC);
#endif

MATCH void func_801EEE68(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 16) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

MATCH void func_801EEF20(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF07C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = FIXED_MUL(rsin((g_FrameCount & 0x1F) << 7), 0x10) + 0x80;
    D_1F800000.view.effect.params[4] = g_Task->timer * 6;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);

    for (i = 1; i <= 8; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[4]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }

    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

/* func_801EF310 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF354(void) {
    SYS_DISPATCH_BYTE(D_801EFCE8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF78C();
        func_801EF88C();
        PopMatrix();
    }
}

MATCH void func_801EF3DC(void) {
    PartyMember* work;
    u8           counter;
    s32          value;

    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (counter == 0) {
        g_Task->facing       = g_BattleEffectBattler->facing;
        g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed + 0x01800000;
        g_Task->param.unk_0B = g_Task->unk_04 * 4 & 0x3F;
        work                 = g_Task;
        value                = D_801EFCC0[work->unk_04];
        work->unk_10         = 0x60;
        work->unk_14         = 0x20;
        work->unk_09         = work->unk_04 * 4 + 1;
        work->unk_0C         = value << 8;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF4DC);

INCLUDE_ASM(func_801EF580);

MATCH void func_801EF690(void) {
    u8           counter;
    PartyMember* work;

    g_Task->param.unk_0B += 4;
    work = g_Task;
    work->unk_10 += work->unk_1C;
    counter      = work->unk_09 - 1;
    work->unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF700(void) {
    u8           counter;
    s32          value;
    PartyMember* work;

    g_Task->param.unk_0B += g_Task->timer >> 1;
    work         = g_Task;
    counter      = work->timer - 1;
    value        = work->unk_1C - 2;
    work->timer  = counter;
    work->unk_1C = value;
    work->unk_10 += value;
    if (!(counter & 0xFF)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF78C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    if (BATTLE_ACTIVE_WORK->facing & 1) {
        rot.vx = 0;
        rot.vy = g_Task->unk_0C;
        rot.vz = 0;
    } else {
        rot.vx = g_Task->unk_0C;
        rot.vy = 0;
        rot.vz = 0;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF88C);
