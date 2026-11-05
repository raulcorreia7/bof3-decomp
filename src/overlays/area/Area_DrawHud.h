/* Queues the area screen overlay at (x, y): one sprite per pad mask hit through AREA_HUD_MASK_TABLE, then the
 * gradient diamond. One definition shared by the area overlays; every change here must verify every member. */
MATCH void Area_DrawHud(s16 x, s16 y) {
    s32 i;
    s32 type;
    s32 tpage;

    if ((g_AreaDrawFlags & (AREA_DRAW_SORTED_RECORDS | AREA_DRAW_NEGATIVE_DEPTH | AREA_DRAW_APPEND_ACTOR_PRIMITIVES |
                            AREA_DRAW_APPEND_AREA_PRIMITIVES)) == 0) {
        return;
    }

    tpage = getTPage(1, 0, 768, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(1, 0xC);
    Area_DrawHudSprite((s16)x, (s16)y, 0);

    type = Area_GetCellCode(D_8014930A, D_8014930E);
    if ((u8)(type + 0x60) >= 2 && (u8)type != 0xAE && (g_AreaWalkFlags & AREA_WALK_TRANSITION) == 0) {
        Area_DrawHudSprite((s16)(x + 0x30), (s16)y, 1);
        for (i = 0; i < 6; i++) {
            if (g_InputMasks & AREA_HUD_MASK_TABLE[i].mask) {
                Area_DrawHudSprite((s16)(x + 0x38), (s16)(y + 8), (u8)(AREA_HUD_MASK_TABLE[i].step + 1));
                break;
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (g_InputMasks & AREA_HUD_MASK_TABLE[i].mask) {
                Area_DrawHudSprite((s16)(x + 0x38), (s16)(y + 8), AREA_HUD_MASK_TABLE[i].step);
                break;
            }
        }
    }

    if ((u8)(type + 0x60) >= 2) {
        Area_DrawHudSprite((s16)(x + 0x30), (s16)(y + 0x10), 2);
        for (i = 0; i < 8; i++) {
            if (D_80145AC0 & AREA_HUD_MASK_TABLE[i].mask) {
                Area_DrawHudSprite((s16)(x + 0x38), (s16)(y + 0x10), (u8)(AREA_HUD_MASK_TABLE[i].step + 1));
                break;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            if (D_80145AC0 & AREA_HUD_MASK_TABLE[i].mask) {
                Area_DrawHudSprite((s16)(x + 0x38), (s16)(y + 0x10), AREA_HUD_MASK_TABLE[i].step);
                break;
            }
        }
    }

    if ((func_801B6610(D_8014930A, D_8014930E) & BYTE_MASK) || (g_AreaWalkFlags & AREA_WALK_TRANSITION) ||
        (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) == 0xC || (g_GameFlags & 0x4000)) {
        Area_DrawHudSprite((s16)(x + 0x30), (s16)(y + 0x18), 3);
    }
    Area_DrawGradientDiamond(x + 0x18, y + 0x18);
}
