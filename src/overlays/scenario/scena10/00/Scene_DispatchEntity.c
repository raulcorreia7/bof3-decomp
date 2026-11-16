#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F6FAC(void) {
    Actor* work;

    Area_SelectSceneRecord(0x1EA);
    work                     = g_Task;
    work->unk_48             = 0;
    work->pos.z.part.integer = 0x64;
    g_Task->active_flags     = 0;
    g_Task->unk_2A           = 0;
    g_Task->timer            = 0;
    g_Task->unk_0A           = 0x1E;
    g_Task->draw_layer       = 1;
    Actor_SelectScript((u8)(g_Task->unk_06 - 0x4E));
    g_Task->header.mode = 1;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F7068(void) {
    u8  i;
    u8  count;
    u32 limit;
    u8  timer;
    u16 width;
    u16 height;

    i     = 0;
    count = 0;
    while (i < 3) {
        width = D_801FE7CC[i].width;
        timer = g_Task->timer;
        limit = timer << 4;
        if (limit < width) {
            width = limit;
        } else {
            count++;
        }
        height = D_801FE7CC[i].height;
        if (limit < height) {
            height = limit;
        } else {
            count++;
        }
        if ((g_Task->option_flags & (1 << i)) == 0) {
            UI_DrawBoxOutline(D_801FE7CC[i].x, D_801FE7CC[i].y, (u8)width, (u8)height);
        }
        i++;
    }
    g_Task->timer++;
    if (count == 6) {
        g_Task->header.mode = 2;
    }
}
#else
INCLUDE_ASM(func_801F7068);
#endif

MATCH void func_801F719C(void) {
    u8 i;

    i = 0;
    do {
        if (((g_Task->option_flags >> i) & 1) == 0) {
            UI_DrawPanelBox(D_801FE7CC[i].x, D_801FE7CC[i].y, (u8)D_801FE7CC[i].width, (u8)D_801FE7CC[i].height);
        }
        i++;
    } while (i < 3);
    if ((g_Task->option_flags & 1) == 0) {
        g_Task->screen_x = (u16)D_801FE7CC[0].x + D_801FE804[0];
        g_Task->screen_y = (u16)D_801FE7CC[0].y + D_801FE804[1];
        Actor_StepAnimLoop();
        Area_AddActor();
    }
    if (((g_Task->option_flags >> 1) & 1) == 0) {
        sprintf((char*)g_UiFormatBuffer, D_801F6C04, Item_GetRecord(0, g_Task->unk_06));
        UI_DrawText((s16)((u16)D_801FE7CC[1].x + 4), (s16)((u16)D_801FE7CC[1].y + 2), 0, 8, g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, D_801F6C08, (u16)Item_Count(0, g_Task->unk_06, 0));
        UI_DrawText((s16)((u16)D_801FE7CC[1].x + 0x48), (s16)((u16)D_801FE7CC[1].y + 2), 0, 2, g_UiFormatBuffer);
    }
    func_801F781C((u16)D_801FE7CC[2].x + 1, (u16)D_801FE7CC[2].y + 1, 0x80, 0x68);
    if (g_Task->unk_0A != 0) {
        g_Task->unk_0A--;
    } else if (g_InputHeld != 0) {
        g_Task->header.mode = 3;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F73EC(void) {
    u8  i;
    u16 height;
    u16 limit;
    u16 width;

    i = 0;
    do {
        width = D_801FE7CC[i].width;
        limit = (u16)(g_Task->timer << 4);
        if (limit < width) {
            width = limit;
        }
        height = D_801FE7CC[i].height;
        if (limit < height) {
            height = limit;
        }
        if (((g_Task->option_flags >> i) & 1) == 0) {
            UI_DrawBoxOutline(D_801FE7CC[i].x, D_801FE7CC[i].y, (u8)width, (u8)height);
        }
        i++;
    } while (i < 3);
    g_Task->timer--;
    if (g_Task->timer == 0) {
        g_Task->header.mode = 4;
    }
}
#else
INCLUDE_ASM(func_801F73EC);
#endif

MATCH void func_801F74F8(void) {
    Actor_Clear();
}

MATCH void func_801F7518(void) {
    SYS_DISPATCH_TASK(D_801FE820, 1, g_Task);
}

MATCH void func_801F755C(void) {
    g_Task->unk_06 = 0x4E;
    func_801F6FAC();
    g_Task->header.step = 0;
}

/* Item panel step: move the cursor, switch panel, or move one of the selected item into the stock at D_80144908. */
MATCH void func_801F7590(void) {
    func_801F7DDC();
    if (g_InputPressed & (PADLup | PADLdown)) {
        if (g_InputPressed & PADLup) {
            g_Task->header.step--;
        } else {
            g_Task->header.step++;
        }
        g_Task->header.step &= 7;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
        g_Task->unk_06 = (g_Task->header.step & 7) + 0x4E;
        Actor_SelectScript(g_Task->unk_06 - 0x4E);
    }
    if (g_InputPressed & PADRleft) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 9));
        g_Task->unk_0A      = 20;
        g_Task->header.mode = 2;
    } else if (g_InputPressed & PADRup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 12));
        g_Task->header.mode = 3;
    } else if (g_InputPressed & PADRdown) {
        if (Item_Count(0, g_Task->unk_06, 0) & 0xFFFF) {
            if (D_80144908[g_Task->header.step] < 100) {
                D_80144908[g_Task->header.step]++;
            }
            Item_Remove(0, g_Task->unk_06, 1, 0);
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 10));
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 13));
        }
    }
}

