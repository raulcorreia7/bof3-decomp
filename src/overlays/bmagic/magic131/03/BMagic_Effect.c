#include "magic131_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC24);

INCLUDE_ASM(func_801EEDEC);

INCLUDE_ASM(func_801EEF64);

INCLUDE_ASM(func_801EF000);

INCLUDE_ASM(func_801EF110);

INCLUDE_ASM(func_801EF1C0);

MATCH void func_801EF3D0(void) {
    if (!EMI_IsReady()) {
        return;
    }
    if (g_Battle.scroll_dir & 0x2) {
        EMI_LoadArchive(D_800B499C[g_Battle.dragon_form][1][g_EmiLoadedCharacterIndex]);
    } else {
        EMI_LoadArchive(D_800B499C[g_Battle.dragon_form][0][g_EmiLoadedCharacterIndex]);
    }
    g_Task->header.mode += 1;
}

MATCH void func_801EF488(void) {
    PartyMember* prev;
    PartyMember* battler;
    s32          i;
    s32          slot;

    if (EMI_IsReady() != 0) {
        i = 0;
        if (g_Game.party_size != 0) {
            do {
                slot                              = i & BYTE_MASK;
                g_Game.members[slot].header.flags = 1;
                prev                              = g_Task;
                battler                           = &g_Game.members[slot];
                g_Task                            = battler;
                Actor_SelectScript((battler->facing + 4) & BYTE_MASK);
                if (g_Game.members[slot].chr.status & 0x2080) {
                    Actor_SelectScript((g_Task->facing + 0x18) & BYTE_MASK);
                }
                if (g_Game.members[slot].chr.status & 0x800) {
                    Actor_SelectScript((g_Task->facing + 0x30) & BYTE_MASK);
                }
                if (func_801DB524(slot) & BYTE_MASK) {
                    Actor_SelectScript((g_Task->facing + 0x1C) & BYTE_MASK);
                }
                i++;
                g_Task = prev;
            } while ((u32)(i & BYTE_MASK) < g_PartySize);
        }
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF668 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

INCLUDE_ASM(func_801EF6AC);

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EFA68);

MATCH void func_801EFB64(void) {
    PartyMember* work  = g_Task;
    u8           timer = work->unk_09 - 1;
    work->unk_0C += work->unk_18;
    work->unk_09 = timer;
    work->unk_10 += work->unk_1C;
    work->unk_2E.half += work->unk_0C;
    work->unk_30.half += work->unk_10;
    if (timer == 0) {
        g_Task->unk_09 = 0x24;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFBF8(void) {
    u8 count;

    Actor_StepAnimLoop();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Actor_SelectScript(1U);
        g_Task->unk_09 = 0x29;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EFC74);

MATCH void func_801EFEF0(void) {
    if (Actor_StepAnimOnce() != 0u) {
        g_Task->unk_09      = 0xF;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EFF48(void) {
    u32 direction;
    u8  timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        direction = LOBU(g_Battle.scroll_dir);
        if (direction == 0 || direction == 3) {
            g_Task->unk_0C = 8;
            g_Task->unk_10 = -1;
            g_Task->unk_18 = 1;
            g_Task->unk_1C = -1;
        } else {
            g_Task->unk_0C = -8;
            g_Task->unk_10 = -1;
            g_Task->unk_18 = -1;
            g_Task->unk_1C = -1;
        }
        g_Task->unk_09 = 0;
        g_Task->timer  = 30;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0034(void) {
    u8           timer;
    u8           count;
    PartyMember* work;

    if (g_FrameCount & 0x1) {
        count = g_Task->unk_09;
        if (count < 8U) {
            g_Task->unk_09 = count + 1;
            g_Task->unk_10 += g_Task->unk_1C;
        }
    }
    work        = g_Task;
    timer       = work->timer - 1;
    work->timer = timer;
    work->unk_2E.half += work->unk_0C;
    work->unk_30.half += work->unk_10;
    if (!(timer & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801F0100(void) {
    SYS_DISPATCH_BYTE(D_801F1BF4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F030C();
    }
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801F01F8(void) {
    if ((BATTLE_ACTIVE_WORK->unk_09 == 0) && (EMI_IsReady() != 0)) {
        g_Task->timer = 8;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801F030C(void) {
    POLY_F4* prim;
    s32      shade;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0, 0x13F, 0, 0, 0xEF, 0x13F, 0xEF);
    shade = g_Task->unk_09 * 15;
    setRGB0(prim, shade, shade, shade);
    GFX_AddPrim(2, sizeof(POLY_F4));
    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}

MATCH void func_801F0438(void) {
    SYS_DISPATCH_BYTE(D_801F1C08, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F06B4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F04C0);

MATCH void func_801F053C(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x40);
}

MATCH void func_801F058C(void) {
    PartyMember* work;
    PartyMember* active;
    s8           count;

    work = g_Task;
    work->unk_09 += 2;
    work         = g_Task;
    count        = work->unk_5D - 4;
    work->unk_5D = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F06B4);

MATCH void func_801F0B44(void) {
    SYS_DISPATCH_BYTE(D_801F1C24, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F0D44();
        func_801F0DF4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F0BCC);

MATCH void func_801F0C4C(void) {
    s32 value;

    value          = g_Task->unk_14 + 0x20;
    g_Task->unk_14 = value;
    if (value == 0x200) {
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void Effect_CountDownAndStep2(void) {
    BMAGIC_COUNT_DOWN_AND_STEP();
}

MATCH void func_801F0CE4(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->unk_14 += 0x10;

    timer        = work->unk_09 - 2;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

INCLUDE_ASM(func_801F0DF4);

MATCH void func_801F10F4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 27), 1, D_801F24E0);
}

MATCH void func_801F1138(void) {
    SYS_DISPATCH_BYTE(D_801F1C48, D_801F24E0->header.step);
    if (D_801F24E0->header.flags != 0 && D_801F24E0->header.step != 0) {
        func_801F1B14();
        func_801F1844();
    }
}

INCLUDE_ASM(func_801F11B8);

INCLUDE_ASM(func_801F12A0);

MATCH void func_801F13A4(void) {
    s16* angle_cell;
    u8   phase;
    u8   timer;

    D_801F24E0->phase_0C += 0x10;
    phase                   = D_801F1C38[D_801F24E0->unk_07];
    angle_cell              = &D_1F800006;
    *angle_cell             = phase << 7;
    D_801F24E0->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << 7) * (s16)D_801F24E0->phase_0C) >> 3);
    D_801F24E0->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) * (s16)D_801F24E0->phase_0C) >> 3);
    timer                   = D_801F24E0->timer_05 - 2;
    D_801F24E0->timer_05    = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801F1AC4();
    }
}

MATCH void func_801F14A0(void) {
    s16 timer;

    SYS_DISPATCH_BYTE(D_801F1C94, D_801F24E0->header.step);
    timer = D_801F24E0->unk_26;
    if (timer != 0) {
        D_801F24E0->unk_26 = timer - 1;
        return;
    }
    if (D_801F24E0->header.flags != 0 && D_801F24E0->header.step != 0) {
        func_801F1B14();
        func_801F1844();
    }
}

MATCH void func_801F153C(void) {
    s16* angle_cell;
    u8   phase;

    phase                   = D_801F1C54[D_801F24E0->unk_07];
    angle_cell              = &D_1F800006;
    *angle_cell             = phase << 6;
    D_801F24E0->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << 6) << 6) >> 3);
    D_801F24E0->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) << 6) >> 3);
    D_801F24E0->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    COORD_INT(D_801F24E0->pos.z) += D_801F1C74[D_801F24E0->unk_07] << 6;
    D_801F24E0->phase_0C = 0x40;
    D_801F24E0->timer_05 = 16;
    D_801F24E0->unk_06   = 8;
    D_801F24E0->header.step += 1;
}

