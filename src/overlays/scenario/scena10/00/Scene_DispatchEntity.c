#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F6FAC(void) {
    Actor* work;

    Area_SceneSelectRecord(0x1EA);
    work                      = TASK(Actor);
    work->unk_48              = 0;
    work->pos.z.part.integer  = 0x64;
    TASK(Actor)->active_flags = 0;
    TASK(Actor)->mirror       = 0;
    TASK(Actor)->timer        = 0;
    TASK(Actor)->unk_0A       = 0x1E;
    TASK(Actor)->draw_layer   = 1;
    Script_Select((u8)(TASK(Actor)->unk_06 - 0x4E));
    TASK(Actor)->header.mode = 1;
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
        width = D_801FE7CC[i].box.w;
        timer = TASK(Actor)->timer;
        limit = timer << 4;
        if (limit < width) {
            width = limit;
        } else {
            count++;
        }
        height = D_801FE7CC[i].box.h;
        if (limit < height) {
            height = limit;
        } else {
            count++;
        }
        if ((TASK(Actor)->option_flags & (1 << i)) == 0) {
            UI_WindowDrawBoxOutline(D_801FE7CC[i].signed_box.x, D_801FE7CC[i].signed_box.y, (u8)width, (u8)height);
        }
        i++;
    }
    TASK(Actor)->timer++;
    if (count == 6) {
        TASK(Actor)->header.mode = 2;
    }
}
#else
INCLUDE_ASM(func_801F7068);
#endif

MATCH void func_801F719C(void) {
    u8 i;

    i = 0;
    do {
        if (((TASK(Actor)->option_flags >> i) & 1) == 0) {
            UI_WindowDrawPanelBox(D_801FE7CC[i].signed_box.x, D_801FE7CC[i].signed_box.y, (u8)D_801FE7CC[i].signed_box.w, (u8)D_801FE7CC[i].signed_box.h);
        }
        i++;
    } while (i < 3);
    if ((TASK(Actor)->option_flags & 1) == 0) {
        TASK(Actor)->screen_x = (u16)D_801FE7CC[0].signed_box.x + D_801FE804[0];
        TASK(Actor)->screen_y = (u16)D_801FE7CC[0].signed_box.y + D_801FE804[1];
        Script_AnimStepLoop();
        Area_AddActor();
    }
    if (((TASK(Actor)->option_flags >> 1) & 1) == 0) {
        sprintf((char*)g_UiTextFormatBuffer, D_801F6C04, Item_GetRecord(ITEM_CATEGORY_ITEM, TASK(Actor)->unk_06));
        UI_TextDraw((s16)((u16)D_801FE7CC[1].signed_box.x + 4), (s16)((u16)D_801FE7CC[1].signed_box.y + 2), 0, 8, g_UiTextFormatBuffer);
        sprintf((char*)g_UiTextFormatBuffer, D_801F6C08, (u16)Item_Count(ITEM_CATEGORY_ITEM, TASK(Actor)->unk_06, 0));
        UI_TextDraw((s16)((u16)D_801FE7CC[1].signed_box.x + 0x48), (s16)((u16)D_801FE7CC[1].signed_box.y + 2), 0, 2, g_UiTextFormatBuffer);
    }
    func_801F781C((u16)D_801FE7CC[2].signed_box.x + 1, (u16)D_801FE7CC[2].signed_box.y + 1, 0x80, 0x68);
    if (TASK(Actor)->unk_0A != 0) {
        TASK(Actor)->unk_0A--;
    } else if (g_PadStates[0].held != 0) {
        TASK(Actor)->header.mode = 3;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F73EC(void) {
    u32 height;
    u32 width;
    s32 limit;
    u8  i;

    i = 0;
    do {
        width  = D_801FE7CC[i].box.w;
        /* The copy is the clamp's operand, as retail compares against its a2 copy. */
        height = width;
        limit  = TASK(Actor)->timer << 4;
        if (((u16)limit) < height) {
            width = limit;
        }
        height = D_801FE7CC[i].box.h;
        if (((u16)limit) < height) {
            height = limit;
        }
        if (((TASK(Actor)->option_flags >> i) & 1) == 0) {
            UI_WindowDrawBoxOutline(D_801FE7CC[i].signed_box.x, D_801FE7CC[i].signed_box.y, (u8)width, (u8)height);
        }
        i++;
    } while (i < 3);
    TASK(Actor)->timer--;
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode = 4;
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
    TASK(Actor)->unk_06 = 0x4E;
    func_801F6FAC();
    TASK(Actor)->header.step = 0;
}

/* Item panel step: move the cursor, switch panel, or move one of the selected item into the stock at D_80144908. */
MATCH void func_801F7590(void) {
    func_801F7DDC();
    if (g_PadStates[0].pressed & (PADLup | PADLdown)) {
        if (g_PadStates[0].pressed & PADLup) {
            TASK(Actor)->header.step--;
        } else {
            TASK(Actor)->header.step++;
        }
        TASK(Actor)->header.step &= 7;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
        TASK(Actor)->unk_06 = (TASK(Actor)->header.step & 7) + 0x4E;
        Script_Select(TASK(Actor)->unk_06 - 0x4E);
    }
    if (g_PadStates[0].pressed & PADRleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 9));
        TASK(Actor)->unk_0A      = 20;
        TASK(Actor)->header.mode = 2;
    } else if (g_PadStates[0].pressed & PADRup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 12));
        TASK(Actor)->header.mode = 3;
    } else if (g_PadStates[0].pressed & PADRdown) {
        if (Item_Count(ITEM_CATEGORY_ITEM, TASK(Actor)->unk_06, 0) & 0xFFFF) {
            if (D_80144908[TASK(Actor)->header.step] < 100) {
                D_80144908[TASK(Actor)->header.step]++;
            }
            Item_Remove(ITEM_CATEGORY_ITEM, TASK(Actor)->unk_06, 1, 0);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 10));
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 13));
        }
    }
}