MATCH void func_801F7758(void) {
    Scena10Rect* rect;

    rect = &D_801FE7CC[2];
    UI_DrawPanelBox(rect->x, rect->y, (u8)rect->width, (u8)rect->height);
    func_801F781C((u16)rect->x + 1, (u16)rect->y + 1, 128, 104);
    if (g_Task->unk_0A != 0) {
        g_Task->unk_0A--;
    } else if (g_InputPressed != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 12));
        g_Task->header.mode = 1;
    }
}

/* Draw the item panel background at (x, y) and, on each of the eight rows, the glyph for each owned item up to three. */
MATCH void func_801F781C(u16 x, u16 y, u16 width, u16 height) {
    POLY_FT4* prim;
    u8        i;
    u8        j;
    u8        count;
    u8        glyph;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);
    setClut(prim, 64, 483);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setXY4(prim, x, y, x + width, y, x, y + height, x + width, y + height);
    setUV4(prim, 0, 0x98, 0x80, 0x98, 0, 0xFF, 0x80, 0xFF);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    i = 0;
    do {
        count = D_80144908[i];
        if (count > 3) {
            count = 3;
        }
        for (j = 0; j < count; j++) {
            glyph = D_801FE830[i][j];
            if (glyph != 10) {
                func_801F79E8(D_801FE848[glyph].vx + x, D_801FE848[glyph].vy + y);
            }
        }
        i++;
    } while (i < 8);
}

MATCH void func_801F79E8(u16 x, u16 y) {
    POLY_FT4* prim;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);
    setClut(prim, 48, 483);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setXY4(prim, x, y, x + 16, y, x, y + 16, x + 16, y + 16);
    setUV4(prim, 0xB0, 0x50, 0xC0, 0x50, 0xB0, 0x60, 0xC0, 0x60);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}

MATCH void func_801F7AD4(void) {
    Scena10Rect* rect;
    u8*          record;
    u8           count;
    u8           color;
    s16          x;
    s16          y;
    u8           i;

    rect = &D_801FE7CC[4];
    UI_DrawWindow(rect->x, rect->y, rect->width, rect->height, 0, g_WindowStyle);
    x = rect->x + 8;
    y = rect->y + 4;
    i = 0;
    do {
        record = Item_GetRecord(0, (u8)(i + 0x4E));
        count  = (u8)Item_Count(0, (u8)(i + 0x4E), 0);
        color  = -(count == 0) & 7;
        UI_DrawText(x, y, color, (u8)Game_ReadCommand(record), record);
        sprintf((char*)g_UiFormatBuffer, D_801F6C10, count);
        UI_DrawGlyphString(x + 0x5A, y + 3, color, g_UiFormatBuffer);
        i++;
        y += 0xF;
    } while (i < 8);
}

