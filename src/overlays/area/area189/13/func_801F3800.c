#include "area189_13.h"
#include "menu/save_data.h"

#ifdef NON_MATCHING
/* Draws the area 189 backdrop: the title strip, the palette column of cells, the rain sheet when the
 * scratch fade is lit, the marker quads, and the palette tint that follows the target cell. */
NON_MATCHING void func_801F3800(void) {
    RECT*     window;
    POLY_FT4* prim;
    TILE*     tile;
    POLY_G4*  quad;
    u16*      left;
    u16*      right;
    s32       shade;
    s32       scale;
    s32       dx;
    s32       dy;
    s32       phase;
    s32       i;
    s32       j;

    window          = GFX_CURSOR(RECT);
    g_GfxPrimCursor = (u8*)(window + 1);
    /* Open-coded: setRECT stores w before h, retail stores h first. */
    window->x       = 32;
    window->y       = 0;
    window->h       = 32;
    window->w       = 32;
    SetDrawMode(GFX_CURSOR(DR_MODE), 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), window);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));

    prim = GFX_CURSOR(POLY_FT4);
    SetPolyFT4(prim);
    SetShadeTex(prim, 1);
    setXYWH(prim, 0, 0x5A, 0x140, 0x20);
    setUVWH(prim, 0, 0, 0xFF, 0x40);
    prim->tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    prim->clut  = getClut(0, 0x1E4);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_FT4));

    window          = GFX_CURSOR(RECT);
    g_GfxPrimCursor = (u8*)(window + 1);
    /* Open-coded for the same h-before-w order. */
    window->x       = 0;
    window->y       = 0;
    window->h       = 256;
    window->w       = 256;
    SetDrawMode(GFX_CURSOR(DR_MODE), 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), window);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));

    SetDrawMode(GFX_CURSOR(DR_MODE), 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_SUB, 320, 256), 0);
    func_801F497C(sizeof(DR_MODE));

    tile = GFX_CURSOR(TILE);
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, 0, 0x32);
    tile->w = 0x140;
    tile->h = 0x28;
    setRGB0(tile, 0xFF, 0xFF, 0xFF);
    func_801F497C(sizeof(TILE));

    if (g_SaveData.desert.clock < 0x1B0) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[0].vy = g_ScratchPadVectors[0].vz = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[1].vz = 0x80;
    } else if (g_SaveData.desert.clock < 0x1E0) {
        phase                     = (g_SaveData.desert.clock - 0x1B0) / 3;
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[0].vy = g_ScratchPadVectors[0].vz = phase * 8;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[1].vz = 0x80 - phase * 8;
        Area_PaletteApplyTint(0, 6, phase * 4 / 10 - 6, phase / 8 - 2, 0);
    } else if (g_SaveData.desert.clock < 0x390) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[0].vy = g_ScratchPadVectors[0].vz = 0x80;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[1].vz = 0;
    } else {
        phase = (g_SaveData.desert.clock - 0x390) / 3;
        shade = phase - 6;
        if (shade < 0) {
            shade = 0;
        }
        g_ScratchPadVectors[0].vx = 0x80 - shade * 12;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[0].vz = 0x80 - phase * 8;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[1].vz = phase * 8;
        Area_PaletteApplyTint(0, 6, D_801F6254[phase * 3], D_801F6255[phase * 3], D_801F6256[phase * 3]);
    }

    for (j = 0; j < 2; j++) {
        for (i = 0; i < 3; i++) {
            prim = GFX_CURSOR(POLY_FT4);
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            SetSemiTrans(prim, 1);
            setXYWH(prim, (((g_AreaCameraAngle.vz * 5) >> 4) & 0xFF) + (i - 1) * 0x100, 0, 0x100, 0x5A);
            setRGB0(prim, g_ScratchPadVectors[j].vx, g_ScratchPadVectors[j].vy, g_ScratchPadVectors[j].vz);
            prim->tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 448, 256);
            prim->clut  = getClut(0, j + 0x1E6);
            setUVWH(prim, 0, j * 0x60, 0xFF, 0x5A);
            func_801F497C(sizeof(POLY_FT4));
        }
    }

    scale = g_ScratchPadVectors[1].vx;
    if (scale != 0) {
        func_801F43E8(scale);
    }

    for (j = 0; j < 2; j++) {
        left  = D_801F6240;
        right = D_801F6242;
        SetDrawMode(GFX_CURSOR(DR_MODE), 0, 1, getTPage(TPAGE_DEPTH_8BIT, j + 1, 320, 256), 0);
        func_801F497C(sizeof(DR_MODE));
        for (i = 0; i < 4; i++) {
            quad = GFX_CURSOR(POLY_G4);
            SetPolyG4(quad);
            SetSemiTrans(quad, 1);
            setXY4(quad, left[0], 0x5A, right[0], 0x5A, left[0], D_801F624C[i], right[0], D_801F624D[i]);
            setRGB0(quad, g_ScratchPadVectors[j].vx, g_ScratchPadVectors[j].vy, g_ScratchPadVectors[j].vz);
            setRGB1(quad, g_ScratchPadVectors[j].vx, g_ScratchPadVectors[j].vy, g_ScratchPadVectors[j].vz);
            setRGB2(quad, 0, 0, 0);
            setRGB3(quad, 0, 0, 0);
            left++;
            right++;
            func_801F497C(sizeof(POLY_G4));
        }
    }

    dx = g_AreaTargetCellX - 0x1780;
    if (dx < 0) {
        dx = -dx;
    }
    dy = g_AreaTargetCellY - 0x1380;
    if (dy < 0) {
        dy = -dy;
    }
    shade = 0xC0 - (dx + dy) / 3;
    shade = shade > 0x80 ? 0x80 : shade;
    shade = shade < 0 ? 0 : shade;
    if (shade != 0) {
        func_801F4150(shade, ((((g_AreaCameraAngle.vz + 0x800) & 0xFFF) - 0x400) * 5 >> 4) - 0x28);
    }

    if (SYS_TestFlag(&g_SceneFlagWords[14 * 8], 4) != 0) {
        dx = g_AreaTargetCellX - 0x1780;
        if (dx < 0) {
            dx = -dx;
        }
        dy = g_AreaTargetCellY - 0xE00;
        if (dy < 0) {
            dy = -dy;
        }
        shade = 0x100 - (dx + dy) / 4;
        shade = shade > 0x80 ? 0x80 : shade;
        shade = shade < 0 ? 0 : shade;
        if (shade != 0) {
            func_801F4150(shade, ((((g_AreaCameraAngle.vz + ratan2(g_AreaTargetCellX - 0x1780, -g_AreaTargetCellY) - 0x400) & 0xFFF) - 0x200) * 10 >> 5) - 0x28);
        }
    }
}
#else
INCLUDE_ASM(func_801F3800);
#endif