MATCH void func_801F7758(void) {
    RectU16* rect;

    rect = &D_801FE7CC[2];
    UI_WindowDrawPanelBox(rect->signed_box.x, rect->signed_box.y, (u8)rect->signed_box.w, (u8)rect->signed_box.h);
    func_801F781C((u16)rect->signed_box.x + 1, (u16)rect->signed_box.y + 1, 128, 104);
    if (TASK(Actor)->unk_0A != 0) {
        TASK(Actor)->unk_0A--;
    } else if (g_PadStates[0].pressed != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 12));
        TASK(Actor)->header.mode = 1;
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
    RectU16* rect;
    u8*      record;
    u8       count;
    u8       color;
    s16      x;
    s16      y;
    u8       i;

    rect = &D_801FE7CC[4];
    UI_WindowDraw(rect->box.x, rect->box.y, rect->box.w, rect->box.h, 0, g_WindowStyle);
    x = rect->box.x + 8;
    y = rect->box.y + 4;
    i = 0;
    do {
        record = Item_GetRecord(ITEM_CATEGORY_ITEM, (u8)(i + ITEM_PART_A));
        count  = (u8)Item_Count(ITEM_CATEGORY_ITEM, (u8)(i + ITEM_PART_A), 0);
        color  = -(count == 0) & 7;
        UI_TextDraw(x, y, color, (u8)Game_ReadCommand(record), record);
        sprintf((char*)g_UiTextFormatBuffer, D_801F6C10, count);
        UI_TextDrawGlyphString(x + 0x5A, y + 3, color, g_UiTextFormatBuffer);
        i++;
        y += 0xF;
    } while (i < 8);
}

/* Draw rectangle 6: a styled window with the rectangle as one textured quad. */
MATCH void func_801F7C34(void) {
    POLY_FT4* prim;
    RectU16*  rect;

    rect = &D_801FE7CC[6];
    func_801AE3F0((u16)rect->box.x, (u16)rect->box.y, rect->box.w, rect->box.h, 0, g_WindowStyle);
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);
    setClut(prim, 32, 483);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setXY4(prim, (u16)rect->box.x, (u16)rect->box.y, (u16)rect->box.x + (rect->box.w - 1), (u16)rect->box.y, (u16)rect->box.x, (u16)rect->box.y + rect->box.h, (u16)rect->box.x + (rect->box.w - 1),
           (u16)rect->box.y + rect->box.h);
    setUV4(prim, 0xC0, 0x50, (u8)rect->box.w + 0xBF, 0x50, 0xC0, (u8)rect->box.h + 0x50, (u8)rect->box.w + 0xBF, (u8)rect->box.h + 0x50);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}

