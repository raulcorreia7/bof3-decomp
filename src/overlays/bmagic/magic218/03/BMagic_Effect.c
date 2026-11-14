#include "magic218_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDB8};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* target;
    u16*         src;
    u16*         dst;
    u16          i;
    u32          slot;

    for (i = 0; i < 8; i++) {
        D_801EF790[i] = 0;
    }
    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 103) & BYTE_MASK;
    target                             = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].target.party = target;
    g_Task->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE18 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE5C(void) {
    SYS_DISPATCH_BYTE(D_801EF774, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF250();
        PopMatrix();
    }
}

MATCH void func_801EEEE4(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        src              = BATTLE_ACTIVE_WORK;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        dst->pos.z       = src->pos.z;
        dst->unk_5D      = 0x10;
        g_Task->unk_09   = 0x10;
        g_Task->timer    = 4;
        g_Task->header.step++;
    }
}

MATCH void func_801EEF84(void) {
    s32 i;
    u8  slot;

    g_Task->unk_09 += 2;
    SP_REF(s16, 0) = g_Task->unk_09 << 4;
    i              = 0;
    do {
        if (D_801EF790[i & BYTE_MASK] == 0) {
            slot = (i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK;
            if (!(Battle_SlotIsBlocked(slot) & BYTE_MASK)) {
                if (func_801EF70C(&g_BattleEnemyBattlers[i & BYTE_MASK]) != 0) {
                    if (g_Battle.active_battler != (i & BYTE_MASK) + BATTLE_PARTY_CHARACTERS_COUNT) {
                        D_801EF790[i & BYTE_MASK] = -1;
                        Battle_ApplyDamageFlags(slot, 0x10);
                    }
                }
            }
        }
        i++;
    } while ((u32)(i & BYTE_MASK) < 8);
    if (g_FrameCount & 0x1) {
        if (g_Task->timer < 32) {
            g_Task->timer += 1;
        }
    }
    if (g_Task->unk_09 == 96) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0F0(void) {
    u8 count;
    u8 timer;

    if (g_FrameCount & 0x1) {
        timer = g_Task->timer;
        if (timer < 32U) {
            g_Task->timer = timer + 1;
        }
    }
    g_Task->unk_09 += 1;
    count          = g_Task->unk_5D - 1;
    g_Task->unk_5D = count;
    if ((count << 24) == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF250(void) {
    POLY_FT4* poly;
    long      depth;
    long      flag;
    s32       tpage;
    s32       x;
    s32       y;
    u8        ring;
    u8        i;
    s16       angle;

    D_1F800000.view.effect.params[4] = (s8)g_Task->unk_5D * 8;
    D_1F800000.view.effect.params[5] = (s8)g_Task->unk_5D * 8;
    D_1F800000.view.effect.params[6] = (s8)g_Task->unk_5D * 8;
    D_1F800000.view.effect.params[0] = g_Task->timer * 16;
    D_1F800000.view.effect.params[1] = g_Task->unk_09 * 16;
    D_1F800014[1].vz                 = -FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    for (ring = 1; ring < 9; ring++) {
        D_1F800000.view.effect.params[2] = D_1F800000.view.effect.params[1];
        D_1F800000.view.effect.params[1] = D_1F800000.view.effect.params[2] - 0x40;
        D_1F800014[3].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[2]);
        D_1F800014[3].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[2]);
        D_1F800014[2].vz                 = D_1F800014[1].vz;
        D_1F800014[3].vz                 = D_1F800014[1].vz;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
        D_1F800014[0].vz                 = -FIXED_MUL(rsin(ring << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = D_1F800014[0].vz;
        for (i = 1; i < 33; i++) {
            angle = i;
            angle &= 0x1F;
            D_1F800000.view.effect.params[3] = angle << 7;
            D_1F800014[0].vx                 = D_1F800014[1].vx;
            D_1F800014[0].vy                 = D_1F800014[1].vy;
            D_1F800014[1].vx                 = FIXED_MUL(rsin(angle << 7), D_1F800000.view.effect.params[1]);
            D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[1]);
            D_1F800014[2].vx                 = D_1F800014[3].vx;
            D_1F800014[2].vy                 = D_1F800014[3].vy;
            D_1F800014[3].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[2]);
            D_1F800014[3].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[2]);
            x                                = (D_1F800014[3].vx << 9) + g_Task->pos.x.fixed;
            y                                = (D_1F800014[3].vy << 9) + g_Task->pos.y.fixed;
            tpage                            = GetGraphType() == 1 || GetGraphType() == 2 ? 0x2A5 : 0xB5;
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 1, sizeof(DR_MODE));
            poly = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(poly);
            SetSemiTrans(poly, 1);
            poly->tpage = GetTPage(1, 1, 0x340, 0x100);
            poly->clut  = GetClut(0, 0x1FA);
            poly->u0    = ((i & 1) + (ring - 1) / 4 * 2) << 6;
            poly->v0    = D_801EF780[ring - 1];
            poly->u1    = (((i & 1) + (ring - 1) / 4 * 2) << 6) + 0x3F;
            poly->v1    = D_801EF780[ring - 1];
            poly->u2    = ((i & 1) + (ring - 1) / 4 * 2) << 6;
            poly->v2    = D_801EF788[ring - 1] - 1 + D_801EF780[ring - 1];
            poly->u3    = (((i & 1) + (ring - 1) / 4 * 2) << 6) + 0x3F;
            poly->v3    = D_801EF788[ring - 1] - 1 + D_801EF780[ring - 1];
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3, &depth, &flag);
            poly->r0 = D_1F800000.view.effect.params[4];
            poly->g0 = D_1F800000.view.effect.params[5];
            poly->b0 = D_1F800000.view.effect.params[6];
            Area_AddCellPrim(x, y, 1, sizeof(POLY_FT4));
        }
    }
}

INCLUDE_ASM(func_801EF70C);
