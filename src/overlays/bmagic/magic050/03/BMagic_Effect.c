#include "magic050_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC10 */
#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    u32          slot;
    u8           i;

    SELF(PartyMember)->param.unk_0B = 0;
    Battle_CenterCamera();
    SELF(PartyMember)->facing       = g_BattleEffectBattler->facing;
    SELF(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 4) & BYTE_MASK;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].arg.unk_09   = D_801EFA90[i] + 1;
        g_BattleEffects[slot].unk_08       = SELF(PartyMember)->facing;
        g_BattleEffects[slot].pos.x.fixed  = SELF(PartyMember)->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = SELF(PartyMember)->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = SELF(PartyMember)->pos.z.fixed;
        SELF(PartyMember)->param.unk_0B += 1;
        i++;
    } while (i < 10);
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEDF8(void) {
    s32 cue;
    s32 timer;
    u8  timer_next;

    timer = SELF(PartyMember)->unk_09;
    if (timer != 16) {
        if (timer < 17) {
            cue = 0x101;
            if (timer != 8) {
            } else {
                goto block_7;
            }
        } else {
            cue = 0x101;
            if (timer != 24) {
            } else {
                goto block_7;
            }
        }
    } else {
        cue = 0x102;
    block_7:
        SND_SEQueueSelection(cue);
    }
    timer_next                = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = timer_next;
    if ((timer_next & BYTE_MASK) == 25) {
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEF08 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF4C(void) {
    SYS_DISPATCH_BYTE(D_801EFAF0, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.step != 0 && SELF(PartyMember)->header.flags != 0) {
        Battle_ProjectRange();
        func_801EF1B0();
        func_801EF4C4();
        func_801EF898();
    }
}

MATCH void func_801EEFDC(void) {
    PartyMember* work;
    PartyMember* next;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        next         = SELF(PartyMember);
        next->unk_0C = D_801EFAA0[next->param.unk_0B].x;
        next->unk_10 = D_801EFAA0[next->param.unk_0B].y;
        Effect_RotatePosition(next);
        work              = SELF(PartyMember);
        work->pos.x.fixed = g_AreaScrollTargetX + work->unk_0C;
        work->pos.y.fixed = g_AreaScrollTargetY + work->unk_10;
        if (work->param.unk_0B == 0) {
            Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        }
        SELF(PartyMember)->unk_09 = 32;
        SELF(PartyMember)->timer  = 2;
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpTimerByTwoAndStep.h"

MATCH void func_801EF138(void) {
    PartyMember* work;
    u8           count;

    work = SELF(PartyMember);
    work->timer++;
    work         = SELF(PartyMember);
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Effect_Reset();
    }
}

/* Draws the ring of sixteen glowing triangles around the caster, sized by the timer. */
MATCH void func_801EF1B0(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.words[0] = SELF(PartyMember)->timer;
    if (g_Battle.action_id == 50) {
        g_ScratchPad.cells.words[2] = SELF(PartyMember)->unk_09 * 3;
        g_ScratchPad.cells.words[3] = SELF(PartyMember)->unk_09;
    } else {
        g_ScratchPad.cells.words[2] = SELF(PartyMember)->unk_09 * 5;
        g_ScratchPad.cells.words[3] = SELF(PartyMember)->unk_09;
    }
    for (i = 0; i < 16; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value, SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.words[0]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.words[0]), SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 8), g_ScratchPad.cells.words[0]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 8), g_ScratchPad.cells.words[0]));
        if (g_Battle.action_id == 50) {
            setRGB0(prim, g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
            setRGB1(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], 1);
            setRGB2(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], 1);
        } else {
            setRGB0(prim, g_ScratchPad.cells.words[3], 1, g_ScratchPad.cells.words[2]);
            setRGB1(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2]);
            setRGB2(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2]);
        }
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

/* Draws the ring of sixteen glowing quads around the caster, from the timer out to half again its size. */
MATCH void func_801EF4C4(void) {
    POLY_G4* prim;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.words[0] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.words[1] = SELF(PartyMember)->timer + SELF(PartyMember)->timer / 2;
    if (g_Battle.action_id == 50) {
        g_ScratchPad.cells.words[2] = SELF(PartyMember)->unk_09 * 4;
        g_ScratchPad.cells.words[3] = SELF(PartyMember)->unk_09;
    } else {
        g_ScratchPad.cells.words[2] = SELF(PartyMember)->unk_09 * 6;
        g_ScratchPad.cells.words[3] = SELF(PartyMember)->unk_09;
    }
    for (i = 0; i < 16; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY4(prim, SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.words[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.words[0]),
               SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 8), g_ScratchPad.cells.words[0]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 8), g_ScratchPad.cells.words[0]), SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.words[1]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.words[1]), SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 8), g_ScratchPad.cells.words[1]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 8), g_ScratchPad.cells.words[1]));
        if (g_Battle.action_id == 50) {
            setRGB0(prim, g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3]);
            setRGB1(prim, g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3]);
        } else {
            setRGB0(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2]);
            setRGB1(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2]);
        }
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EF898(void) {
    TILE_1* prim;
    s32     i;
    s32     tpage;

    g_ScratchPad.cells.words[0] = SELF(PartyMember)->timer * 3;
    g_ScratchPad.cells.words[2] = SELF(PartyMember)->unk_09 * 6;
    g_ScratchPad.cells.words[3] = SELF(PartyMember)->unk_09;
    for (i = 0; i < 16; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (TILE_1*)g_GfxPrimCursor;
        SetTile1(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.words[0]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.words[0]));
        if (g_Battle.action_id == 50) {
            setRGB0(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3]);
        } else {
            setRGB0(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[2]);
        }
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(TILE_1));
    }
}
