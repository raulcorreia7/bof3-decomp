#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6FE0(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    FAKE_ORDER_LOCK(D_801FC418[index]());
}

MATCH void func_801F7014(void) {
    D_80146872 = 1;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F7028(void) {
}
#else
INCLUDE_ASM(func_801F7028);
#endif

/* Averages each working palette colour's red, green and blue channels into a
 * grey level and keeps the mask bit, then marks the palette for upload. */
MATCH void func_801F7960(void) {
    u16* cell;
    u32  row;
    u32  col;
    u32  row_base;
    u32  color;
    u32  red;
    u32  rgb;
    u32  average;
    u32  packed;

    row = 0;
    do {
        col      = 0;
        row_base = AREA_PALETTE_WORK + (row & 0xFF) * AREA_PALETTE_ROW;
        do {
            cell    = MEM_PTR(u16, (col & 0xFFFF) * 2 + row_base);
            color   = *cell;
            red     = color & 0x1F;
            rgb     = color & 0xFFFF;
            average = (red + ((rgb >> 5) & 0x1F) + ((rgb >> 10) & 0x1F)) / 3;
            packed  = color & 0x8000;
            packed |= average << 10;
            packed |= average << 5;
            *cell = average | packed;
            col++;
        } while ((col & 0xFFFF) < AREA_PALETTE_COLORS);
        row++;
    } while ((row & 0xFF) < AREA_PALETTE_ROWS);
    g_GfxPalettePending = 1;
}

#include "overlays/scenario/shared/Scene_SpawnActor.h"

MATCH bool Scene_SpawnActor(u8 type, s16 angle_x, s16 angle_y, s16 angle_z, u8 layer, s32 scene_step){SCENE_SPAWN_ACTOR(D_801FC4C0)}

MATCH void func_801F7B5C(void) {
    SYS_DISPATCH_BYTE(D_801FC424, g_ScenarioState.state_04);
}

MATCH void func_801F7B98(void) {
}