/* Draw rectangle 6: a styled window with the rectangle as one textured quad. */
MATCH void func_801F7C34(void) {
    POLY_FT4*    prim;
    Scena10Rect* rect;

    rect = &D_801FE7CC[6];
    func_801AE3F0((u16)rect->x, (u16)rect->y, rect->width, rect->height, 0, g_WindowStyle);
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);
    setClut(prim, 32, 483);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setXY4(prim, (u16)rect->x, (u16)rect->y, (u16)rect->x + (rect->width - 1), (u16)rect->y, (u16)rect->x, (u16)rect->y + rect->height, (u16)rect->x + (rect->width - 1), (u16)rect->y + rect->height);
    setUV4(prim, 0xC0, 0x50, (u8)rect->width + 0xBF, 0x50, 0xC0, (u8)rect->height + 0x50, (u8)rect->width + 0xBF, (u8)rect->height + 0x50);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}

/* Draw the "Choose parts" window with its item list and cursor, then place and step the cursor actor. */
MATCH void func_801F7DDC(void) {
    UI_DrawWindow(D_801FE7CC[3].x, D_801FE7CC[3].y, D_801FE7CC[3].width, D_801FE7CC[3].height, 2, g_WindowStyle);
    sprintf(g_UiFormatBuffer, D_801F6C04, D_801FE874);
    UI_DrawText((u16)D_801FE7CC[3].x + 8, D_801FE7CC[3].y + 2, 0, 12, g_UiFormatBuffer);
    func_801F7AD4();
    Menu_DrawCursorSprite(D_801FE808[0], (u16)(D_801FE808[1] + (g_Task->header.step & 7) * 15), 0);
    func_801F7C34();
    g_Task->screen_x = D_801FE7CC[5].x + D_801FE804[0];
    g_Task->screen_y = D_801FE7CC[5].y + D_801FE804[1];
    UI_DrawPanelBox(D_801FE7CC[5].x, D_801FE7CC[5].y, (u8)D_801FE7CC[5].width, (u8)D_801FE7CC[5].height);
    Actor_StepAnimLoop();
    Area_AddActor();
}

MATCH void func_801F7F50(void) {
    SYS_DISPATCH_BYTE(D_801FE8F4, D_80146872);
}

MATCH void func_801F7F8C(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7FA0);

MATCH void func_801F8550(void) {
    Game_SetScriptActive();
    Scene_SetupParty(0);
    g_AreaScrollTargetX = 0x490000;
    g_AreaScrollTargetY = 0x560000;
    Area_InitMapRenderer();
    g_AreaCameraAngle.vx = -0x23C;
    D_801FE9D8           = Actor_FindFreeSpawned();
    if (D_801FE9D8 != GAME_NONE) {
        g_SpawnedActors[D_801FE9D8].header.flags   = 1;
        g_SpawnedActors[D_801FE9D8].type           = 0x13;
        g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x2EC;
        g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
        g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x31E;
        g_SpawnedActors[D_801FE9D8].layer          = 0x80;
    }
    SND_RequestBGM(0x7A);
    g_SceneState.state_04 = 1;
    g_SceneState.step_05  = 0;
}

MATCH void func_801F8694(void) {
    SYS_DISPATCH_BYTE(D_801FE900, g_SceneState.state_04);
}

MATCH void func_801F86D0(void) {
}

INCLUDE_ASM(func_801F86D8);

INCLUDE_ASM(func_801F8C00);

INCLUDE_ASM(func_801F95B8);

MATCH void func_801F9FC4(void) {
    g_ScratchPad.cells.halves[0] = Actor_FindFreeField();
    if (g_ScratchPad.cells.halves[0] != 255) {
        func_801A4D54(D_801FE938);
    }
}

INCLUDE_ASM(func_801FA010);

MATCH u8 func_801FA5EC(void) {
    u8 i;
    u8 count;

    for (i = 0; i < 8; i += 1) {
        count = Item_Count(ITEM_CAT_ITEM, i + 0x4E, 0);
        if (count != 0) {
            return count;
        }
    }
    return 0;
}

MATCH s32 func_801FA644(void) {
    if (((D_80144908[0] >= 2) && (D_80144908[2] >= 3) && (D_80144908[3] >= 2) && (D_80144908[5] != 0)) && (D_80144908[7] >= 2)) {
        return 1;
    }
    return 0;
}