MATCH void func_801F1644(void) {
    s16* angle_cell;
    u8   phase;

    D_801F24E0->unk_06 += 2;
    D_801F24E0->phase_0C += 0x20;
    phase                   = D_801F1C54[D_801F24E0->unk_07];
    angle_cell              = &D_1F800006;
    *angle_cell             = phase << 6;
    D_801F24E0->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << 6) * (s16)D_801F24E0->phase_0C) >> 3);
    D_801F24E0->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) * (s16)D_801F24E0->phase_0C) >> 3);
    if ((s16)D_801F24E0->phase_0C == 0x200) {
        D_801F24E0->header.step += 1;
    }
}

INCLUDE_ASM(func_801F1748);

INCLUDE_ASM(func_801F1844);

MATCH u8 func_801F1A58(void) {
    u8 i;

    for (i = 0; i < 48; i++) {
        if (!(D_801F1CA0[i].header.flags & 0x1)) {
            D_801F1CA0[i].header.flags |= 1;
            return i;
        }
    }
    return GAME_NONE;
}

MATCH void func_801F1AC4(void) {
    D_801F24E0->header.flags = 0;
    D_801F24E0->header.mode  = 0;
    D_801F24E0->header.step  = 0;
    D_801F24E0->unk_03       = 0;
    D_801F24E0->unk_04       = 0;
}

MATCH void func_801F1B14(void) {
    BMagicEffectWork* work;
    s16               vec[3];
    TILE_1*           primitive;

    work      = D_801F24E0;
    vec[0]    = (work->pos.x.fixed >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (work->pos.y.fixed >> 9) - 0x4000;
    vec[2]    = -(COORD_INT(work->pos.z) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    D_801F24E0->unk_20 = primitive->x0;
    D_801F24E0->unk_22 = primitive->y0;
}
