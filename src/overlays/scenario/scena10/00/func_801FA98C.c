#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FA98C(void) {
    u8 slot;
    u8 next;

    switch (g_ScenarioState.step) {
        case 0:
            D_801FE9DC = 0;
            UI_ModeSet(0);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C1DF0(1);
            g_ScenarioState.step = 2;
            break;
        case 2:
            func_8019FA28(0x80, 0x580000, 0x390000, 0x85);
            g_GameRequestType    = 0xFF;
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0x88;
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            UI_ModeSet(1);
            g_ScriptVars[0]      = 1;
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SND_BGMFadeOut(0x88, 0x64, 4);
            SND_SEPlay(0x204);
            D_801FE9DC               = 1;
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 5;
            break;
        case 5:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_801FE9DC = 0;
            UI_ModeSet(1);
            g_AreaScrollTargetX = 0x1F0000;
            g_AreaScrollTargetY = 0x360000;
            Area_InitMapRenderer();
            g_ScriptVars[0]++;
            g_ScenarioState.step = 7;
            break;
        case 7:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.step = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            g_ScenarioState.step = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                g_SpawnedActors[D_801FE9D8].type           = 0x13;
                g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x2D6;
                g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x29A;
                g_SpawnedActors[D_801FE9D8].layer          = 0x80;
            }
            func_801C601C(1);
            g_ScenarioState.step = 0xA;
            break;
        case 10:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            if (g_SpawnedActors[D_801FE9D8].header.flags & 1) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_801FE9DC = 1;
            UI_ModeSet(1);
            g_AreaScrollTargetX = 0x510000;
            g_PartyX            = 0x510000;
            g_AreaScrollTargetY = 0x80000;
            g_PartyY            = 0x80000;
            Area_InitMapRenderer();
            Area_ScrollAdvance(-0x560);
            g_ScenarioState.step = 0xC;
            break;
        case 12:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            next = 0xD;
            goto advance_low;
            break;
        case 13:
            if (g_ScriptVars[0] != 0xD) {
                break;
            }
            UI_ModeSet(0);
            SND_BGMPlay(0x86, 0x64, 0x10);
            g_ScenarioState.step = 0xE;
            break;
        case 14:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            UI_ModeSet(1);
            g_AreaScrollTargetX = 0x580000;
            g_PartyX            = 0x580000;
            g_AreaScrollTargetY = 0x390000;
            g_PartyY            = 0x390000;
            Area_InitMapRenderer();
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[D_801FE9D8].header.flags = 1;
                g_SpawnedActors[D_801FE9D8].type         = 0x18;
                g_SpawnedActors[D_801FE9D8].header.mode  = 0x63;
            }
            Area_ScrollAdvance(-0x9C0);
            g_ScenarioState.step = 0xF;
            break;
        case 15:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            next = 0x10;
            goto advance_low;
            break;
        case 16:
            if (g_ScriptVars[0] != 0x13) {
                break;
            }
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[D_801FE9D8].header.flags   = 1;
            g_SpawnedActors[D_801FE9D8].type           = 0x13;
            g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x210;
            g_SpawnedActors[D_801FE9D8].camera_angle.y = D_801492DA;
            g_SpawnedActors[D_801FE9D8].camera_angle.z = 0xE2;
            g_SpawnedActors[D_801FE9D8].layer          = 0x5A;
            SND_SEPlay(0x203);
            g_ScenarioState.step = 0x11;
            break;
        case 17:
            if (g_SpawnedActors[D_801FE9D8].header.flags & 1) {
                break;
            }
            D_801FE9DC = 0;
            g_GameFlags |= 0x80;
            SND_SEPlay(0x205);
            func_8019FA28(0x79, 0x2A0000, 0x180000, 0x80);
            g_GameRequestType    = 1;
            g_ScenarioState.step = 0x12;
            break;
        case 18:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            if (g_ScriptVars[0] != 1) {
                break;
            }
            func_801C1E3C(1);
            func_8019FA28(0x84, 0x50000, 0x460000, 0x80);
            g_GameEntryMode      = 0;
            g_ScenarioState.step = 0x13;
            break;
        case 19:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            if (g_ScriptVars[0] != 5) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            SYS_SetFlag(g_SceneFlags, 0x14);
            g_ScenarioState.step = 0x14;
        case 20:
            if (g_GameCellType == 0) {
                D_801FE9DC = 0;
                break;
            }
            D_801FE9DC = 1;
            break;
        case 21:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C1DF0(2);
            func_8019FA28(0x84, 0x50000, 0x460000, 0x82);
            g_GameRequestType        = 0xFF;
            g_GameEntryMode          = 0xFF;
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0x16;
            break;
        case 22:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            D_801FE9DC           = 1;
            g_AreaDrawFlags      = 0x1F;
            g_ScenarioState.step = 0x17;
            break;
        case 23:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            g_AreaScrollTargetX = 0x240000;
            g_PartyX            = 0x240000;
            g_AreaDrawFlags     = 0;
            D_801FE9DC          = 0;
            g_AreaScrollTargetY = 0x2E0000;
            g_PartyY            = 0x2E0000;
            Area_InitMapRenderer();
            (void)Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0x18;
            break;
        case 24:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            next            = 0x19;
            goto advance;
            break;
        case 25:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            D_801FE9DC          = 1;
            g_AreaScrollTargetX = 0x50000;
            g_PartyX            = 0x50000;
            g_AreaDrawFlags     = 0;
            g_AreaScrollTargetY = 0x460000;
            g_PartyY            = 0x460000;
            Area_InitMapRenderer();
            (void)Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0x1A;
            break;
        case 26:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            next            = 0x1B;
            goto advance;
            break;
        case 27:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            g_AreaScrollTargetX = 0x240000;
            g_PartyX            = 0x240000;
            g_AreaDrawFlags     = 0;
            D_801FE9DC          = 0;
            g_AreaScrollTargetY = 0x2E0000;
            g_PartyY            = 0x2E0000;
            Area_InitMapRenderer();
            (void)Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0x1C;
            break;
        case 28:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            next            = 0x1D;
            goto advance;
            break;
        case 29:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[D_801FE9D8].header.flags   = 1;
            g_SpawnedActors[D_801FE9D8].type           = 0x13;
            g_SpawnedActors[D_801FE9D8].camera_angle.x = g_AreaCameraAngle.vx;
            g_SpawnedActors[D_801FE9D8].camera_angle.y = D_801492DA;
            g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x10E;
            g_SpawnedActors[D_801FE9D8].layer          = 0x40;
            g_ScenarioState.step                       = 0x1E;
            break;
        case 30:
            if (g_SpawnedActors[D_801FE9D8].header.flags & 1) {
                break;
            }
            g_ScenarioState.step = 0x1F;
            g_ScriptVars[0]++;
            break;
        case 31:
            if (g_ScriptVars[0] != 0xD) {
                break;
            }
            D_801FE9DC          = 1;
            g_AreaScrollTargetX = 0x50000;
            g_PartyX            = 0x50000;
            g_AreaDrawFlags     = 0;
            g_AreaScrollTargetY = 0x460000;
            g_PartyY            = 0x460000;
            Area_InitMapRenderer();
            (void)Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0x20;
            break;
        case 32:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            next            = 0x21;
            goto advance;
            break;
        case 33:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            g_AreaScrollTargetX = 0x1A0000;
            g_PartyX            = 0x1A0000;
            g_AreaDrawFlags     = 0;
            D_801FE9DC          = 0;
            g_AreaScrollTargetY = 0x110000;
            g_PartyY            = 0x110000;
            Area_InitMapRenderer();
            Area_ScrollAdvance(0x320);
            g_AreaCameraAngle.vx     = -0x32E;
            g_AreaCameraAngle.vz     = 0x74;
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0x22;
            break;
        case 34:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            g_ScriptVars[0]++;
            SND_SEPlay(0x205);
            SND_SEPlay(0x200);
            SND_StartDecrescendo(0, 0, 0x64, 8);
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[D_801FE9D8].header.flags = 1;
                g_SpawnedActors[D_801FE9D8].type         = 0x18;
                g_SpawnedActors[D_801FE9D8].header.mode  = 0x5F;
            }
            g_AreaSceneMode      = 0x23;
            g_ScenarioState.step = 0x23;
            break;
        case 35:
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[D_801FE9D8].header.flags   = 1;
            g_SpawnedActors[D_801FE9D8].type           = 0x13;
            g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x3C8;
            g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[D_801FE9D8].camera_angle.z = g_AreaCameraAngle.vz;
            g_SpawnedActors[D_801FE9D8].layer          = 0x40;
            g_ScenarioState.step                       = 0x24;
            break;
        case 36:
            if (g_SpawnedActors[D_801FE9D8].header.flags & 1) {
                break;
            }
            g_ScenarioState.step = 0x25;
            break;
        case 37:
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[D_801FE9D8].header.flags   = 1;
            g_SpawnedActors[D_801FE9D8].type           = 0x13;
            g_SpawnedActors[D_801FE9D8].camera_angle.x = g_AreaCameraAngle.vx;
            g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x17C;
            g_SpawnedActors[D_801FE9D8].layer          = 0x50;
            g_ScenarioState.step                       = 0x26;
            break;
        case 38:
            if (g_SpawnedActors[D_801FE9D8].header.flags & 1) {
                break;
            }
            g_ScenarioState.step = 0x27;
            break;
        case 39:
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[D_801FE9D8].header.flags   = 1;
            g_SpawnedActors[D_801FE9D8].type           = 0x31;
            g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x3F4;
            g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[D_801FE9D8].vx             = 0x100;
            g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x2B0;
            g_SpawnedActors[D_801FE9D8].layer          = 0xFF;
            g_ScenarioState.timer_06                   = 0x50;
            g_ScenarioState.step                       = 0x28;
            break;
        case 40:
            if (g_SpawnedActors[D_801FE9D8].header.flags & 1) {
                break;
            }
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 0x29;
            break;
        case 41:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            UI_ModeSet(1);
            g_AreaScrollTargetX = 0x240000;
            g_PartyX            = 0x240000;
            g_AreaScrollTargetY = 0x2F0000;
            g_PartyY            = 0x2F0000;
            Area_InitMapRenderer();
            g_AreaCameraAngle.vx = -0x2AA;
            g_AreaCameraAngle.vz = 0x74;
            slot                 = func_8019601C();
            D_801FE9D8           = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                g_SpawnedActors[D_801FE9D8].type           = 0x13;
                g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x32E;
                g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x334;
                g_SpawnedActors[D_801FE9D8].layer          = 0x40;
            }
            g_ScriptVars[0]++;
            SND_SeqPlay(0, 0, 0, 0);
            SND_SeqFadeIn(0, 0, 0x64, 8);
            SND_SEPlay(0x201);
            SND_SEPlay(0x204);
            g_ScenarioState.step = 0x2A;
            break;
        case 42:
            g_AreaSceneMode = 0x23;
            if (g_ScriptVars[0] != 0x13) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 0x2B;
            break;
        case 43:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            D_801FE9DC          = 1;
            g_AreaScrollTargetX = 0x50000;
            g_PartyX            = 0x50000;
            g_AreaDrawFlags     = 0;
            g_AreaScrollTargetY = 0x460000;
            g_PartyY            = 0x460000;
            Area_InitMapRenderer();
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0x2C;
            break;
        case 44:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            next            = 0x2D;
            goto advance;
            break;
        case 45:
            if (g_ScriptVars[0] != 0x17) {
                break;
            }
            D_801FE9DC = 0;
            func_801C1DF0(3);
            SND_SEPlay(0x205);
            func_8019FA28(0x79, 0x2C0000, 0x370000, 0x80);
            g_GameRequestType    = 1;
            g_ScenarioState.step = 0x2E;
            break;
        case 46:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            slot       = func_8019601C();
            D_801FE9D8 = slot;
            if ((slot & BYTE_MASK) == GAME_NONE) {
                break;
            }
            g_SpawnedActors[D_801FE9D8].header.flags   = 1;
            g_SpawnedActors[D_801FE9D8].type           = 0x13;
            g_SpawnedActors[D_801FE9D8].camera_angle.x = g_AreaCameraAngle.vx;
            g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[D_801FE9D8].camera_angle.z = 0xA0;
            g_SpawnedActors[D_801FE9D8].layer          = 0xCC;
            g_ScenarioState.step                       = 0x2F;
            break;
        case 47:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x16);
            g_GameFlags &= ~0x80;
            func_8019FA28(0x5E, 0x320000, 0x210000, 0x8D);
            g_GameRequestType    = 0xFF;
            g_GameEntryMode      = 0;
            g_ScenarioState.step = 0x30;
            break;
        case 48:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            UI_MessageStartArea(0x96);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0x31;
            break;
        case 49:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            UI_ModeSet(1);
            g_ScriptVars[0]++;
            g_ScenarioState.step = 0x32;
            break;
        case 50:
            if (g_ScriptVars[0] != 0x15) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x17);
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
    goto epilogue;

advance_low:
    g_ScenarioState.step = next;
    g_ScriptVars[0]++;
    goto epilogue;

advance:
    g_ScenarioState.step = next;
    g_ScriptVars[0]++;
epilogue:
    func_801FC220();
}
#else
INCLUDE_ASM(func_801FA98C);
#endif
