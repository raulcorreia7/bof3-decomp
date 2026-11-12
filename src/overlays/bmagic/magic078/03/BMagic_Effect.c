#include "magic078_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EECFC, Effect_PlayOnIdleTick};
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(4, 0xC);

    SYS_DISPATCH_BYTE(handlers, g_Task->header.mode);

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(4, 0xC);
}

MATCH void func_801EECFC(void) {
    PartyMember* actor;
    PartyMember* battler;
    u8           first;
    u8           slot;

    /* kept: retail rescales the slot index and re-reads g_BattleEffects at every store; a row
     * pointer changes the bytes. */
    actor                               = g_Battle.selected_actor;
    first                               = Battle_AllocEffect(1, 0xD);
    g_BattleEffects[first].target.party = g_Task;
    g_BattleEffects[first].header.mode  = 0;
    g_BattleEffects[first].arg.unk_09   = 0;
    battler                             = g_BattleEffectBattler;
    g_BattleEffects[first].pos.x.fixed  = battler->pos.x.fixed;
    g_BattleEffects[first].pos.y.fixed  = battler->pos.y.fixed;
    g_BattleEffects[first].pos.z.fixed  = battler->pos.z.fixed + TO_COORD(512);
    slot                                = Battle_AllocEffect(1, 0xD);
    g_BattleEffects[slot].target.effect = &g_BattleEffects[first];
    g_BattleEffects[slot].unk_4C        = g_Task;
    g_BattleEffects[slot].header.mode   = 1;
    g_BattleEffects[slot].arg.unk_09    = 0;
    g_BattleEffects[slot].pos.x.fixed   = actor->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed   = actor->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed   = actor->pos.z.fixed + TO_COORD(256);
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

/* func_801EEEE4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

INCLUDE_ASM(func_801EEF28);

MATCH void func_801EF08C(void) {
    u8 count;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) == 0xC) {
        g_Task->timer = 15;
        g_Task->header.step += 1;
        return;
    }
    g_Task->unk_09 = count + 1;
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

MATCH void func_801EF12C(void) {
    s32 angle;
    s32 target;
    s32 dir;

    angle = ratan2(g_Battle.selected_actor->pos.y.fixed - g_Task->pos.y.fixed, g_Battle.selected_actor->pos.x.fixed - g_Task->pos.x.fixed);
    dir   = g_Task->unk_0C;
    if (dir < 0) {
        dir += 0x3F;
    }
    dir >>= 6;
    target = angle & 0xFFF;
    if (target < 0) {
        target += 0x3F;
    }
    if (dir == (target >> 6)) {
        g_Task->timer = 15;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF1CC(void) {
    u8 count;

    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 1;
        g_Task->header.step              = g_Task->header.step + 1;
    }
}

MATCH void func_801EF228(void) {
    if (g_BattleEffectBattler->param.unk_0B == 2) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF278(void) {
    g_Task->timer += 8;
    if (g_Task->timer >= 129U) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2CC(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF318);

MATCH void func_801EFE14(LINE_F4* prim, s32* out, SVECTOR v0, SVECTOR v1, SVECTOR v2, SVECTOR v3) {
    long p;
    long flag;

    SetLineF4(prim);
    SetSemiTrans(prim, 1);
    setRGB0(prim, 0x40, 0x40, 0xC0);
    *out = RotAverage4(&v0, &v1, &v2, &v3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
}

MATCH void func_801EFEB8(void) {
    PartyMember* work;
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;

    PushMatrix();
    work   = g_Task;
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    if (work->slot == 13) {
        rot.vz = work->unk_0C;
    }
    pos.vx = (work->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (work->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(work->pos.z) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801EFF84(void) {
    s32 tpage;

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(4, 0xC);

    if (g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F02FC();
        PopMatrix();
    }

    SYS_DISPATCH_BYTE(D_801F08C4, g_Task->header.step);

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(4, 0xC);
}

MATCH void func_801F00A0(void) {
    if (g_Task->unk_4C->param.unk_0B == 1) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

/* func_801F00EC */
MATCH void Effect_PlayCueAtTick(void) {
    u8 count;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) == 8) {
        SND_QueueSelectionFx(0x101);
        g_Task->header.step += 1;
        return;
    }
    g_Task->unk_09 = count + 1;
}

MATCH void func_801F014C(void) {
    func_800AF2B4(g_BattleEffectBattler, 0x30);
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) + 0x10;
    if (func_800AF5FC(g_BattleEffectBattler, 0x1C000) != 0) {
        g_Task->timer = 30;
        g_Task->header.step += 1;
    }
}

/* func_801F01D0 */
MATCH void Effect_PlayCueOnTimeout(void) {
    PartyMember* work;

    work        = g_Task;
    work->timer = work->timer - 1;
    if (work->timer == 0) {
        SND_QueueSelectionFx(0x102);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0230(void) {
    PartyMember* linked;

    linked = g_Task->unk_4C;
    func_800AF2B4(g_BattleEffectBattler, 8);
    if (func_800AF5FC(g_BattleEffectBattler, 0x4000) != 0) {
        linked->param.unk_0B = 2;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F02B4(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 8) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F02FC);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