/* Draw the "Choose parts" window with its item list and cursor, then place and step the cursor actor. */
MATCH void func_801F7DDC(void) {
    UI_WindowDraw(D_801FE7CC[3].box.x, D_801FE7CC[3].box.y, D_801FE7CC[3].box.w, D_801FE7CC[3].box.h, UI_WINDOW_STYLE_TRANSLUCENT, g_WindowStyle);
    sprintf(g_UiTextFormatBuffer, D_801F6C04, D_801FE874);
    UI_TextDraw((u16)D_801FE7CC[3].box.x + 8, D_801FE7CC[3].box.y + 2, 0, ITEM_NAME_LENGTH, g_UiTextFormatBuffer);
    func_801F7AD4();
    UI_CursorDraw(D_801FE808[0], (u16)(D_801FE808[1] + (TASK(Actor)->header.step & 7) * 15), 0);
    func_801F7C34();
    TASK(Actor)->screen_x = D_801FE7CC[5].signed_box.x + D_801FE804[0];
    TASK(Actor)->screen_y = D_801FE7CC[5].signed_box.y + D_801FE804[1];
    UI_WindowDrawPanelBox(D_801FE7CC[5].signed_box.x, D_801FE7CC[5].signed_box.y, (u8)D_801FE7CC[5].signed_box.w, (u8)D_801FE7CC[5].signed_box.h);
    Script_AnimStepLoop();
    Area_AddActor();
}

MATCH void func_801F7F50(void) {
    SYS_DISPATCH_BYTE(D_801FE8F4, D_80146872);
}

MATCH void func_801F7F8C(void) {
    D_80146872 = 1;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F7FA0(void) {
    s32 actor_index;
    u16 updated_flags;
    u8  slot;

    if (g_GameAreaId == 0x52) {
        if ((g_GameCellType == 0) && (SYS_TestFlag(g_SceneFlags, 4) == 0)) {
            SYS_ClearFlag(g_SceneFlags, 0x33);
        }
        if ((g_GameCellType == 1) && (SYS_TestFlag(g_SceneFlags, 0x3D) != 0) && (SYS_TestFlag(g_SceneFlags, 4) == 0)) {
            func_801F8550();
        }
    }
    if (g_GameAreaId == 0x5E) {
        if ((SYS_TestFlag(g_SceneFlags, 0x17) == 0) && (SYS_TestFlag(g_SceneFlags, 0x16) != 0)) {
            g_AreaDrawFlags = 0;
            SYS_SetFlag(g_SceneFlags, 0x17);
        }
        if (SYS_TestFlag(g_SceneFlags, 0x12) == 0) {
            func_801A4BC0(0x31, 0x1A, 0);
            func_801A4BC0(0x32, 0x1A, 0);
        }
    }
    if ((g_GameAreaId == 0x62) && (g_GameCellType == 0) && (SYS_TestFlag(g_SceneFlags, 4) != 0) && (SYS_TestFlag(g_SceneFlags, 8) == 0)) {
        func_801C1DF0(0);
        func_801BE1B0(1);
    }
    if (g_GameAreaId == 0x69) {
        if ((g_GameCellType == 0) && (SYS_TestFlag(g_SceneFlags, 0x35) == 0)) {
            SYS_SetFlag(g_SceneEventFlags, 0x4F);
        }
        if (g_GameCellType == 1) {
            SYS_SetFlag(g_SceneFlags, 0x36);
        }
    }
    if ((g_GameAreaId == 0x78) && (SYS_TestFlag(g_SceneFlags, 0x3D) == 0)) {
        if (SYS_TestFlag(g_SceneFlags, 0x39) != 0) {
            if (SYS_TestFlag(g_SceneFlags, 0x3A) == 0) {
                func_801BE1B0(2);
            } else if (SYS_TestFlag(g_SceneFlags, 0x3B) == 0) {
                if (g_GameCellType == 5) {
                    func_801BE1B0(7);
                    updated_flags = g_GameFlags | 0x10;
                } else {
                    updated_flags = g_GameFlags & 0xFFEF;
                }
                g_GameFlags = updated_flags;
            }
        }
        if (SYS_TestFlag(g_SceneFlags, 0x3C) != 0) {
            func_801C1DF0(5);
            func_801BE1B0(6);
            g_GameFlags &= 0xFFEF;
        }
    }
    if (g_GameAreaId == 0x79) {
        if ((SYS_TestFlag(g_SceneFlags, 0x16) == 0) && (SYS_TestFlag(g_SceneFlags, 0x15) != 0)) {
            g_AreaCameraAngle.vx       = -0x2EC;
            FIELD(s16, &D_801492DA, 2) = 0x360;
            g_AreaCameraOffsetZ        = 0x5DC;
            func_801C601C(0);
        }
        g_Game.members[0].param.unk_0B = 0;
    }
    if ((g_GameAreaId == 0x80) && (g_GameCellType == 3) && (SYS_TestFlag(g_SceneFlags, 0x12) == 0) && (SYS_TestFlag(g_SceneFlags, 0xB) != 0)) {
        SYS_SetFlag(g_SceneFlags, 0xC);
    }
    if (g_GameAreaId == 0x83) {
        if (SYS_TestFlag(g_SceneFlags, 0x12) != 0) {
            if (g_GameCellType != 0) {
                SND_SEPlay(0x205);
                D_801FE9DC = 1;
            } else {
                SND_SEPlay(0x204);
                D_801FE9DC = 0;
            }
        }
    }
    if ((g_GameAreaId == 0x84) && (g_GameCellType == 1) && (SYS_TestFlag(g_SceneFlags, 0x14) == 0)) {
        SND_SEPlay(0x204);
        D_801FE9DC                 = 1;
        FIELD(s16, &D_801492DA, 2) = 0x302;
        slot                       = func_8019601C();
        actor_index                = slot & 0xFF;
        D_801FE9D8                 = slot;
        if (actor_index != 0xFF) {
            g_SpawnedActors[actor_index].header.flags  = 1;
            g_SpawnedActors[D_801FE9D8].type           = 0x13;
            g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x2AA;
            g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x200;
            g_SpawnedActors[D_801FE9D8].layer          = 0x40;
            g_SpawnedActors[D_801FE9D8].camera_angle.y = D_801492DA;
        }
    }
    D_80146872 = 2;
}
#else
INCLUDE_ASM(func_801F7FA0);
#endif

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
    SND_BGMRequest(0x7A);
    g_ScenarioState.state_04 = 1;
    g_ScenarioState.step     = 0;
}

