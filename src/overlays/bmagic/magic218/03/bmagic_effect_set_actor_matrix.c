#include "magic218_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEEE4(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--SELF(PartyMember)->unk_09 == 0) {
        src                       = BATTLE_ACTIVE_WORK;
        dst                       = SELF(PartyMember);
        dst->pos.x.fixed          = src->pos.x.fixed;
        dst->pos.y.fixed          = src->pos.y.fixed;
        dst->pos.z                = src->pos.z;
        dst->unk_5D               = 0x10;
        SELF(PartyMember)->unk_09 = 0x10;
        SELF(PartyMember)->timer  = 4;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EEF84(void) {
    s32 i;
    u8  slot;

    SELF(PartyMember)->unk_09 += 2;
    SP_REF(s16, 0) = SELF(PartyMember)->unk_09 << 4;
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
        if (SELF(PartyMember)->timer < 32) {
            SELF(PartyMember)->timer += 1;
        }
    }
    if (SELF(PartyMember)->unk_09 == 96) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF0F0(void) {
    u8 count;
    u8 timer;

    if (g_FrameCount & 0x1) {
        timer = SELF(PartyMember)->timer;
        if (timer < 32U) {
            SELF(PartyMember)->timer = timer + 1;
        }
    }
    SELF(PartyMember)->unk_09 += 1;
    count                     = SELF(PartyMember)->unk_5D - 1;
    SELF(PartyMember)->unk_5D = count;
    if ((count << 24) == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

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

    g_ScratchPad.cells.halves[4] = (s8)SELF(PartyMember)->unk_5D * 8;
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5D * 8;
    g_ScratchPad.cells.halves[6] = (s8)SELF(PartyMember)->unk_5D * 8;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer * 16;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_09 * 16;
    g_ScratchPadVectors[1].vz    = -FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    for (ring = 1; ring < 9; ring++) {
        g_ScratchPad.cells.halves[2] = g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[1] = g_ScratchPad.cells.halves[2] - 0x40;
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[2].vz    = g_ScratchPadVectors[1].vz;
        g_ScratchPadVectors[3].vz    = g_ScratchPadVectors[1].vz;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vz    = -FIXED_MUL(rsin(ring << 8), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = g_ScratchPadVectors[0].vz;
        for (i = 1; i < 33; i++) {
            angle = i;
            angle &= 0x1F;
            g_ScratchPad.cells.halves[3] = angle << 7;
            g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[2]);
            g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[2]);
            x                            = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.x.fixed;
            y                            = (g_ScratchPadVectors[3].vy << 9) + SELF(PartyMember)->pos.y.fixed;
            tpage                        = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 1, sizeof(DR_MODE));
            poly = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(poly);
            SetSemiTrans(poly, 1);
            poly->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 0x340, 0x100);
            poly->clut  = GetClut(0, 0x1FA);
            setUV4(poly, ((i & 1) + (ring - 1) / 4 * 2) << 6, D_801EF780[ring - 1], (((i & 1) + (ring - 1) / 4 * 2) << 6) + 0x3F, D_801EF780[ring - 1], ((i & 1) + (ring - 1) / 4 * 2) << 6,
                   D_801EF788[ring - 1] - 1 + D_801EF780[ring - 1], (((i & 1) + (ring - 1) / 4 * 2) << 6) + 0x3F, D_801EF788[ring - 1] - 1 + D_801EF780[ring - 1]);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                          &depth, &flag);
            setRGB0(poly, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
            Area_CellAddPrim(x, y, 1, sizeof(POLY_FT4));
        }
    }
}

MATCH bool func_801EF70C(EnemyBattler* enemy) {
    s32 dx;
    s32 dy;
    s32 horizontal;
    s32 radius;
    s32 record_y;

    dx         = (enemy->pos.x.fixed >> 9) - (SELF(PartyMember)->pos.x.fixed >> 9);
    record_y   = SELF(PartyMember)->pos.y.fixed >> 9;
    dy         = (enemy->pos.y.fixed >> 9) - record_y;
    horizontal = dx * dx + dy * dy;
    radius     = g_ScratchPad.cells.halves[0];
    record_y   = radius * radius;
    return horizontal <= record_y;
}
