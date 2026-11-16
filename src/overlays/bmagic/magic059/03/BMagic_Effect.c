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

/* Moves the effect one step around a circle. */
MATCH void func_801EF118(void) {
    u8           angle;
    s16*         cell;
    PartyMember* work;

    work                = g_Task;
    cell                = (s16*)&D_1F80000E;
    angle               = work->unk_09 + 1;
    work->unk_09        = angle;
    *cell               = angle << 4;
    g_Task->pos.x.fixed = g_Task->unk_18 + (rsin((s16)(angle << 4)) << 6);
    g_Task->pos.y.fixed = g_Task->unk_1C + (rcos(*cell) << 6);
    if (g_Task->param.unk_0B == 0) {
        func_800A9820(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF1E0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF224(void) {
    SYS_DISPATCH_BYTE(D_801F0670, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF638();
        func_801EF70C(-g_Task->unk_09 & 0x3F, 0x20);
        func_801EF70C((8 - g_Task->unk_09) & 0x3F, 0x20);
        func_801EF70C((16 - g_Task->unk_09) & 0x3F, 0x20);
        func_801EF70C((24 - g_Task->unk_09) & 0x3F, 0x20);
        func_801EF70C((32 - g_Task->unk_09) & 0x3F, 0x20);
        func_801EF70C((40 - g_Task->unk_09) & 0x3F, 0x20);
        func_801EF70C((48 - g_Task->unk_09) & 0x3F, 0x20);
        func_801EF70C((56 - g_Task->unk_09) & 0x3F, 0x20);
        func_801EF70C((4 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((12 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((20 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((28 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((36 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((44 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((52 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        func_801EF70C((60 - g_Task->unk_09 * 2) & 0x3E, 0x50);
        PopMatrix();
    }
}

MATCH void func_801EF4C4(void) {
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.step += 1;
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
    src = (PartyMember*)g_BattleEffectBattler;
    setVector(&rot, 0, 0, 0);
    g_Task->pos.x.fixed      = src->pos.x.fixed;
    g_Task->pos.y.fixed      = src->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(src->pos.z);
    setVector(&pos, (g_Task->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (g_Task->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -COORD_INT(g_Task->pos.z) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

INCLUDE_ASM(func_801EF70C);

MATCH void func_801EFE48(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 5, 1, g_Task);
}

MATCH void func_801EFE8C(void) {
    s16* angle;

    SYS_DISPATCH_BYTE(D_801F0684, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        angle                        = &g_ScratchPad.cells.halves[7];
        *angle                       = ((g_Task->unk_09 * 3) & 0x3F) << 6;
        g_ScratchPad.cells.halves[0] = g_Task->unk_0C + ((rsin((g_FrameCount & 0xF) << 6) * 16) >> 12);
        g_Task->pos.x.fixed          = g_BattleEffectBattler->pos.x.fixed + ((rcos(*angle) * g_ScratchPad.cells.halves[0]) >> 3);
        g_Task->pos.y.fixed          = g_BattleEffectBattler->pos.y.fixed + ((rsin(*angle) * g_ScratchPad.cells.halves[0]) >> 3);
        g_Task->pos.y.fixed += (rcos((g_FrameCount & 0x3F) << 6) * 128) >> 3;
        Battle_ProjectRange();
        func_801F01A4();
    }
}

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

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    g_ScratchPad.cells.halves[0] = 32;
    setXY4(prim, g_Task->unk_2E.half + FIXED_MUL(rcos(3328), g_ScratchPad.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(3328), g_ScratchPad.cells.halves[0]),
           g_Task->unk_2E.half + FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]),
           g_Task->unk_2E.half + FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]),
           g_Task->unk_2E.half + FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 0, 0, 31, 32);
    g_ScratchPad.cells.halves[6] = g_Task->timer * g_Task->param.unk_0B;
    setRGB0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[6]);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F0490 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F04F4 */
#include "overlays/bmagic/Actor_Clear.h"

/* Sets the effect height to the mean z of the unblocked battlers on the side opposite the active battler. */
MATCH void func_801F0544(void) {
    s32 count;
    s32 sum;
    s32 i;

    count = 0;
    sum   = 0;
    if (g_Battle.active_battler < 3) {
        for (i = 0; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + 3))) {
                sum += g_BattleEnemyBattlers[i].pos.z.part.integer;
                count++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!Battle_SlotIsBlocked((u8)i)) {
                sum += g_Game.members[i].pos.z.part.integer;
                count++;
            }
        }
    }
    g_Task->pos.z.part.integer = sum / count;
}