MATCH void func_801F8694(void) {
    SYS_DISPATCH_BYTE(D_801FE900, g_ScenarioState.state_04);
}

MATCH void func_801F86D0(void) {
}

/* Runs one step of a scena10 scene script, picked by g_ScenarioState.step: spawns its actors, greys the palette and moves the camera. */
MATCH void func_801F86D8(void) {
    u32           row;
    u32           col;
    u32           row_base;
    u16*          cell;
    u32           color;
    u32           red;
    u32           rgb;
    u32           average;
    u32           packed;
    SpawnedActor* actor;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_SpawnedActors[D_801FE9D8].header.flags & 1) {
                break;
            }
            g_ScriptVars[0]      = 1;
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            D_801FE9D8 = Actor_FindFreeSpawned();
            if (D_801FE9D8 != GAME_NONE) {
                g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                g_SpawnedActors[D_801FE9D8].type           = 0x13;
                g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x2AA;
                g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x200;
                g_SpawnedActors[D_801FE9D8].layer          = 0x78;
            }
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 9 || !EMI_IsReady()) {
                break;
            }
            g_ScenarioState.step = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 0x19) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (g_SysThreads[2].state) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_8019FA28(0x42, 0x190000, 0x120000, 0x80);
            g_GamePrevSelection  = 0xFF;
            g_ScenarioState.step = 7;
            break;
        case 7:
            if (g_SysThreads[2].state) {
                break;
            }
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
            g_GfxPalettePending  = 1;
            g_ScenarioState.step = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            UI_ModeSet(1);
            g_ScenarioState.step = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_AreaScrollTargetX  = 0x160000;
            g_AreaScrollTargetY  = 0x150000;
            g_AreaCameraSpeed    = 0x20;
            g_ScenarioState.step = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 5);
            func_8019FA28(0x52, 0x480000, 0x580000, 0x81);
            g_GamePrevSelection  = 0xFF;
            g_ScenarioState.step = 11;
            break;
        case 11:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                actor               = &g_SpawnedActors[g_ScratchPad.cells.bytes[0]];
                actor->header.flags = 1;
                actor->type         = 0x20;
                actor->pos.x.fixed  = MEM_PTR(Coord3, D_801468BC)->x.fixed;
                actor->pos.y.fixed  = MEM_PTR(Coord3, D_801468BC)->y.fixed;
                actor->pos.z.fixed  = (Area_HeightSample(actor->pos.x.fixed, actor->pos.y.fixed) << 16) + 0x800000;
            }
            g_ScenarioState.step = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 6);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
}
