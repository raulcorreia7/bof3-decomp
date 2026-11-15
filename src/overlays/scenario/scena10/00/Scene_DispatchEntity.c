#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

INCLUDE_ASM(func_801F6FAC);

INCLUDE_ASM(func_801F7068);

INCLUDE_ASM(func_801F719C);

INCLUDE_ASM(func_801F73EC);

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
    func_80159B9C(rect->x, rect->y, (u8)rect->width, (u8)rect->height);
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
    prim->tpage = GetTPage(0, 0, 704, 256);
    setClut(prim, 64, 483);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setXY4(prim, x, y, x + width, y, x, y + height, x + width, y + height);
    setUV4(prim, 0, 0x98, 0x80, 0x98, 0, 0xFF, 0x80, 0xFF);
    GFX_AddPrim(1, sizeof(POLY_FT4));
    i = 0;
    do {
        count = D_80144908[i];
        if (count > 3) {
            count = 3;
        }
        for (j = 0; j < count; j++) {
            glyph = D_801FE830[i][j];
            if (glyph != 10) {
                func_801F79E8(D_801FE848[glyph].x + x, D_801FE848[glyph].y + y);
            }
        }
        i++;
    } while (i < 8);
}

INCLUDE_ASM(func_801F79E8);

INCLUDE_ASM(func_801F7AD4);

INCLUDE_ASM(func_801F7C34);

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
    func_80159B9C(D_801FE7CC[5].x, D_801FE7CC[5].y, (u8)D_801FE7CC[5].width, (u8)D_801FE7CC[5].height);
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
    func_801BE1B0(0);
    g_AreaScrollTargetX = 0x490000;
    g_AreaScrollTargetY = 0x560000;
    func_80153DE8();
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
    D_1F800000.view.area.entity_counter = Actor_FindFreeField();
    if (D_1F800000.view.area.entity_counter != 255) {
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

INCLUDE_ASM(func_801FA644);
