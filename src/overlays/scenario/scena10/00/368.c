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

INCLUDE_ASM(func_801FA6BC);

INCLUDE_ASM(func_801FA98C);

MATCH void func_801FC220(void) {
    if (D_801FE9DC != 0) {
        s8 step                  = D_801FE94C[g_FrameCount & 0x3];
        g_AreaCameraRefreshCount = 2;
        g_AreaCameraOffsetY += step * 4;
    }
}

INCLUDE_ASM(func_801FC280);

MATCH void func_801FC830(void) {
    if (g_SceneState.step_05 == 1) {
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
            func_801BE1B0(2);
            SYS_SetFlag(g_SceneFlags, 52);
            g_SceneState.state_04 = 0;
            g_SceneState.step_05  = 0;
        }
    }
}

MATCH void func_801FC8A0(void) {
    if (g_SceneState.step_05 == 0x23) {
        Game_ClearScriptActive();
        func_801BE1B0(4);
        *g_ScriptVars         = 0x20;
        g_SceneState.state_04 = 0;
        g_SceneState.step_05  = 0;
    }
}

INCLUDE_ASM(func_801FC900);

INCLUDE_ASM(func_801FCD80);

MATCH u16 func_801FD278(void) {
    SCENA10_PARTY_LOOKUP(4, D_801FE950, D_801FE954, 0);
}

MATCH u16 func_801FD31C(void) {
    SCENA10_PARTY_LOOKUP(5, D_801FE95C, D_801FE964, 0);
}

