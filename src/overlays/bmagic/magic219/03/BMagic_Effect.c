#include "magic219_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic219Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EFA14[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EFA14[i];
            g_BattleEffectBattler = D_801EFA14[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

/* Clears the effect slots, centers the camera and reloads palette rows 2 and 26 of the work copy with the STP bit
 * set. */
MATCH void func_801EED28(void) {
    u16* dst;
    u16* src;
    u16* row_dst;
    u16* row_src;
    u16  i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    i       = 0;
    row_dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    dst     = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src     = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        row_dst[i] = row_src[i] | 0x8000;
        dst[i]     = src[i] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    g_GfxPalettePending                                      = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EEE50(void) {
    u8 i;
    u8 slot;

    for (i = 0; i < 24; i++) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            volatile void* task           = g_Task;
            D_801EFA14[slot].header.mode  = 0;
            D_801EFA14[slot].unk_0B       = i;
            D_801EFA14[slot].target.party = (PartyMember*)task;
            D_801EFA14[slot].arg.unk_09   = D_801EF9E8[i] + (RANDOM_MASK(0x1)) + 1;
            g_Task->param.unk_0B++;
        }
    }
    g_Task->unk_09 = 8;
    g_Task->header.mode++;
}

MATCH void func_801EEF54(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        SND_QueueSelectionEffect(0x101);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF024 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF068(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EFA04, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
        Effect_SetActiveActorMatrix();
        func_801EF71C();
        PopMatrix();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF118(void) {
    PartyMember* cell;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        cell           = D_8014637C;
        g_Task->facing = cell->facing;
        g_Task->unk_0C = 0x20000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed  = cell->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed  = cell->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed  = cell->pos.z.fixed + 0x800000;
        MAGIC219_RING_RADIUS = (g_Task->param.unk_0B >> 3) * 16 + 32;
        MAGIC219_ORBIT_ANGLE = (((g_Task->param.unk_0B & 7) * 2 + (g_Task->param.unk_0B >> 3)) & 0xF) << 8;
        g_Task->unk_0C       = g_BattleEffectBattler->pos.x.fixed + rsin(MAGIC219_ORBIT_ANGLE) * MAGIC219_RING_RADIUS;
        g_Task->unk_10       = g_BattleEffectBattler->pos.y.fixed + rcos(MAGIC219_ORBIT_ANGLE) * MAGIC219_RING_RADIUS;
        g_Task->unk_14       = g_BattleEffectBattler->pos.z.fixed;
        g_Task->unk_25       = 29;
        g_Task->unk_26       = 0xC0;
        g_Task->scale.x      = 0x10000;
        g_Task->scale.y      = 0x10000;
        g_Task->unk_48       = 0;
        g_Task->unk_27       = 2;
        g_Task->unk_28       = 1;
        g_Task->unk_24       = 0;
        g_Task->unk_5C       = 0;
        g_Task->unk_5D       = 0;
        g_Task->unk_5E       = 0;
        g_Task->unk_5F       = 0;
        g_Task->unk_2A       = 0;
        g_Task->unk_29       = 4;
        g_Task->unk_2C.half  = 0;
        g_Task->unk_2B       = 0;
        Actor_SelectScript(0);
        g_Task->unk_18 = ratan2(g_Task->unk_0C - g_Task->pos.x.fixed, g_Task->unk_10 - g_Task->pos.y.fixed);
        g_Task->unk_09 = 3;
        g_Task->timer  = 4;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF3CC);

MATCH void func_801EF530(void) {
    PartyMember* work = g_Task;

    work->unk_25      = 0x1D;
    work->pos.x.fixed = work->unk_0C;
    work->pos.y.fixed = work->unk_10;
    work->pos.z.fixed = work->unk_14;
    g_Task->unk_26    = 0;
    g_Task->unk_27    = 0x1A;
    g_Task->unk_2B    = 1;
    Actor_SelectScript(1);
    g_Task->unk_09 = 0xE;
    g_Task->timer  = 12;
    g_Task->header.step += 1;
}

MATCH void func_801EF5DC(void) {
    u8 timer_next;
    u8 count;

    Actor_StepAnimOnce();
    timer_next = g_Task->timer;
    if (timer_next != 0) {
        g_Task->timer = timer_next - 1;
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

MATCH void func_801EF71C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 2, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    MAGIC219_RING_RADIUS = g_Task->timer << 4;
    setVector(&D_1F800014[2], FIXED_MUL(rsin(0), MAGIC219_RING_RADIUS), FIXED_MUL(rcos(0), MAGIC219_RING_RADIUS), 0);
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), MAGIC219_RING_RADIUS);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), MAGIC219_RING_RADIUS);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 0x60, 0x60, 0x60);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
}

/* func_801EF934 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF998 */
#include "overlays/bmagic/Actor_Clear.h"