MATCH u16 func_801FD3C0(void) {
    SCENA10_PARTY_LOOKUP(3, D_801FE970, D_801FE974, 0xFFFF);
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FD4A4(void) {
    Game_SetScriptActive();
    func_801BE1B0(1);
}

MATCH void func_801FD4CC(void) {
    Game_SetScriptActive();
    func_801BE1B0(4);
}

MATCH void func_801FD4F4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FD528(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 0xA;
    g_ScriptVars[0]       = 0xA;
}

MATCH void func_801FD568(Actor* actor) {
    SCENA10_ACTOR_START(0, 5, 0xF);
}

/* Pick up the item hidden at the actor's cell: add it to the inventory, mark its trigger and show the message. */
MATCH void func_801FD5C0(Actor* actor) {
    u8 i;

    i = 0;
    do {
        if (D_801FE894[i].x == COORD_INT(g_Task->pos.x) && D_801FE894[i].y == COORD_INT(g_Task->pos.y)) {
            g_Task->param.unk_0B = D_801FE894[i].script + 0x4E;
            strncpy(g_TextVariables[0], Item_GetRecord(0, g_Task->param.unk_0B), 12);
            g_TextVariables[0][12] = 0;
            if (Item_Add(0, g_Task->param.unk_0B, 1, 0)) {
                /* FAKE: retail passes the bit index unmasked, as s32. */
                ((void (*)(void*, s32))SYS_SetFlag)(g_SceneFlags, SCENE_TRIGGER_FLAG_BASE + D_801FE894[i].flag);
                Message_Request(2);
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
                actor->unk_7E++;
                Game_SetScriptActive();
            } else {
                Message_Request(3);
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            return;
        }
        i++;
    } while (i < ARRAY_COUNT(D_801FE894));
}

MATCH void func_801FD734(void) {
    u8 i;

    i = 0;
    do {
        if (D_801FE894[i].x == COORD_INT(g_Task->pos.x) && D_801FE894[i].y == COORD_INT(g_Task->pos.y)) {
            if (SYS_TestFlag(g_SceneFlags, SCENE_TRIGGER_FLAG_BASE + D_801FE894[i].flag) == 0) {
                Actor_SelectScript(D_801FE894[i].script);
                g_Task->unk_2A = 0;
            } else {
                g_Task->header.flags = 0;
            }
            return;
        }
        i++;
    } while (i < ARRAY_COUNT(D_801FE894));
}

MATCH void func_801FD814(void) {
    u8 saved_slot;

    saved_slot               = g_Task->param.actor_slot;
    g_Task->param.actor_slot = Actor_FindFreeSpawned();
    if (g_Task->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x5D;
        g_SpawnedActors[g_Task->param.actor_slot].unk_06       = saved_slot;
        g_SpawnedActors[g_Task->param.actor_slot].unk_07       = 0;
    } else {
        g_Task->param.actor_slot = saved_slot;
        g_ScriptState->cursor -= 2;
    }
}

MATCH void func_801FD95C(Actor* actor) {
    SCENA10_ACTOR_START(0xA, 0x1E, 0x13);
}

MATCH void func_801FD9B4(Actor* actor) {
    SCENA10_ACTOR_START(0xB, 0x1F, 0x13);
}

MATCH void func_801FDA0C(Actor* actor) {
    u8* state;

    Game_SetScriptActive();
    func_801BE1B0(1);
    SYS_SetFlag(g_SceneFlags, 21);
    state = &D_80146875;
    *state += 1;
    actor->unk_7E += 1;
}

MATCH void func_801FDA74(void) {
    SYS_SetFlag(g_SceneFlags, 25U);
}

MATCH void func_801FDA9C(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xA;
    g_SceneState.step_05  = 1;
}

MATCH void func_801FDAD4(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xD;
    g_SceneState.step_05  = 5;
}

INCLUDE_ASM(func_801FDB14);

MATCH s32 func_801FE00C(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_JUNK_TOWN) {
        if (SYS_TestFlag(g_SceneFlags, 8) && SYS_TestFlag(g_SceneFlags, 9) == 0 && y >= TO_COORD(48) && (u32)((x >> 16) - 28) < 5) {
            Game_SetScriptActive();
            SYS_SetFlag(g_SceneFlags, 9);
            SYS_SetFlag(g_SceneEventFlags, 67);
            g_ScriptVars[0] = 10;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_TIDAL_CAVES_OUTSIDE && D_80143F03 == 0 && SYS_TestFlag(g_SceneFlags, 53) == 0 && (y >> 16) >= 29) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 12;
        g_SceneState.step_05  = 0;
        return 1;
    }
    if (g_GameAreaId == AREA_ID_CLIFF_GAIST && D_80143F03 == 5 && SYS_TestFlag(g_SceneFlags, 59) && SYS_TestFlag(g_SceneFlags, 60) == 0 && y == TO_COORD(116) + COORD_HALF && x == TO_COORD(37)) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 13;
        g_SceneState.step_05  = 15;
    }
    if (g_GameAreaId == AREA_ID_MACHINE_GUILD_DOCK) {
        if (SYS_TestFlag(g_SceneFlags, 10) == 0 && y > TO_COORD(42) - 1 && (u32)((x >> 16) - 32) < 5) {
            Game_SetScriptActive();
            g_SceneState.state_04 = 3;
            g_SceneState.step_05  = 0;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 11) && SYS_TestFlag(g_SceneFlags, 13) == 0 && y <= TO_COORD(55) && (u32)((x >> 16) - 31) < 2) {
            Game_SetScriptActive();
            g_SceneState.state_04 = 4;
            g_SceneState.step_05  = 10;
            return 1;
        }
    }
    return 0;
}

MATCH bool func_801FE2B0(void) {
    u8 i;

    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_GARR) {
            return 1;
        }
    }
    return 0;
}

MATCH void Scene_JoinPartyRyuAdultGarrNinaAdult(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_NINA_ADULT);
}

MATCH void func_801FE360(void) {
    u8 i;

    for (i = 0; i < g_Game.party_size; i++) {
        Party_RemoveMember(g_Game.members[i].chr.character_id);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_MOMO);
}

/* func_801FE3F8 */
MATCH void Party_JoinNinaAdult(void) {
    Party_JoinMember(CHAR_ID_NINA_ADULT);
}

/* func_801FE418 */
MATCH void Party_JoinMomo(void) {
    Party_JoinMember(CHAR_ID_MOMO);
}

MATCH void func_801FE438(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        ids[slot] = D_80144908[slot];
    }
    EMI_LoadPartyArchives(ids[0], ids[1], ids[2], 0);
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_JoinMember(ids[slot]);
        }
    }
}

#include "overlays/scenario/Scene_RebuildRyuGarrParty.h"

MATCH void func_801FE5B0(void) {
    g_Characters[g_CharSlot[5]].unk_07 &= 254;
    Party_RemoveMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveMomo.h"

MATCH void func_801FE63C(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_RemoveMember(ids[slot]);
        }
    }
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_StashPartyExceptRyuAdult.h"
